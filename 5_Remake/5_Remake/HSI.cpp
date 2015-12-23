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

#pragma region HSI::Common_function
//	Open image from filename
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
#pragma endregion

#pragma region HSI::HSI2RGB
Bitmap^ HSI::getHSIResult(System::String^ filename){
	openfile(filename);
	doHSI_Transfer();
	return Image2;
}

void HSI::doHSI_Transfer(){
	Image2 = gcnew System::Drawing::Bitmap(Width_src, Height_src, System::Drawing::Imaging::PixelFormat::Format24bppRgb);
	ImageData1 = Image1->LockBits(rect, Drawing::Imaging::ImageLockMode::ReadWrite, Image1->PixelFormat);
	ImageData2 = Image2->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, Image2->PixelFormat);

	ptr = ImageData1->Scan0;
	ResultPtr = ImageData2->Scan0;

	p = (Byte*)((System::Void*)ptr);
	Res = (Byte*)((System::Void*)ResultPtr);

	RGB RGB_input, RGB_output;
	HSI_region HSI_input;
	for (int y = 0; y < Image1->Height; y++){
		for (int x = 0; x < Image1->Width; x++){
			RGB_input.B = p[ptr_bit*(x + Width_src*y) + 0];
			RGB_input.G = p[ptr_bit*(x + Width_src*y) + 1];
			RGB_input.R = p[ptr_bit*(x + Width_src*y) + 2];

			//	將BGR正規化
			RGB_input.B = RGB_input.B / 255;
			RGB_input.G = RGB_input.G / 255;
			RGB_input.R = RGB_input.R / 255;

			HSI_input = RGBtoHSI(RGB_input);
			RGB_output = HSI2RGB(HSI_input);

			Res[ptr_bit*(x + Width_src*y) + 0] = RGB_output.B;
			Res[ptr_bit*(x + Width_src*y) + 1] = RGB_output.G;
			Res[ptr_bit*(x + Width_src*y) + 2] = RGB_output.R;

		}
	}

	Image1->UnlockBits(ImageData1);
	Image2->UnlockBits(ImageData2);
}

#pragma region HSI::Return_HSI
HSI_region HSI::RGBtoHSI(RGB input){
	HSI_region output;
	if (input.R * 255 > 255){	//	檢驗RGB是否已正規化
		input.R /= 255;
		input.G /= 255;
		input.B /= 255;
	}
	output.H = figureOutH(input);	//	return Degree
	output.S = figureOutS(input);	//	return 0~1
	output.I = figureOutI(input);	//	return 0~1
	return output;
}

//	convert RGB to HSI, return H
double HSI::figureOutH(RGB input){
	double H, value1, value2, radial;
	//	( (R - G)+(R - B) )
	value1 = (input.R - input.G) + (input.R - input.B);

	//	2 * ( (R-G)^2 + (R-B)(G-B) )^0.5
	value2 = 2 * pow((pow((input.R - input.G), 2) + (input.R - input.B)*(input.G - input.B)), 0.5);
	radial = value1 / value2;	// 結果為弧可直接套入三角函數

	//	H 介於0~360之間(角度)
	H = acos(radial);
	H = H * 180 / PI;	//	to degree
	if (input.B > input.G){
		H = round(360.0 - H);
	}
	else if (input.B == input.G){	//	修復黑色破圖區域
		H = 0;
	}
	else{
		H = round(H);
	}
	return H;
}

//	convert RGB to HSI, return S
double HSI::figureOutS(RGB input){
	if (input.R * 255 > 255){
		input.R /= 255;
		input.G /= 255;
		input.B /= 255;
	}
	double S = 0, BGR_min;
	BGR_min = getMinVaule(input);
	// S is between 0 and 1
	if ((input.R + input.G + input.B) == 0){
		S = 0.0;
	}
	else if (S > 1){
		S = 1.0;
	}
	else{
		S = (3.0 / (input.R + input.G + input.B)) * BGR_min;
		S = 1.0 - S;
	}
	return S;
}

//	convert RGB to HSI, return I
double HSI::figureOutI(RGB input){
	double I = (input.R + input.G + input.B) / 3;
	// I is between 0 and 1
	if (I < 0)
		I = 0.0;
	else if (I>1)
		I = 1.0;
	return I;
}

double HSI::getMinVaule(RGB input){
	if (input.R <= input.G&&input.R <= input.B) return input.R;
	if (input.G <= input.R&&input.G <= input.B) return input.G;
	if (input.B <= input.G&&input.B <= input.R) return input.B;
}
#pragma endregion

#pragma region HSI::Return_RGB

