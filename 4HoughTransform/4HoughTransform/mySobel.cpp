#include "stdafx.h"
#include "mySobel.h"

mySobel::mySobel(double input)
{
	this->setThreshold(input);
	this->setKernel();
	this->pi = 4 * atan(1.0);
	this->pixelTemp = new int[9];
}

System::Drawing::Bitmap^ mySobel::getSobelResult(System::String^ fileName_in){
	if (this->source == nullptr){
		this->openPic(fileName_in);
	}
	else{
		this->reOpen(fileName_in);
	}
	this->doSobel();
	return result;
}

System::Drawing::Bitmap^ mySobel::getdoX(){
	return doX;
}

System::Drawing::Bitmap^ mySobel::getdoY(){
	return doY;
}

void mySobel::openPic(System::String^ fileName){
	this->source = safe_cast<System::Drawing::Bitmap^>(System::Drawing::Image::FromFile(fileName));	//將選取的檔案讀取並且存至Image1			
	this->rect = System::Drawing::Rectangle(0, 0, this->source->Width, this->source->Height);	//設定rect範圍大小

	this->Width_src = this->source->Width;
	this->Height_src = this->source->Height;
	this->imageSize = this->Width_src*this->Height_src;

	this->result = gcnew System::Drawing::Bitmap(Width_src, Height_src,
		System::Drawing::Imaging::PixelFormat::Format24bppRgb);
	this->doX = gcnew System::Drawing::Bitmap(Width_src, Height_src,
		System::Drawing::Imaging::PixelFormat::Format24bppRgb);
	this->doY = gcnew System::Drawing::Bitmap(Width_src, Height_src,
		System::Drawing::Imaging::PixelFormat::Format24bppRgb);
}

void mySobel::reOpen(System::String^ fileName){
	this->openPic(fileName);
}

void mySobel::doSobel(){
	this->ImageData1 = source->LockBits(rect,
		System::Drawing::Imaging::ImageLockMode::ReadWrite, source->PixelFormat);
	this->ImageData2 = result->LockBits(rect,
		System::Drawing::Imaging::ImageLockMode::ReadWrite, result->PixelFormat);
	this->ImageDataX = doX->LockBits(rect,
		System::Drawing::Imaging::ImageLockMode::ReadWrite, doX->PixelFormat);
	this->ImageDataY = doY->LockBits(rect,
		System::Drawing::Imaging::ImageLockMode::ReadWrite, doY->PixelFormat);

	ptr = ImageData1->Scan0;
	ptr_Result = ImageData2->Scan0;
	ptr_x = ImageDataX->Scan0;
	ptr_y = ImageDataY->Scan0;

	p = (System::Byte*)((System::Void*)ptr);
	R = (System::Byte*)((System::Void*)ptr_Result) + ptr_bit;
	p_x = (System::Byte*)((System::Void*)ptr_x) + ptr_bit;
	p_y = (System::Byte*)((System::Void*)ptr_y) + ptr_bit;

	for (int y = 0; y < Height_src; y++){
		for (int x = 0; x < Width_src; x++){
			if (x != 0 && y != 0 && x != Width_src - 1 && y != Height_src - 1)
			{
				int i = 0;
				pixelTemp[0] = p[ptr_bit*((x - 1) + Width_src*(y - 1)) + i];
				pixelTemp[1] = p[ptr_bit*(x + Width_src*(y - 1)) + i];
				pixelTemp[2] = p[ptr_bit*((x + 1) + Width_src*(y - 1)) + i];

				pixelTemp[3] = p[ptr_bit*((x - 1) + Width_src*y) + i];
				pixelTemp[4] = p[ptr_bit*(x + Width_src*y) + i];
				pixelTemp[5] = p[ptr_bit*((x + 1) + Width_src*y) + i];

				pixelTemp[6] = p[ptr_bit*((x - 1) + Width_src*(y + 1)) + i];
				pixelTemp[7] = p[ptr_bit*(x + Width_src*(y + 1)) + i];
				pixelTemp[8] = p[ptr_bit*((x + 1) + Width_src*(y + 1)) + i];

				int sum_x = this->addAll(pixelTemp, true);
				int sum_y = this->addAll(pixelTemp, false);
				int sum_result;

				if (sum_x > threshold)
					sum_x = 255;
				else
					sum_x = 0;
				if (sum_y > threshold)
					sum_y = 255;
				else
					sum_y = 0;
				p_x[ptr_bit*(x + Width_src*y) + 0] = sum_x;	//填入像素值 channel 0 (Blue)
				p_x[ptr_bit*(x + Width_src*y) + 1] = sum_x;	//填入像素值 channel 1 (Green)
				p_x[ptr_bit*(x + Width_src*y) + 2] = sum_x;	//填入像素值 channel 2 (Red)

				p_y[ptr_bit*(x + Width_src*y) + 0] = sum_y;	//填入像素值 channel 0 (Blue)
				p_y[ptr_bit*(x + Width_src*y) + 1] = sum_y;	//填入像素值 channel 1 (Green)
				p_y[ptr_bit*(x + Width_src*y) + 2] = sum_y;	//填入像素值 channel 2 (Red)

				if (sum_x == 255 || sum_y == 255)
					sum_result = 255;
				else
					sum_result = 0;
				R[ptr_bit*(x + Width_src*y) + 0] = sum_result;
				R[ptr_bit*(x + Width_src*y) + 1] = sum_result;
				R[ptr_bit*(x + Width_src*y) + 2] = sum_result;
			}
		}
	}
	source->UnlockBits(ImageData1);
	result->UnlockBits(ImageData2);
	doX->UnlockBits(ImageDataX);
	doY->UnlockBits(ImageDataY);
}

