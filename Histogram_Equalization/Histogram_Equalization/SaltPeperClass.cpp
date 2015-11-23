#include "stdafx.h"
#include "SaltPeperClass.h"

SaltPeperClass::SaltPeperClass(System::String^ fileName)
{
	this->openPic(fileName);
	srand((unsigned)time(NULL));
}

void SaltPeperClass::openPic(System::String^ fileName){
	this->Image1 = safe_cast<System::Drawing::Bitmap^>(System::Drawing::Image::FromFile(fileName));	//將選取的檔案讀取並且存至Image1			
	this->rect = System::Drawing::Rectangle(0, 0, this->Image1->Width, this->Image1->Height);	//設定rect範圍大小

	this->Width_src = this->Image1->Width;
	this->Height_src = this->Image1->Height;
	this->Image1_size = this->Width_src*this->Height_src;

};

System::Drawing::Bitmap^ SaltPeperClass::getNoise(float ratio){
	CreateNoise(ratio);
	return Image1;
}


System::Drawing::Bitmap^ SaltPeperClass::getGaussianNoise(float ratio){
	noise_pixel = round(Image1_size*ratio);
	setGaussianNoise(noise_pixel, 127, 50);
	doGaussianNoise();
	return Image1;
}

void SaltPeperClass::CreateNoise(float ratio){
	nosie_ratio = (float)ratio / 100.0;		// Set ratio
	noise_pixel = (float)Image1_size*(float)nosie_ratio;		// Figrue out how many noise pixel will insert there
	pepper_pixel = noise_pixel / 2;			// Use black pixel to insert half of all nosie
	salt_pixel = noise_pixel / 2;			// Use white pixel to insert half of all nosie

	pepper_array = new int[pepper_pixel];	// Write down the black pixel's Coordinate(X,Y) that was inserted 
	salt_array = new int[salt_pixel];		// Write down the white pixel's Coordinate(X,Y) that was inserted

	ImageData1 = Image1->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, Image1->PixelFormat);
	ptr = ImageData1->Scan0;
	p = (System::Byte*)((System::Void*)ptr);
	int temp = 0;
	int pepper_sum = 0;
	int salt_sum = 0;
	while (pepper_sum != pepper_pixel){		// Loop until the pepper was inserted  half of all nosie
		int rx = rand() % Width_src;		// Rand the X,Y
		int ry = rand() % Height_src;
		int pixel = (rx + ry*Width_src) * 3;
		if (
			p[pixel + 0] != 0 &&
			p[pixel + 1] != 0 &&
			p[pixel + 2] != 0 &&
			p[pixel + 0] != 255 &&
			p[pixel + 1] != 255 &&
			p[pixel + 2] != 255
			)
		{
			p[pixel + 0] = 0;
			p[pixel + 1] = 0;
			p[pixel + 2] = 0;
			pepper_sum++;

		}
		temp++;
	}
	while (salt_sum != salt_pixel){			// Loop until the salt was inserted  half of all nosie
		int rx = rand() % Width_src;		// Rand the X,Y
		int ry = rand() % Height_src;
		int pixel = (rx + ry*Width_src) * 3;
		if (
			p[pixel + 0] != 0 &&
			p[pixel + 1] != 0 &&
			p[pixel + 2] != 0 &&
			p[pixel + 0] != 255 &&
			p[pixel + 1] != 255 &&
			p[pixel + 2] != 255
			)
		{
			p[pixel + 0] = 255;
			p[pixel + 1] = 255;
			p[pixel + 2] = 255;
			salt_sum++;
		}
	}
	Image1->UnlockBits(ImageData1);
}

