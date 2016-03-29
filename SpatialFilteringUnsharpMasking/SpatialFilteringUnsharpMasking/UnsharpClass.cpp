#include "stdafx.h"
#include "UnsharpClass.h"

using namespace System;

UnsharpClass::UnsharpClass(System::String^ fileName_in)
{
	// 初始化陣列
	srcHistogram = gcnew array<int>(256);
	resHistogram = gcnew array<int>(256);
	HistogramEqualization = gcnew array<int>(256);
	releseArray();
	fileName = fileName_in;
	this->openPic(fileName);
	HistogramIsFinish = false;
	isSource = true;
	setHistoVaule(isSource);
}

void UnsharpClass::openPic(System::String^ fileName_in){
	this->Image1 = safe_cast<System::Drawing::Bitmap^>(System::Drawing::Image::FromFile(fileName));	//將選取的檔案讀取並且存至Image1			
	this->rect = System::Drawing::Rectangle(0, 0, this->Image1->Width, this->Image1->Height);	//設定rect範圍大小

	this->Width_src = this->Image1->Width;
	this->Height_src = this->Image1->Height;
	this->TotalPixel = this->Width_src*this->Height_src;
	this->Image1_size = TotalPixel;
}

System::Drawing::Bitmap^ UnsharpClass::getUnsharpMasking(int S_Max){
	this->doUnsharpMasking(S_Max);	// Result is Image1

	return Image2;
}

void UnsharpClass::reOpen(System::String^ fileName_in){
	this->openPic(fileName_in);
}

void UnsharpClass::doUnsharpMasking(int S_Max){
	this->doLowpassFilter(0);	// Result is Image2

	this->doHistogramShrink(S_Max);		// Result is Image2

	this->doPixelDiff();				// Result is Image2

	this->doEqualization();			// Result is Image2

	isSource = false;
	this->setHistoVaule(isSource);	// Show Image2's Histogram
}

/* Lowpass source is Image1, Result to Image2 */
#pragma region doLowpassFilter
void UnsharpClass::doLowpassFilter(int level){
	setKernel(level);

	Image2 = gcnew System::Drawing::Bitmap(Width_src, Height_src, System::Drawing::Imaging::PixelFormat::Format24bppRgb);
	rect = System::Drawing::Rectangle(0, 0, Width_src, Height_src);
	ImageData1 = Image1->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, Image1->PixelFormat);
	ImageData2 = Image2->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, Image2->PixelFormat);

	ResultPtr = ImageData2->Scan0;
	ptr = ImageData1->Scan0;
	R = (System::Byte*)(ResultPtr.ToPointer());
	p = (System::Byte*)(ptr.ToPointer());

	for (int y = 0; y < Height_src; y++){
		for (int x = 0; x < Width_src; x++){
			if (x != 0 && y != 0 && x != Width_src-1 && y != Height_src-1){			// If is not edge
				for (int i = 0; i < 3; i++){
					std::vector<int> pixelTemp(9);
					pixelTemp[0] = kernel[0] * p[ptr_bit*((x - 1) + Width_src*(y - 1)) + i];		// Inside of kernel all of pixel were multiplied by kernel's weight
					pixelTemp[1] = kernel[1] * p[ptr_bit*(x + Width_src*(y - 1)) + i];
					pixelTemp[2] = kernel[2] * p[ptr_bit*((x + 1) + Width_src*(y - 1)) + i];

					pixelTemp[3] = kernel[3] * p[ptr_bit*((x - 1) + Width_src*y) + i];
					pixelTemp[4] = kernel[4] * p[ptr_bit*(x + Width_src*y) + i];
					pixelTemp[5] = kernel[5] * p[ptr_bit*((x + 1) + Width_src*y) + i];

					pixelTemp[6] = kernel[6] * p[ptr_bit*((x - 1) + Width_src*(y + 1)) + i];
					pixelTemp[7] = kernel[7] * p[ptr_bit*(x + Width_src*(y + 1)) + i];
					pixelTemp[8] = kernel[8] * p[ptr_bit*((x + 1) + Width_src*(y + 1)) + i];

					int pixelSum = 0;				// set pixelsum zero for sum temp
					for (int j = 0; j < 9; j++)
						pixelSum += pixelTemp[j];	// Add all of the multiplied by weight vaule to pixelsum

					R[3 * (x + Width_src*y) + i] = round(pixelSum / kernelTemp)>255 ? 255 : round(pixelSum / kernelTemp);	// (kernel vaule sum)/(sum  of the weight)
				}
			}
			else {		// If is edge 
				R[3 * (x + Width_src*y) + 0] = p[3 * (x + Width_src*y) + 0];
				R[3 * (x + Width_src*y) + 1] = p[3 * (x + Width_src*y) + 1];
				R[3 * (x + Width_src*y) + 2] = p[3 * (x + Width_src*y) + 2];
			}
		}
	}

	// Unlock處理完畢的像素範圍
	Image2->UnlockBits(ImageData2);
	Image1->UnlockBits(ImageData1);
}

// set kernel weight
void UnsharpClass::setKernel(int level){
	this->kernelTemp = 9;
	this->kernel = new int[kernelTemp];
	switch (level){
	case 0:			// 3x3	9
		for (int i = 0; i < 9; i++)
			kernel[i] = 1;
		kernelTemp = 9;
		break;
	case 1:			// 3x3	10
		for (int i = 0; i < 9; i++){
			kernel[i] = 1;
		}
		kernel[4] = 2;
		kernelTemp = 10;
		break;
	case 2:			// 3x3	16
		kernel = new int[9]{ 2, 1, 2, 1, 4, 1, 2, 1, 2 };
		kernelTemp = 16;
		break;
	}
}
#pragma endregion

