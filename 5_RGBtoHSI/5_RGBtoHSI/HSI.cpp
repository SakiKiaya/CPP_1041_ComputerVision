#include "stdafx.h"
#include "HSI.h"

using namespace System;
using namespace System::Drawing;

HSI::HSI()
{
	PI = 4 * atan(1.0);
	if (srcHistogram == nullptr){
		srcHistogram = gcnew array<int>(256);
		HistogramEqualization = gcnew array<int>(256);
	}
	this->releseArray();
}

//	Open image in this class
void HSI::openfile(System::String^ fileName){
	this->Image1 = safe_cast<System::Drawing::Bitmap^>(System::Drawing::Image::FromFile(fileName));	//將選取的檔案讀取並且存至Image1			
	setPtr_bit(Image1->PixelFormat);
	this->rect = System::Drawing::Rectangle(0, 0, this->Image1->Width, this->Image1->Height);	//設定rect範圍大小
	this->Width_src = this->Image1->Width;
	this->Height_src = this->Image1->Height;
	this->TotalPixel = this->Width_src*this->Height_src;
}

void HSI::reOpen(System::String^ fileName){
	this->openfile(fileName);
}


Bitmap^ HSI::getHEResult(System::String^ filename){
	openfile(filename);
	doHE();
	return Image2;
}

void HSI::doHE(){
	genSrcHistogram();
	genEqualization();
	doEqualization();
}

//	Gen SrcHistogram with I
void HSI::genSrcHistogram(){
	ImageData1 = Image1->LockBits(rect, Drawing::Imaging::ImageLockMode::ReadWrite, Image1->PixelFormat);
	ptr = ImageData1->Scan0;
	p = (Byte*)((System::Void*)ptr);
	double B, G, R, I, S, H;
	for (int y = 0; y < Image1->Height; y++){
		for (int x = 0; x < Image1->Width; x++){
			B = p[ptr_bit*(x + Width_src*y) + 0];
			G = p[ptr_bit*(x + Width_src*y) + 1];
			R = p[ptr_bit*(x + Width_src*y) + 2];

			setSrcHistogramWithI(figureOutI(B, G, R));
		}
	}
	Image1->UnlockBits(ImageData1);
}

//	Save I to srcHistogram arrary
void HSI::setSrcHistogramWithI(double I){
	int pixel;
	round(I *= 255);	//	convert I to gray 0~255 level

	//	set Histogram for I
	if (I > 255){
		pixel = 255;
	}
	else{
		pixel = I;
	}

	if (srcHistogram[pixel] == -1)
		srcHistogram[pixel] = 0;
	srcHistogram[pixel]++;
}

//	convert RGB to HSI, return I
double HSI::figureOutI(int B, int G, int R){
	double I = (double)(R + G + B) / 3 / 255;
	return I;
}

//	Gen after HE, new I
void HSI::genEqualization(){
	int tempS = 0;
	MaxVaule = getMaxVaule();
	MinVaule = getMinVaule();
	for (int i = 0; i < 256; i++){
		tempS += (srcHistogram[i]) != -1 ? srcHistogram[i] : 0;
		int temp = (double)255 * ((double)tempS / (double)TotalPixel);
		HistogramEqualization[i] = temp > 255 ? 255 : temp;
	}
}

//	回傳陣列最大值
int HSI::getMaxVaule(){
	for (int i = 255; i > 0; i--){
		if (srcHistogram[i] != -1){
			return i;
		}
	}
	return 255;
}

//	回傳陣列最小值
int HSI::getMinVaule(){
	for (int i = 0; i < 256; i++){
		if (srcHistogram[i] != -1){
			return i;
		}
	}
	return 0;
}

//	回傳BGR中最小值
double HSI::getMinVaule(double B, double G, double R){
	double BGR_min;
	if (R <= G&&R <= B) BGR_min = R;
	if (G <= R&&G <= B) BGR_min = G;
	if (B <= G&&B <= R) BGR_min = B;
	return BGR_min;
}

