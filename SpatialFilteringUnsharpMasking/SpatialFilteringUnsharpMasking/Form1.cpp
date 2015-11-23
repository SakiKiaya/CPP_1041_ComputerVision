#include "stdafx.h"
#include "Form1.h"
using namespace CPPWindowsFormsApp;
System::Void Form1::openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
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
		pictureBox_Src->Image = Image1;	//顯示Image1於PictureBox1工具上

		Width_src = Image1->Width;
		Height_src = Image1->Height;
	}
}
System::Void Form1::trackBar1_ValueChanged(System::Object^  sender, System::EventArgs^  e)
{
	this->label1->Text = "SMAX : "+this->trackBar1->Value.ToString();
}
System::Void Form1::button1_Click(System::Object^  sender, System::EventArgs^  e){
	if (Image1 != nullptr){
		if (myUnsharpClass == nullptr)										// if the SqltpeperClass is not setup(create)
			myUnsharpClass = gcnew UnsharpClass(openFileDialog1->FileName);	// setup SaltPeperClass
		else
			myUnsharpClass->reOpen(openFileDialog1->FileName);				// else open the picture again
		Image1 = myUnsharpClass->getUnsharpMasking(this->trackBar1->Value);
		
		chart1->Series["Series1"]->Points->Clear();
		for (int i = 0; i < 256; i++){
			int temp_Histogram = this->myUnsharpClass->getHistogramVaule(i, true);
			Form1::chart1->Series["Series1"]->Points->AddXY(i.ToString(), temp_Histogram != -1 ? temp_Histogram : 0);
		}

		pictureBox_Res->Image = Image1;
	}
	else{
		label1->Text = "Source Error!";
	}
}