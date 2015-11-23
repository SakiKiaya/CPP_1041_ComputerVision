#include "stdafx.h"
#include "Form1.h"

using namespace CPPWindowsFormsApp;
using namespace System;

Form1::Form1(void){
	InitializeComponent();
	//
	//TODO:  在此加入建構函式程式碼
	//
}

Void Form1::openToolStripMenuItem_Click(Object^  sender, EventArgs^  e) {
	//===開圖主程式===

	openFileDialog1->Filter = "點陣圖 (*.bmp)|*.bmp|All files (*.*)|*.*";	//設定Filter，用以限定使用者開啟的檔案		
	openFileDialog1->FileName = "";		//預設檔案名稱為空值		
	openFileDialog1->Title = "載入影像";	//設定跳出選擇視窗的標題名稱		
	openFileDialog1->FilterIndex = 1;	//設定Filter選擇模式(依照Filter數，如本例選擇1表示起始出現的為點陣圖，選擇2表示All filts)

	//跳出檔案選擇視窗(ShowDialog)，並且如果使用者點選檔案，並且檔案名稱超過0個字元，則判斷是為True，進入處理程序
	if (openFileDialog1->ShowDialog() == Windows::Forms::DialogResult::OK && openFileDialog1->FileName->Length > 0){

		Image1 = safe_cast<Bitmap^>(Image::FromFile(openFileDialog1->FileName));	//將選取的檔案讀取並且存至Image1			
		rect = Rectangle(0, 0, Image1->Width, Image1->Height);	//設定rect範圍大小

		//像素值為b,g,r方式排列下去，所以寬度實際上有*3的數值大小		
		picBox_Src->Image = Image1;	//顯示Image1於PictureBox1工具上

		Width_src = Image1->Width;
		Height_src = Image1->Height;

		chart1->Series["Gray"]->Points->Clear();
	}
}

Void Form1::saveToolStripMenuItem_Click(Object^  sender, EventArgs^  e){
	if (picBox_Res->Image != nullptr)
		picBox_Res->Image->Save("Result.BMP");
	else
		label1->Text = "source fail";
}

/* Histogram equalization */
// Show source Histogram
Void Form1::showToolStripMenuItem_Click(Object^  sender, EventArgs^  e){
	// 判斷是否以載入圖片
	if (Image1 != nullptr){
		if (myHistogram == nullptr)										// if the myHistogramClass is not setup(create)
			myHistogram = gcnew HistogramClass(openFileDialog1->FileName); // setup myHistogramClass
		else
			myHistogram->reOpen(openFileDialog1->FileName);
		myHistogram->getEqualizationResult();
		this->myHistogram->setHistoVaule(true);
		// 繪製圖表
		chart1->Series["Gray"]->Points->Clear();
		for (int i = 0; i < 256; i++){
			int temp_Histogram = this->myHistogram->getHistogramVaule(i, true);
			Form1::chart1->Series["Gray"]->Points->AddXY(i.ToString(), temp_Histogram != -1 ? temp_Histogram : 0);
		}
	}
	else{
		label1->Text = "Source Error!";
	}
}
// Show equalization histogram and result image
Void Form1::equalizationToolStripMenuItem_Click(Object^  sender, EventArgs^  e){
	if (Image1 != nullptr){		// image isn't loaded
		if (myHistogram == nullptr)										// if the myHistogramClass is not setup(create)
			myHistogram = gcnew HistogramClass(openFileDialog1->FileName); // setup myHistogramClass
		else
			myHistogram->reOpen(openFileDialog1->FileName);

		//將影像顯示在pictureBox1
		picBox_Res->Image = myHistogram->getEqualizationResult();
		this->tabControl1->SelectTab(1);

		// 繪製圖表
		chart1->Series["Gray"]->Points->Clear();
		for (int i = 0; i < 256; i++){
			int temp_Histogram = this->myHistogram->getHistogramVaule(i, false);
			Form1::chart1->Series["Gray"]->Points->AddXY(i.ToString(), temp_Histogram != -1 ? temp_Histogram : 0);
		}
	}
	else{
		label1->Text = "Source Error!";
	}
}

