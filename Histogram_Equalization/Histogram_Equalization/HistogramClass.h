#pragma once
ref class HistogramClass
{
public:
	HistogramClass(System::String^ fileName);
	System::Drawing::Bitmap^ getEqualizationResult();
	int getHistogramVaule(int index, int isSource);
	void setHistoVaule(bool isSource);
	void releseArray();
	void reOpen(System::String^ fileName);

private:
	void openPic(System::String^ fileName);
	void setHistoFinish();
	void doEqualization();
	void setResultImage();
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
	int Width_src;
	int Height_src;
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

};