//	replace Image1's changes brightness, and convert to RGB and save in Image2
void HSI::doEqualization(){
	Image2 = gcnew System::Drawing::Bitmap(Width_src, Height_src, System::Drawing::Imaging::PixelFormat::Format24bppRgb);
	ImageData1 = Image1->LockBits(rect, Drawing::Imaging::ImageLockMode::ReadWrite, Image1->PixelFormat);
	ImageData2 = Image2->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, Image2->PixelFormat);

	ptr = ImageData1->Scan0;
	ResultPtr = ImageData2->Scan0;

	p = (Byte*)((System::Void*)ptr);
	Res = (Byte*)((System::Void*)ResultPtr);

	double B, G, R, b, g, r, I, S, H, value1, value2, radial, BGR_min;
	for (int y = 0; y < Image1->Height; y++){
		for (int x = 0; x < Image1->Width; x++){
			B = p[ptr_bit*(x + Width_src*y) + 0];
			G = p[ptr_bit*(x + Width_src*y) + 1];
			R = p[ptr_bit*(x + Width_src*y) + 2];

			//	將BGR正規化
			B = B / 255;
			G = G / 255;
			R = R / 255;

			//	取得BGR中最小值;
			BGR_min = (double)getMinVaule(B, G, R);

			//	透過正規化後的BGR計算HSI
			I = (R + G + B) / 3;
			S = (double)(3 / ((double)(R + G + B))*(double)BGR_min);
			S = 1.0 - S;

			value1 = ((R - G) + (R - B)) * 0.5;
			value2 = pow((pow((R - G), 2) + (R - B)*(G - B)), 0.5);
			radial = value1 / value2;	// 結果為弧可直接套入三角函數

			//	if result is 1.#IND00000000, or 1.#INF00000000
			//	that mean the result is overflow
			H = acos(radial);
			H = H * 180 / PI;	//	to degree

			g = G / I;
			b = B / I;

			if (g > b){
				H = round(360.0 - H);
			}
			else{
				H = round(H);
			}

			I = (double)getEqualization(I * 255 > 255 ? 255 : I * 255) / 255;

			RGB myRGB = HSI2RGB(H, S, I);

			Res[ptr_bit*(x + Width_src*y) + 0] = myRGB.B;
			Res[ptr_bit*(x + Width_src*y) + 1] = myRGB.G;
			Res[ptr_bit*(x + Width_src*y) + 2] = myRGB.R;
		}
	}

	Image1->UnlockBits(ImageData1);
	Image2->UnlockBits(ImageData2);
}

//	H = degree, S = double, I = I * 255 
RGB HSI::HSI2RGB(double H, double S, double I){
	double b, g, r, degree;
	RGB result;
	degree = getAreaDegree(degree);

	r = (1 - S) / 3;
	g = (1 + (S*cos(degree * PI / 180)) / cos((60 - degree) * PI / 180)) / 3;
	b = 1 - (r + b);

	I *= 255;	//	轉回原本灰階值;

	result.R = round((double)(3 * I * r));
	result.R = result.R > 255 ? 255 : result.R;
	result.G = round((double)(3 * I * g));
	result.G = result.G > 255 ? 255 : result.G;
	result.B = round((double)(3 * I * b));
	result.B = result.B > 255 ? 255 : result.B;
	return result;
}

// 判斷區間
double HSI::getAreaDegree(double degree){
	if (0 < degree && degree <= 120){
		return degree;	//	RG sector
	}
	else if (120 < degree&&degree <= 240){
		degree -= 120;	//	GB sector
		return degree;
	}
	else if (240 < degree&&degree <= 360){
		degree -= 240;	//	BR sector
		return degree;
	}
}

//	轉換為均衡化後數值
int HSI::getEqualization(int index){
	return HistogramEqualization[index];
}



//	依影像通道數設定指標移動量
void HSI::setPtr_bit(System::Drawing::Imaging::PixelFormat input){
	switch (input){
	case Imaging::PixelFormat::Format24bppRgb:
		ptr_bit = 3;
		break;
	case Imaging::PixelFormat::Format32bppArgb:
		ptr_bit = 4;
		break;
	case Imaging::PixelFormat::Format32bppPArgb:
		ptr_bit = 4;
		break;
	case Imaging::PixelFormat::Format32bppRgb:
		ptr_bit = 4;
		break;
	default:
		ptr_bit = 2;
		break;
	}
}

//	Initialize Arrary
void HSI::releseArray(){
	for (int i = 0; i < 256; i++){
		srcHistogram[i] = -1;
		HistogramEqualization[i] = -1;
	}
}
