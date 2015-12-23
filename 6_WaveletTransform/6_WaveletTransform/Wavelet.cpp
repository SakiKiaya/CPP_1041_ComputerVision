#include "stdafx.h"
#include "Wavelet.h"


Wavelet::Wavelet()
{
}

#pragma region Common_function

//	Open image in this class
void Wavelet::openfile(System::String^ filename){
	this->Image1 = safe_cast<System::Drawing::Bitmap^>(System::Drawing::Image::FromFile(filename));	//�N������ɮ�Ū���åB�s��Image1			
	setPtr_bit(Image1->PixelFormat);
	this->rect = System::Drawing::Rectangle(0, 0, this->Image1->Width, this->Image1->Height);	//�]�wrect�d��j�p
	this->Width_src = this->Image1->Width;
	this->Height_src = this->Image1->Height;
	this->TotalPixel = this->Width_src*this->Height_src;
}

//	�̼v���q�D�Ƴ]�w���в��ʶq
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
	//
	/*	TODO : Wavelet mothed*/
	//
}

void doFirst(){

}

#pragma endregion