void mySobel::setKernel(){
	this->maskX = new int[9]{ -1, -2, -1, 0, 0, 0, 1, 2, 1 };
	this->maskY = new int[9]{ -1, 0, 1, -2, 0, 2, -1, 0, 1 };
}

void mySobel::setThreshold(double threshold_in){
	this->threshold = threshold_in;
}

/* Pseudo-convolution kernels used to quickly compute approximate gradient magnitude.
	Input mask_in is 3x3 kernel.
	If want to do X, give true, if want to do Y, give another.
	Return result is int for approximate gradient magnitude.
	*/
int mySobel::addAll(int *mask_in, bool isX){
	int result = 0;
	if (isX){
		for (int i = 0; i < 9; i++){
			result += mask_in[i] * this->maskX[i];
		}
	}
	else{
		for (int i = 0; i < 9; i++){
			result += mask_in[i] * this->maskY[i];
		}
	}
	return abs(result);	// return abs of sum
}

System::Drawing::Bitmap^ mySobel::getHoughTransform(int threshold){
	this->quantization = gcnew System::Drawing::Bitmap(
		180, 2 * sqrt(Width_src*Width_src + Height_src*Height_src),
		System::Drawing::Imaging::PixelFormat::Format24bppRgb);

	this->quan_size = this->quantization->Width*this->quantization->Height;
	this->quan_Height = round(sqrt(Width_src*Width_src + Height_src*Height_src));

	this->quan_rect = System::Drawing::Rectangle(0, 0, 180, (int)round(2 * sqrt(Width_src*Width_src + Height_src*Height_src)));	//設定rect範圍大小

	this->ImageData1 = result->LockBits(rect,
		System::Drawing::Imaging::ImageLockMode::ReadWrite, result->PixelFormat);
	this->ImageData2 = quantization->LockBits(quan_rect,
		System::Drawing::Imaging::ImageLockMode::ReadWrite, quantization->PixelFormat);

	ptr = ImageData1->Scan0;
	ptr_Result = ImageData2->Scan0;

	p = (System::Byte*)((System::Void*)ptr);
	R = (System::Byte*)((System::Void*)ptr_Result);
	myLine = new line[imageSize];
	int line_count = 0;
	for (int y = 0; y < Height_src; y++){
		for (int x = 0; x < Width_src; x++){
			if (p[ptr_bit*(x + Width_src*y) + 0] == 255){
				for (int angle = -90; angle <= 90; angle++){
					//	Sin, Cos are used the radians. Multiply by Math.PI/180 to convert degrees to radians.
					int rho = x*cos(angle*pi / 180) + y*sin(angle*pi / 180);
					//	Anotherway : rho = -tan(theta *pi / 180)*x + y;
					int point;
					if (abs(rho) <= quan_Height){
						// point = x + width * y
						point = (angle + 90) + (180 * (rho + quan_Height));
					}

					if (R[ptr_bit * point + 2] < 255){
						R[ptr_bit * point + 0]++;
						R[ptr_bit * point + 1]++;
						R[ptr_bit * point + 2]++;
					}

					if (R[ptr_bit * point + 0] == threshold){
						R[ptr_bit * point + 0] = 0;
						R[ptr_bit * point + 1] = 0;
						R[ptr_bit * point + 2] = 255;
						myLine[line_count].theta = angle;
						myLine[line_count].rho = rho;
						line_count++;
					}
				}
			}
		}
	}
	result->UnlockBits(ImageData1);
	quantization->UnlockBits(ImageData2);

	this->ImageData1 = result->LockBits(rect,
		System::Drawing::Imaging::ImageLockMode::ReadWrite, result->PixelFormat);
	ptr = ImageData1->Scan0;
	p = (System::Byte*)((System::Void*)ptr);

	if (line_count != 0)
		for (int i = 0; i < line_count; i++){
			drawLine(myLine[i].theta, myLine[i].rho);
		}

	result->UnlockBits(ImageData1);

	return quantization;
}

void mySobel::drawLine(int theta, int rho){
	//	角度 = 斜率/(pi/180); 斜率 = 角度*(pi/180)
	//	y = 斜率*x+C
	int y;
	for (int x = 0; x < Width_src; x++){
		y = (rho - cos(theta *(pi / 180))*x) / sin(theta *(pi / 180));
		//	for Anotherway : y = tan(theta *(pi / 180)) * x + rho;
		if (y < Height_src && y > 0){
			p[ptr_bit*(x + Width_src*y) + 0] = 0;
			p[ptr_bit*(x + Width_src*y) + 1] = 0;
			p[ptr_bit*(x + Width_src*y) + 2] = 255;
		}
	}
}