/* SaltPeper nosie create (5%~70%)*/
// 5%
Void Form1::toolStripMenuItem2_Click(Object^  sender, EventArgs^  e) {
	if (Image1 != nullptr){
		if (mySaltPepper == nullptr)										// if the SqltpeperClass is not setup(create)
			mySaltPepper = gcnew SaltPeperClass(openFileDialog1->FileName);	// setup SaltPeperClass
		else
			mySaltPepper->reOpen(openFileDialog1->FileName);				// else open the picture again
		Image1 = mySaltPepper->getNoise(5.0);
		picBox_Res->Image = Image1;
		this->tabControl1->SelectTab(1);
	}
	else{
		label1->Text = "Source Error!";
	}
}
// 10%
Void Form1::toolStripMenuItem3_Click(Object^  sender, EventArgs^  e) {
	if (Image1 != nullptr){
		if (mySaltPepper == nullptr)
			mySaltPepper = gcnew SaltPeperClass(openFileDialog1->FileName);
		else
			mySaltPepper->reOpen(openFileDialog1->FileName);
		Image1 = mySaltPepper->getNoise(10.0);
		picBox_Res->Image = Image1;
		this->tabControl1->SelectTab(1);
	}
	else{
		label1->Text = "Source Error!";
	}
}
// 20%
Void Form1::toolStripMenuItem4_Click(Object^  sender, EventArgs^  e) {
	if (Image1 != nullptr){
		if (mySaltPepper == nullptr)
			mySaltPepper = gcnew SaltPeperClass(openFileDialog1->FileName);
		else
			mySaltPepper->reOpen(openFileDialog1->FileName);
		Image1 = mySaltPepper->getNoise(20.0);
		picBox_Res->Image = Image1;
		this->tabControl1->SelectTab(1);
	}
	else{
		label1->Text = "Source Error!";
	}
}
// 50%
Void Form1::toolStripMenuItem5_Click(Object^  sender, EventArgs^  e) {
	if (Image1 != nullptr){
		if (mySaltPepper == nullptr)
			mySaltPepper = gcnew SaltPeperClass(openFileDialog1->FileName);
		else
			mySaltPepper->reOpen(openFileDialog1->FileName);
		Image1 = mySaltPepper->getNoise(50.0);
		picBox_Res->Image = Image1;
		this->tabControl1->SelectTab(1);
	}
	else{
		label1->Text = "Source Error!";
	}
}
// 70%
Void Form1::toolStripMenuItem6_Click(Object^  sender, EventArgs^  e) {
	if (Image1 != nullptr){
		if (mySaltPepper == nullptr)
			mySaltPepper = gcnew SaltPeperClass(openFileDialog1->FileName);
		else
			mySaltPepper->reOpen(openFileDialog1->FileName);
		Image1 = mySaltPepper->getNoise(70.0);
		picBox_Res->Image = Image1;
		this->tabControl1->SelectTab(1);
	}
	else{
		label1->Text = "Source Error!";
	}
}

/*Gaussion nosie create (5%~50%)*/
// 5%
Void Form1::gaussToolStripMenuItem_Click(Object^  sender, EventArgs^  e){
	if (Image1 != nullptr){
		if (mySaltPepper == nullptr)
			mySaltPepper = gcnew SaltPeperClass(openFileDialog1->FileName);
		else
			mySaltPepper->reOpen(openFileDialog1->FileName);

		/*float mean = 127;	// 中間值?
		float sigma = 50;	// 標準差*/
		picBox_Res->Image = this->mySaltPepper->getGaussianNoise(0.05);
		this->tabControl1->SelectTab(1);
	}
	else{
		label1->Text = "Source Error!";
	}
}

