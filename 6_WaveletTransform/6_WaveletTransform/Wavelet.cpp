#include "stdafx.h"
#include "Wavelet.h"

using namespace System;
using namespace System::Drawing;

Wavelet::Wavelet()
{
	negative = -1;
}

#pragma region Common_function

//	Open image in this class
void Wavelet::openfile(System::String^ filename){
	this->Image1 = safe_cast<System::Drawing::Bitmap^>(System::Drawing::Image::FromFile(filename));	//將選取的檔案讀取並且存至Image1			
	setPtr_bit(Image1->PixelFormat);
	this->rect = System::Drawing::Rectangle(0, 0, this->Image1->Width, this->Image1->Height);	//設定rect範圍大小
	this->Width_src = this->Image1->Width;
	this->Height_src = this->Image1->Height;
	this->TotalPixel = this->Width_src*this->Height_src;
}

//	依影像通道數設定指標移動量
void Wavelet::setPtr_bit(System::Drawing::Imaging::PixelFormat input){
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

#pragma region Wavelet::doWavelet

Bitmap^ Wavelet::getWaveletResult(System::String^ filename){
	openfile(filename);
	doWavelet();
	return Image2;
}

void Wavelet::doWavelet(){
	imageSize input;
	input.Height = Height_src;
	input.Width = Width_src;
	//	First - Source size
	figureOutLH(input);

	//	Second - Half of Source 
	input.Height /= 2;
	input.Width /= 2;
	//figureOutLH(input);

	//	Third - Quarter of Source
	//input.Height /= 2;
	//input.Width /= 2;
	//figureOutLH(input);

}


void Wavelet::figureOutLH_Row(imageSize input){
	int B, G, R, gray, value1, value2, output, halfWidth;
	halfWidth = input.Width / 2;
#pragma region LH1_ROW
	for (int y = 0; y < Height_src; y++){
		//L1-ROW
		for (int x = 0; x < Width_src; x++){
			if (x + 1 < Width_src&&y + 1 < Height_src){
				if (x < input.Width&&y < input.Height){
					value1 = p[ptr_bit*(x * 2 + Width_src*y) + 0];
					value2 = p[ptr_bit*(x * 2 + Width_src*y) + 3];
					//	if isH, output = (value1-value2)/2
					if (x >= halfWidth){
						output = (value1 + (negative*value2)) / 2;
					}
					else{
						output = (value1 + value2) / 2;
					}
				}
				else{
					output = p[ptr_bit*(x + Width_src*y * 2) + 0];
				}
				Res[ptr_bit*(x + Width_src*y) + 0] = output;
				Res[ptr_bit*(x + Width_src*y) + 1] = output;
				Res[ptr_bit*(x + Width_src*y) + 2] = output;
			}
		}
	}
#pragma endregion 
}

void Wavelet::figureOutLH_Col(imageSize input){
	int B, G, R, gray, value1, value2, output, halfHeight;
	halfHeight = input.Height / 2;
#pragma region LH1_COL
	for (int y = 0; y < Height_src; y++){
		//L1-Col
		for (int x = 0; x < Width_src; x++){
			if ((y + 1 < Height_src) && (x + 1 < Width_src)){
				if (x + 1 < input.Width&&y + 2 < input.Height){
					value1 = p[ptr_bit*(x + Width_src*(y)) + 0];
					value2 = p[ptr_bit*(x + Width_src*(y + 1)) + 0];
					//	if isH, output = (value1-value2)/2
					if (y >= halfHeight){
						output = (value1 + (negative*value2)) / 2;
					}
					else{
						output = (value1 + value2) / 2;
					}
				}
				else{
					output = p[ptr_bit*(x + Width_src*y) + 0];
				}
				Res[ptr_bit*(x + Width_src*y) + 0] = output;
				Res[ptr_bit*(x + Width_src*y) + 1] = output;
				Res[ptr_bit*(x + Width_src*y) + 2] = output;
			}
		}
	}
#pragma endregion 
}

void Wavelet::figureOutLH(imageSize input){
	Image2 = gcnew System::Drawing::Bitmap(Width_src, Height_src, System::Drawing::Imaging::PixelFormat::Format24bppRgb);
	ImageData1 = Image1->LockBits(rect, Drawing::Imaging::ImageLockMode::ReadWrite, Image1->PixelFormat);
	ImageData2 = Image2->LockBits(rect, Drawing::Imaging::ImageLockMode::ReadWrite, Image2->PixelFormat);

	ptr = ImageData1->Scan0;
	ResultPtr = ImageData2->Scan0;

	p = (Byte*)((System::Void*)ptr);
	Res = (Byte*)((System::Void*)ResultPtr);

	figureOutLH_Row(input);

	Image1->UnlockBits(ImageData1);
	Image2->UnlockBits(ImageData2);

	Image1 = Image2;

	Image2 = gcnew System::Drawing::Bitmap(Width_src, Height_src, System::Drawing::Imaging::PixelFormat::Format24bppRgb);
	ImageData1 = Image1->LockBits(rect, Drawing::Imaging::ImageLockMode::ReadWrite, Image1->PixelFormat);
	ImageData2 = Image2->LockBits(rect, Drawing::Imaging::ImageLockMode::ReadWrite, Image2->PixelFormat);
	ptr = ImageData1->Scan0;
	ResultPtr = ImageData2->Scan0;

	p = (Byte*)((System::Void*)ptr);
	Res = (Byte*)((System::Void*)ResultPtr);

	figureOutLH_Col(input);

	Image1->UnlockBits(ImageData1);
	Image2->UnlockBits(ImageData2);
}

#pragma endregion

int RGB2Gray(int R, int G, int B){
	return (R + G + B) / 3;
}