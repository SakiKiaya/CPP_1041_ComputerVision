#pragma once

using namespace System::Drawing;
struct RGB{
	double R;
	double G;
	double B;
};

struct Sector
{
	int sector;
	double degree;
};

ref class HSI
{
public:
	HSI();
	Bitmap^ getHEResult(System::String^ filename);	//	return HE Result Bitmap
	
private:
	void openfile(System::String^ filename);
	void setPtr_bit(System::Drawing::Imaging::PixelFormat input);
	void reOpen(System::String^ fileName);

	void doHE();	//	use HSI to do Histogram Equ
	void setSrcHistogramWithI(double I);
	double figureOutI(double B, double G, double R);	
	void genSrcHistogram();
	void genEqualization();
	void doEqualization();
	RGB HSI2RGB(double H, double S, double I);

	void releseArray();
	int getEqualization(int index);
	int getMaxVaule();
	int getMinVaule();
	double getMinVaule(double B, double G, double R);
	Sector getAreaDegree(double degree);

	array<int>^ srcHistogram;
	array<int>^ HistogramEqualization;

	double PI;
	int MaxVaule;
	int MinVaule;
	int Width_src;
	int Height_src;
	int TotalPixel;

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