// 10%
Void Form1::gaussionNoise10ToolStripMenuItem_Click(Object^  sender, EventArgs^  e){
	if (Image1 != nullptr){
		if (mySaltPepper == nullptr)
			mySaltPepper = gcnew SaltPeperClass(openFileDialog1->FileName);
		else
			mySaltPepper->reOpen(openFileDialog1->FileName);
		picBox_Res->Image = this->mySaltPepper->getGaussianNoise(0.10);
		this->tabControl1->SelectTab(1);
	}
	else{
		label1->Text = "Source Error!";
	}
}

// 20%
Void Form1::gaussionNoise20ToolStripMenuItem_Click(Object^  sender, EventArgs^  e){
	if (Image1 != nullptr){
		if (mySaltPepper == nullptr)
			mySaltPepper = gcnew SaltPeperClass(openFileDialog1->FileName);
		else
			mySaltPepper->reOpen(openFileDialog1->FileName);
		picBox_Res->Image = this->mySaltPepper->getGaussianNoise(0.20);
		this->tabControl1->SelectTab(1);
	}
	else{
		label1->Text = "Source Error!";
	}
}

//50%
Void Form1::gaussionNoise50ToolStripMenuItem_Click(Object^  sender, EventArgs^  e){
	if (Image1 != nullptr){
		if (mySaltPepper == nullptr)
			mySaltPepper = gcnew SaltPeperClass(openFileDialog1->FileName);
		else
			mySaltPepper->reOpen(openFileDialog1->FileName);
		picBox_Res->Image = this->mySaltPepper->getGaussianNoise(0.50);
		this->tabControl1->SelectTab(1);
	}
	else{
		label1->Text = "Source Error!";
	}
}

/* Low-pass filter */
// 3x3(9)
Void Form1::kernel3x39ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
	if (Image1 != nullptr){
		if (mySaltPepper == nullptr)
			mySaltPepper = gcnew SaltPeperClass(openFileDialog1->FileName);
		else
			mySaltPepper->reOpen(openFileDialog1->FileName);
		picBox_Res->Image = mySaltPepper->getLowpassFilter(0);	//level = 0 use 3x3(9) kernel
		this->tabControl1->SelectTab(1);
	}
	else{
		label1->Text = "Source Error!";
	}
}
// 3x3(10)
Void Form1::kernel3x310ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
	if (Image1 != nullptr){
		if (mySaltPepper == nullptr)
			mySaltPepper = gcnew SaltPeperClass(openFileDialog1->FileName);
		else
			mySaltPepper->reOpen(openFileDialog1->FileName);
		picBox_Res->Image = mySaltPepper->getLowpassFilter(1);	//level = 1 use 3x3(10) kernel
		this->tabControl1->SelectTab(1);
	}
	else{
		label1->Text = "Source Error!";
	}
}
// 3x3(16)
Void Form1::kernel3x316ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
	if (Image1 != nullptr){
		if (mySaltPepper == nullptr)
			mySaltPepper = gcnew SaltPeperClass(openFileDialog1->FileName);
		else
			mySaltPepper->reOpen(openFileDialog1->FileName);
		picBox_Res->Image = mySaltPepper->getLowpassFilter(2);	//level = 2 use 3x3(16) kernel
		this->tabControl1->SelectTab(1);
	}
	else{
		label1->Text = "Source Error!";
	}
}

Void Form1::lopassFilterToolStripMenuItem_Click(Object^  sender, EventArgs^  e) {
}

/* Median filter */
Void Form1::medianFilterToolStripMenuItem_Click(Object^  sender, EventArgs^  e) {
	if (Image1 != nullptr && mySaltPepper != nullptr){
		picBox_Res->Image = mySaltPepper->getMedianFilter();
		this->tabControl1->SelectTab(1);
	}
	else{
		label1->Text = "Source Error!";
	}
}