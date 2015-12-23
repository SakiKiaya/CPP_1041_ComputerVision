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

			R /= 255;
			G /= 255;
			B /= 255;

			setSrcHistogramWithI(figureOutI(B, G, R));
		}
	}
	Image1->UnlockBits(ImageData1);
}

//	Save I to srcHistogram arrary
void HSI::setSrcHistogramWithI(double I){
	int pixel;
	I = round(I * 255);	//	convert I to gray 0~255 level

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
double HSI::figureOutI(double B, double G, double R){
	double I = (R + G + B) / 3;
	if (I < 0)
		I = 0.0;
	else if (I>1)
		I = 1.0;
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
			//	I 介於0~1之間
			I = figureOutI(B, G, R);

			//	S 介於0~1之間
			S = (3.0 / (R + G + B)) * BGR_min;
			S = 1.0 - S;
			if ((R + G + B) == 0)
				S = 0.0;
			else if (S > 1)
				S = 1.0;
			//	1/2 * ( (R - G)+(R - B) )
			value1 = ((R - G) + (R - B)) * 0.5;

			//	( (R-G)^2 + (R-B)(G-B) )^0.5
			value2 = pow((pow((R - G), 2) + (R - B)*(G - B)), 0.5);
			radial = value1 / value2;	// 結果為弧可直接套入三角函數

			//	if result is 1.#IND00000000, or 1.#INF00000000
			//	that mean the result is overflow
			//	H 介於0~360之間(角度)
			H = acos(radial);
			H = H * 180 / PI;	//	to degree
			if (B > G){
				H = round(360.0 - H);
			}
			else if(B == G){
				H = 0;
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
	double b, g, r, degree, value1, value2;
	RGB result;
	Sector mySec;

	mySec = getAreaDegree(H);
	degree = mySec.degree;

	value1 = S * cos(degree * PI / 180);	//	S * Cos(H(degree))
	value2 = cos((60 - degree) * PI / 180);	//	Cos(60- H(degree))

	switch (mySec.sector){
	case 0:	//RG sector 0~120
		b = (1.0 - S) / 3.0;
		r = (1.0 + (value1 / value2)) / 3.0;
		g = 1.0 - (r + b);
		if (round(r + g + b) != 1)
			int rgb_add = 0;
		break;
	case 1:	//GB sector 120~240
		r = (1.0 - S) / 3.0;
		g = (1.0 + (value1 / value2)) / 3.0;
		b = 1.0 - (r + g);
		if (round(r + g + b) != 1)
			int rgb_add = 0;
		break;
	case 2:	//BR sector 240~360
		g = (1.0 - S) / 3.0;
		b = (1.0 + (value1 / value2)) / 3.0;
		r = 1.0 - (g + b);
		if (round(r + g + b) != 1)
			int rgb_add = 0;
		break;
	}


	I *= 255;	//	轉回原本灰階值;

	result.R = round((double)(3.0 * I * r));
	result.R = result.R > 255 ? 255 : result.R;
	result.R = result.R < 0 ? 0 : result.R;

	result.G = round((double)(3.0 * I * g));
	result.G = result.G > 255 ? 255 : result.G;
	result.G = result.G < 0 ? 0 : result.G;

	result.B = round((double)(3.0 * I * b));
	result.B = result.B > 255 ? 255 : result.B;
	result.R = result.R < 0 ? 0 : result.R;
	return result;
}

// 判斷區間
Sector HSI::getAreaDegree(double degree){
	Sector mysec;
	if (0 <= degree && degree <= 120){
		mysec.degree = degree;
		mysec.sector = 0;	//	RG sector
	}
	else if (120 < degree&&degree <= 240){
		degree -= 120;
		mysec.degree = degree;
		mysec.sector = 1;	//	GB sector
	}
	else if (240 < degree&&degree <= 360){
		degree -= 240;
		mysec.degree = degree;
		mysec.sector = 2;	//	BR sector
	}
	return mysec;
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
