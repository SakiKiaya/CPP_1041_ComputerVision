#pragma once
using namespace System::Drawing;

ref class HSI
{
public:
	HSI();
	Bitmap^ getHSIResult(System::String^ filename);	//	return HSItoRGB
	Bitmap^ getHEResult(System::String^ filename);	//	return HSItoRGB

private:
	void openfile(System::String^ filename);
	void setPtr_bit(System::Drawing::Imaging::PixelFormat input);
	void reOpen(System::String^ fileName);
	void doHSI_Transfer();

	void releseArray();
	void genSrcHistogram();
	void setSrcHistogramWithI(double I);
	void genEqualization();
	void doEqualization();
	int getMaxVaule();
	int getMinVaule();
	int getEqualization(double index);

	HSI_region RGBtoHSI(RGB input);
	RGB HSI2RGB(HSI_region input);
	double figureOutH(RGB input);
	double figureOutS(RGB input);
	double figureOutI(RGB input);
	double getMinVaule(RGB input);
	Sector getAreaDegree(double degree);

	double PI;
	int MaxVaule;
	int MinVaule;
	int Width_src;
	int Height_src;
	int TotalPixel;

	array<int>^ srcHistogram;
	array<int>^ HistogramEqualization;

	System::Drawing::Bitmap^ Image1;
	System::Drawing::Bitmap^ Image2;
	System::Drawing::Rectangle rect;
	System::Drawing::Imaging::BitmapData^ ImageData1;
	System::Drawing::Imaging::BitmapData^ ImageData2;
	System::IntPtr ptr;
	System::IntPtr ResultPtr;
	System::Byte* p;
	System::Byte* Res;
	int ptr_bit;
};

