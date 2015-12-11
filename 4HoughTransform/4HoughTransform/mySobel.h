#pragma once
struct line
{
	int theta;
	int rho;
};
ref class mySobel
{
public:
	mySobel(double threshold);
	void setThreshold(double threshold_in);
	void openPic(System::String^ fileName);
	void reOpen(System::String^ fileName);
	System::Drawing::Bitmap^ getSobelResult(System::String^ fileName_in);
	System::Drawing::Bitmap^ getHoughTransform(int threshold);
	void drawLine(int theta,int rho);
	System::Drawing::Bitmap^ getdoX();
	System::Drawing::Bitmap^ getdoY();

	System::Drawing::Bitmap^ source;
	System::Drawing::Bitmap^ doX;
	System::Drawing::Bitmap^ doY;
	System::Drawing::Bitmap^ result;

	System::Drawing::Bitmap^ quantization;
private:
	void doSobel();
	void setKernel();
	int addAll(int *mask_in, bool isX);

	int *maskX;
	int *maskY;

	int *srcTemp_mask;
	int *resTemp_mask;
	//int *quantization;

	double threshold;

	int Width_src;
	int Height_src;
	int imageSize;

	int quan_size;
	int quan_Height;

	line *myLine;

	double pi;

	System::Drawing::Rectangle rect;
	System::Drawing::Rectangle quan_rect;

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