/* do Histogram Shrink source is Image2, Result is Image2 */
/* if S_Min is 0, and S_Max >= 30 */
void UnsharpClass::doHistogramShrink(int S_Max){
	isSource = false;
	this->setHistoVaule(isSource);
	double S_Min = 0;
	
	ImageData2 = Image2->LockBits(rect, Drawing::Imaging::ImageLockMode::ReadWrite, Image2->PixelFormat);
	ptr = ImageData2->Scan0;
	p = (Byte*)((System::Void*)ptr);

	for (int y = 0; y < Image2->Height; y++){
		for (int x = 0; x < Image2->Width; x++){
			/* S(x,y) = (( S_Max - S_Min ) / 255 ) * r(x,y) + S_min */
			int pixel = round(((double)(S_Max - S_Min) / 255.0) * (double)p[0] + S_Min);
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
	Image2->UnlockBits(ImageData2);
}

/* doPixelDiff (alpha-beta) alpha is Image1 reOpen, beta is Image2*/
/* Result is Image2*/
void UnsharpClass::doPixelDiff(){
	this->reOpen(fileName);		// reOpen the original image to Image1

	ImageData1 = Image1->LockBits(rect, Drawing::Imaging::ImageLockMode::ReadWrite, Image1->PixelFormat);
	ImageData2 = Image2->LockBits(rect, Drawing::Imaging::ImageLockMode::ReadWrite, Image2->PixelFormat);
	ptr = ImageData1->Scan0;
	IntPtr ptr2 = ImageData2->Scan0;
	p = (Byte*)((System::Void*)ptr);	// p = alpha
	R = (Byte*)((System::Void*)ptr2);	// R = beta
	for (int y = 0; y < Image1->Height; y++){
		for (int x = 0; x < Image1->Width; x++){
			int pixel = p[0] - (R[0]+R[1]+R[2])/3;	// diff
			// 像素值填入
			R[0] = (Byte)pixel>0 ? (Byte)pixel : 0;	//填入像素值 channel 0 (Blue)
			R[1] = (Byte)pixel>0 ? (Byte)pixel : 0;	//填入像素值 channel 1 (Green)
			R[2] = (Byte)pixel>0 ? (Byte)pixel : 0;	//填入像素值 channel 2 (Red)

			// 指到下一個像素資訊
			p += ptr_bit;
			R += ptr_bit;
		}
	}
	Image1->UnlockBits(ImageData1);
	Image2->UnlockBits(ImageData2);
}


/* Equalization source is Image1, Result to Image1 */
#pragma region doEqualization
void UnsharpClass::setHistoVaule(bool isSource){
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

void UnsharpClass::setHistoFinish(){
	HistogramIsFinish = true;
}

/* Result is Image2 */
void UnsharpClass::doEqualization(){
	isSource = false;
	setHistoVaule(isSource);

	int tempS = 0;
	MaxVaule = getMaxVaule();
	MinVaule = getMinVaule();
	if (isSource){
		for (int i = 0; i < 256; i++){
			tempS += (srcHistogram[i]) != -1 ? srcHistogram[i] : 0;
			int temp = std::round((double)255 * ((double)tempS / (double)TotalPixel));
			HistogramEqualization[i] = temp > 255 ? 255 : temp;
		}
	}
	else{
		for (int i = 0; i < 256; i++){
			tempS += (resHistogram[i]) != -1 ? resHistogram[i] : 0;
			int temp = std::round((double)255 * ((double)tempS / (double)TotalPixel));
			HistogramEqualization[i] = temp > 255 ? 255 : temp;
		}
	}
	setEqualizationResultImage();
}

int UnsharpClass::getEqualization(int index){
	return HistogramEqualization[index];
}

/* Source is Image2, Result is Image1 */
void UnsharpClass::setEqualizationResultImage(){
	//Image1 = gcnew System::Drawing::Bitmap(Width_src, Height_src, System::Drawing::Imaging::PixelFormat::Format24bppRgb);
	//ImageData1 = Image1->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, Image1->PixelFormat);
	ImageData2 = Image2->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, Image2->PixelFormat);

	//ptr = ImageData1->Scan0;		// Image1
	IntPtr ptr2 = ImageData2->Scan0;// Image2
	//p = (Byte*)((System::Void*)ptr);
	R = (Byte*)((System::Void*)ptr2);

	for (int y = 0; y < Image2->Height; y++){
		for (int x = 0; x < Image2->Width; x++){

			// 取得均衡化後像素值
			int pixel = this->getEqualization(R[0]);

			// 像素值填入
			R[0] = (Byte)pixel;	//填入像素值 channel 0 (Blue)
			R[1] = (Byte)pixel;	//填入像素值 channel 1 (Green)
			R[2] = (Byte)pixel;	//填入像素值 channel 2 (Red)

			R += ptr_bit;
			//R += ptr_bit2;
		}
	}
	//Image1->UnlockBits(ImageData1);
	Image2->UnlockBits(ImageData2);
}

int UnsharpClass::getHistogramVaule(int index, int isSource){
	if (isSource)
		return srcHistogram[index];
	else
		return resHistogram[index];
}

int UnsharpClass::getMaxVaule(){
	for (int i = 255; i > 0; i--){
		if (srcHistogram[i] != -1){
			return i;
		}
	}
	return 255;
}

int UnsharpClass::getMinVaule(){
	for (int i = 0; i < 256; i++){
		if (srcHistogram[i] != -1){
			return i;
		}
	}
	return 0;
}

void UnsharpClass::releseArray(){
	for (int i = 0; i < 256; i++){
		srcHistogram[i] = -1;
		resHistogram[i] = -1;
		HistogramEqualization[i] = -1;
	}
}

#pragma endregion
