#pragma once
ref class UnsharpClass
{
public:
	UnsharpClass(System::String^ fileName_in);
	System::Drawing::Bitmap^ getUnsharpMasking(int S_Max);
	int getHistogramVaule(int index, int isSource);
	void setHistoVaule(bool isSource);
	void releseArray();
	void reOpen(System::String^ fileName);

private:
	void openPic(System::String^ fileName_in);
	void doUnsharpMasking(int S_Max);
	void doLowpassFilter(int level);
	void setKernel(int level);

	void doHistogramShrink(int S_Max);

	void doEqualization();
	void setHistoFinish();
	void setEqualizationResultImage();
	
	void doPixelDiff();
	
	int getEqualization(int index);
	int getMaxVaule();
	int getMinVaule();


	array<int>^ srcHistogram;
	array<int>^ resHistogram;
	array<int>^ HistogramEqualization;
	bool isSource;
	bool HistogramIsFinish;
	int MaxVaule;
	int MinVaule;
	int TotalPixel;

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
	System::String^ fileName;

};