RGB HSI::HSI2RGB(HSI_region input){
	double b, g, r, degree, value1, value2;
	RGB result;
	Sector mySec;

	mySec = getAreaDegree(input.H);
	degree = mySec.degree;

	value1 = input.S * cos(degree * PI / 180);	//	S * Cos(H(degree))
	value2 = cos((60 - degree) * PI / 180);	//	Cos(60- H(degree))

	switch (mySec.sector){
	case 0:	//RG sector 0~120
		b = (1.0 - input.S) / 3.0;
		r = (1.0 + (value1 / value2)) / 3.0;
		g = 1.0 - (r + b);
		if (round(r + g + b) != 1)
			int rgb_add = 0;	//	(Debug用) 驗證rgb 之關係
		break;
	case 1:	//GB sector 120~240
		r = (1.0 - input.S) / 3.0;
		g = (1.0 + (value1 / value2)) / 3.0;
		b = 1.0 - (r + g);
		if (round(r + g + b) != 1)
			int rgb_add = 0;	//	(Debug用) 驗證rgb 之關係
		break;
	case 2:	//BR sector 240~360
		g = (1.0 - input.S) / 3.0;
		b = (1.0 + (value1 / value2)) / 3.0;
		r = 1.0 - (g + b);
		if (round(r + g + b) != 1)
			int rgb_add = 0;	//	(Debug用) 驗證rgb 之關係
		break;
	}

	input.I *= 255;	//	轉回原本灰階值;

	result.R = round((double)(3.0 * input.I * r));
	result.R = result.R > 255 ? 255 : result.R;
	result.R = result.R < 0 ? 0 : result.R;

	result.G = round((double)(3.0 * input.I * g));
	result.G = result.G > 255 ? 255 : result.G;
	result.G = result.G < 0 ? 0 : result.G;

	result.B = round((double)(3.0 * input.I * b));
	result.B = result.B > 255 ? 255 : result.B;
	result.B = result.B < 0 ? 0 : result.B;

	return result;
}

Sector HSI::getAreaDegree(double degree){
	Sector mysec;
	if (0 == degree || (0 < degree && degree <= 120)){
		mysec.degree = degree;
		mysec.sector = 0;	//	RG sector
	}
	else if (120 < degree && degree <= 240){
		degree -= 120.0;
		mysec.degree = degree;
		mysec.sector = 1;	//	GB sector
	}
	else if (240 < degree&&degree <= 360){
		degree -= 240.0;
		mysec.degree = degree;
		mysec.sector = 2;	//	BR sector
	}
	return mysec;
}
#pragma endregion

#pragma endregion

#pragma region HSI::doHEwithHSI

//	Initialize Arrary
void HSI::releseArray(){
	for (int i = 0; i < 256; i++){
		srcHistogram[i] = -1;
		HistogramEqualization[i] = -1;
	}
}

Bitmap^ HSI::getHEResult(System::String^ filename){
	openfile(filename);
	genSrcHistogram();
	genEqualization();
	doEqualization();
	return Image2;
}

//	Gen SrcHistogram with I
void HSI::genSrcHistogram(){
	ImageData1 = Image1->LockBits(rect, Drawing::Imaging::ImageLockMode::ReadWrite, Image1->PixelFormat);
	ptr = ImageData1->Scan0;
	p = (Byte*)((System::Void*)ptr);
	double B, G, R, I, S, H;
	RGB input;
	for (int y = 0; y < Image1->Height; y++){
		for (int x = 0; x < Image1->Width; x++){
			input.B = p[ptr_bit*(x + Width_src*y) + 0];
			input.G = p[ptr_bit*(x + Width_src*y) + 1];
			input.R = p[ptr_bit*(x + Width_src*y) + 2];

			input.R /= 255;
			input.G /= 255;
			input.B /= 255;

			setSrcHistogramWithI(figureOutI(input));
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

//	轉換為均衡化後數值
int HSI::getEqualization(double index){
	index = round(index * 255);
	return HistogramEqualization[(int)index > 255 ? 255 : (int)index];
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

	RGB input, output;
	HSI_region input_HSI;
	for (int y = 0; y < Image1->Height; y++){
		for (int x = 0; x < Image1->Width; x++){
			input.B = p[ptr_bit*(x + Width_src*y) + 0];
			input.G = p[ptr_bit*(x + Width_src*y) + 1];
			input.R = p[ptr_bit*(x + Width_src*y) + 2];

			//	將BGR正規化
			input.B /= 255;
			input.G /= 255;
			input.R /= 255;

			//	透過正規化後的BGR計算HSI
			input_HSI.I = figureOutI(input);
			input_HSI.S = figureOutS(input);
			input_HSI.H = figureOutH(input);

			input_HSI.I = getEqualization(input_HSI.I) / 255.0;

			output = HSI2RGB(input_HSI);
			
			Res[ptr_bit*(x + Width_src*y) + 0] = output.B;
			Res[ptr_bit*(x + Width_src*y) + 1] = output.G;
			Res[ptr_bit*(x + Width_src*y) + 2] = output.R;

		}
	}

	Image1->UnlockBits(ImageData1);
	Image2->UnlockBits(ImageData2);
}
#pragma endregion