#pragma once
ref class SaltPeperClass
{
public:
	SaltPeperClass(System::String^ fileName);
	System::Drawing::Bitmap^ getNoise(float ratio);
	System::Drawing::Bitmap^ getGaussianNoise(float ratio);
	System::Drawing::Bitmap^ getMedianFilter();
	System::Drawing::Bitmap^ getLowpassFilter(int level);
	void reOpen(System::String^ fileName);

private:
	void openPic(System::String^ fileName);
	void CreateNoise(float ratio);
	void doMedianFilter();
	void doLowpassFilter(int level);
	void setKernel(int level);
	void setGaussianNoise(int imageSize, double mean,double sigma);	//mean 期望值, sigma 標準差
	int getGaussianNoiseArrayVaule(int index);
	void doGaussianNoise();

	//宣告點陣圖的格式
	System::Drawing::Bitmap^ Image1;
	System::Drawing::Bitmap^ Image2;
	System::Drawing::Rectangle rect;
	System::Drawing::Imaging::BitmapData^ ImageData1;
	System::Drawing::Imaging::BitmapData^ ImageData2;
	System::IntPtr ptr;
	System::IntPtr ResultPtr;
	System::Byte* p;
	System::Byte* R;
	int ptr_bit = 3;
	int ptr_bit2 = 3;


	//common
	int Width_src;
	int Height_src;

	float nosie_ratio;
	int Image1_size;
	int noise_pixel;
	int pepper_pixel;
	int salt_pixel;

	int *pepper_array;
	int *salt_array;
	int *GaussianNoise_array;
	bool *Noise_position_array;

	int *kernel;
	//int kernel[9];
	int kernelTemp;
};
