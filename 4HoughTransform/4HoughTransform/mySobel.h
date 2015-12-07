#pragma once
ref class mySobel
{
public:
	mySobel(double threshold);
	void openPic(System::String^ fileName);
	void reOpen(System::String^ fileName);
	System::Drawing::Bitmap^ getSobelResult(System::String^ fileName_in);
	System::Drawing::Bitmap^ getdoX();
	System::Drawing::Bitmap^ getdoY();
	System::Drawing::Bitmap^ source;
	System::Drawing::Bitmap^ doX;
	System::Drawing::Bitmap^ doY;
	System::Drawing::Bitmap^ result;
private:
	void doSobel();
	void setKernel();
	void setThreshold(double threshold_in);
	int addAll(int *mask_in, bool isX);

	int *maskX;
	int *maskY;
	
	int *srcTemp_mask;
	int *resTemp_mask;
	
	double threshold;

	int Width_src;
	int Height_src;
	int imageSize;

	System::Drawing::Rectangle rect;
	System::Drawing::Imaging::BitmapData^ ImageData1;
	System::Drawing::Imaging::BitmapData^ ImageData2;
	System::Drawing::Imaging::BitmapData^ ImageDataX;
	System::Drawing::Imaging::BitmapData^ ImageDataY;
	System::IntPtr ptr;
	System::IntPtr ptr_Result;
	System::IntPtr ptr_x;
	System::IntPtr ptr_y;
	System::Byte* p;
	System::Byte* R;
	System::Byte* p_x;
	System::Byte* p_y;
	int ptr_bit = 3;
	int ptr_bit2 = 3;
	int* pixelTemp;
};