void SaltPeperClass::doMedianFilter(){
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
			if (x != 0 && y != 0 && x != Width_src && y != Height_src){
				for (int i = 0; i < 3; i++){
					std::vector<int> pixelTemp(9);
					pixelTemp[0] = p[ptr_bit*((x - 1) + Width_src*(y - 1)) + i];
					pixelTemp[1] = p[ptr_bit*(x + Width_src*(y - 1)) + i];
					pixelTemp[2] = p[ptr_bit*((x + 1) + Width_src*(y - 1)) + i];

					pixelTemp[3] = p[ptr_bit*((x - 1) + Width_src*y) + i];
					pixelTemp[4] = p[ptr_bit*(x + Width_src*y) + i];
					pixelTemp[5] = p[ptr_bit*((x + 1) + Width_src*y) + i];

					pixelTemp[6] = p[ptr_bit*((x - 1) + Width_src*(y + 1)) + i];
					pixelTemp[7] = p[ptr_bit*(x + Width_src*(y + 1)) + i];
					pixelTemp[8] = p[ptr_bit*((x + 1) + Width_src*(y + 1)) + i];
					std::sort(pixelTemp.begin(), pixelTemp.end());
					R[3 * (x + Width_src*y) + i] = pixelTemp[4];
				}
			}
			else {
				R[3 * (x + Width_src*y) + 0] = p[3 * (x + Width_src*y) + 0];
				R[3 * (x + Width_src*y) + 1] = p[3 * (x + Width_src*y) + 1];
				R[3 * (x + Width_src*y) + 2] = p[3 * (x + Width_src*y) + 2];
			}
		}
	}

	//Unlock處理完畢的像素範圍
	Image2->UnlockBits(ImageData2);
	Image1->UnlockBits(ImageData1);
}

System::Drawing::Bitmap^ SaltPeperClass::getMedianFilter(){
	if (Image2 != nullptr)
		Image1 = Image2;
	this->doMedianFilter();

	return this->Image2;
}

void SaltPeperClass::doLowpassFilter(int level){
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
			if (x != 0 && y != 0 && x != Width_src && y != Height_src){			// If is not edge
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

System::Drawing::Bitmap^ SaltPeperClass::getLowpassFilter(int level){
	doLowpassFilter(level);
	return Image2;
}

// set kernel weight
void SaltPeperClass::setKernel(int level){
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

void SaltPeperClass::reOpen(System::String^ fileName){
	this->openPic(fileName);
}

int SaltPeperClass::getGaussianNoiseArrayVaule(int index){
	return GaussianNoise_array[index];
}

void SaltPeperClass::setGaussianNoise(int NoiseAmount, double mean, double sigma){
	GaussianNoise_array = new int[NoiseAmount];
	for (int i = 0; i < NoiseAmount; i++){
		GaussianNoise_array[i] = 0;
	}

	for (int i = 0; i < NoiseAmount; i++)
	{
		double u = rand() / (double)RAND_MAX;
		double v = rand() / (double)RAND_MAX;
		float x = sqrt(-2 * log(u)) * cos(2 * 3.14159 * v) * sigma + mean;
		int temp = (int)round(x);
		GaussianNoise_array[temp]++;
	}
}

void SaltPeperClass::doGaussianNoise(){
	if (GaussianNoise_array != nullptr){
		Noise_position_array = new bool[Image1_size];
		for (int i = 0; i < Image1_size; i++)
			Noise_position_array[i] = false;
		ImageData1 = Image1->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, Image1->PixelFormat);
		ptr = ImageData1->Scan0;
		p = (System::Byte*)((System::Void*)ptr);
		int temp = 0;
		while (temp < noise_pixel){		// Loop until the pepper was inserted  half of all nosie
			int rx = rand() % Width_src;		// Rand the X,Y
			int ry = rand() % Height_src;
			int pixel = (rx + ry*Width_src) * 3;
			if (Noise_position_array[pixel/3] == false){
				p[pixel + 0] = GaussianNoise_array[temp];
				p[pixel + 1] = GaussianNoise_array[temp];
				p[pixel + 2] = GaussianNoise_array[temp];
				Noise_position_array[pixel/3] = true;
			}
			temp++;
		}
		Image1->UnlockBits(ImageData1);
	}
}