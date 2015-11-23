#include "stdafx.h"
#include "HistogramClass.h"

using namespace System;

HistogramClass::HistogramClass(System::String^ fileName)
{
	// 初始化陣列
	srcHistogram = gcnew array<int>(256);
	resHistogram = gcnew array<int>(256);
	HistogramEqualization = gcnew array<int>(256);
	releseArray();
	openPic(fileName);
	HistogramIsFinish = false;
	isSource = true;

	setHistoVaule(isSource);
}

void HistogramClass::openPic(System::String^ fileName){
	this->Image1 = safe_cast<System::Drawing::Bitmap^>(System::Drawing::Image::FromFile(fileName));	//將選取的檔案讀取並且存至Image1			
	this->rect = System::Drawing::Rectangle(0, 0, this->Image1->Width, this->Image1->Height);	//設定rect範圍大小

	this->Width_src = this->Image1->Width;
	this->Height_src = this->Image1->Height;
	this->TotalPixel = this->Width_src*this->Height_src;

};
void HistogramClass::reOpen(System::String^ fileName){
	this->openPic(fileName);
}
void HistogramClass::setHistoVaule(bool isSource){
	releseArray();
	if (isSource){
		ImageData1 = Image1->LockBits(rect, Drawing::Imaging::ImageLockMode::ReadWrite, Image1->PixelFormat);
		ptr = ImageData1->Scan0;
		p = (Byte*)((System::Void*)ptr);

		for (int y = 0; y < Image1->Height; y++){
			for (int x = 0; x < Image1->Width; x++){
				// 計算灰階值(計算HSI的Y)
				int pixel = (p[0] + p[1] + p[2]) / 3;
				// 填入直方圖陣列
				if (HistogramIsFinish){
					for (int i = 0; i < 256; i++)
						srcHistogram[i] = -1;
					srcHistogram[pixel]++;
				}
				if (srcHistogram[pixel] == -1)
					srcHistogram[pixel] = 0;
				srcHistogram[pixel]++;

				// 像素值填入
				p[0] = (Byte)pixel;	//填入像素值 channel 0 (Blue)
				p[1] = (Byte)pixel;	//填入像素值 channel 1 (Green)
				p[2] = (Byte)pixel;	//填入像素值 channel 2 (Red)

				// 指到下一個像素資訊
				p += ptr_bit;
			}
		}
		Image1->UnlockBits(ImageData1);
	}
	else{
		rect = System::Drawing::Rectangle(0, 0, Width_src, Height_src);
		ImageData2 = Image2->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, Image2->PixelFormat);

		ResultPtr = ImageData2->Scan0;
		R = (Byte*)((System::Void*)ResultPtr);

		for (int y = 0; y < Image2->Height; y++){
			for (int x = 0; x < Image2->Width; x++){
				// 計算灰階值(計算HSI的Y)
				int pixel = R[0];

				// 填入直方圖陣列
				if (HistogramIsFinish){
					for (int i = 0; i < 256; i++)
						resHistogram[i] = -1;
					resHistogram[pixel]++;
				}
				if (resHistogram[pixel] == -1)
					resHistogram[pixel] = 0;
				resHistogram[pixel]++;
				R += ptr_bit2;
			}
		}
		Image2->UnlockBits(ImageData2);
	}
}

void HistogramClass::setHistoFinish(){
	HistogramIsFinish = true;
}

void HistogramClass::doEqualization(){
	int tempS = 0;
	MaxVaule = getMaxVaule();
	MinVaule = getMinVaule();
	for (int i = 0; i < 256; i++){
		tempS += (srcHistogram[i]) != -1 ? srcHistogram[i] : 0;
		int temp = std::round((double)255 * ((double)tempS / (double)TotalPixel));
		HistogramEqualization[i] = temp > 255 ? 255 : temp;
	}
}

int HistogramClass::getEqualization(int index){
	return HistogramEqualization[index];
}

void HistogramClass::setResultImage(){
	Image2 = gcnew System::Drawing::Bitmap(Width_src, Height_src, System::Drawing::Imaging::PixelFormat::Format24bppRgb);
	ImageData1 = Image1->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, Image1->PixelFormat);
	ImageData2 = Image2->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, Image2->PixelFormat);

	ptr = ImageData1->Scan0;
	IntPtr ptr2 = ImageData2->Scan0;
	p = (Byte*)((System::Void*)ptr);
	R = (Byte*)((System::Void*)ptr2);

	for (int y = 0; y < Image2->Height; y++){
		for (int x = 0; x < Image2->Width; x++){

			// 取得均衡化後像素值
			int pixel = this->getEqualization(p[0]);

			// 像素值填入
			R[0] = (Byte)pixel;	//填入像素值 channel 0 (Blue)
			R[1] = (Byte)pixel;	//填入像素值 channel 1 (Green)
			R[2] = (Byte)pixel;	//填入像素值 channel 2 (Red)

			p += ptr_bit;
			R += ptr_bit2;
		}
	}
	Image1->UnlockBits(ImageData1);
	Image2->UnlockBits(ImageData2);
}

int HistogramClass::getHistogramVaule(int index, int isSource){
	if (isSource)
		return srcHistogram[index];
	else
		return resHistogram[index];
}

int HistogramClass::getMaxVaule(){
	for (int i = 255; i > 0; i--){
		if (srcHistogram[i] != -1){
			return i;
		}
	}
	return 255;
}

int HistogramClass::getMinVaule(){
	for (int i = 0; i < 256; i++){
		if (srcHistogram[i] != -1){
			return i;
		}
	}
	return 0;
}

System::Drawing::Bitmap^ HistogramClass::getEqualizationResult(){
	isSource = true;
	setHistoVaule(isSource);
	doEqualization();
	setResultImage();
	isSource = false;
	setHistoVaule(isSource);

	return Image2;
}

void HistogramClass::releseArray(){
	for (int i = 0; i < 256; i++){
		srcHistogram[i] = -1;
		resHistogram[i] = -1;
		HistogramEqualization[i] = -1;
	}	
}