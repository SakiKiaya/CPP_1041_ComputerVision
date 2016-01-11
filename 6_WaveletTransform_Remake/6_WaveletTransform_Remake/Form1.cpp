#include "stdafx.h"
#include "Form1.h"

using namespace CPPWindowsFormsApp;
System::Void Form1::openImageToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
	label1->Text = "";
	openFileDialog1->Filter = "點陣圖 (*.bmp)|*.bmp|All files (*.*)|*.*";	//設定Filter，用以限定使用者開啟的檔案		
	openFileDialog1->FileName = "";		//預設檔案名稱為空值		
	openFileDialog1->Title = "載入影像";	//設定跳出選擇視窗的標題名稱		
	openFileDialog1->FilterIndex = 1;	//設定Filter選擇模式(依照Filter數，如本例選擇1表示起始出現的為點陣圖，選擇2表示All filts)

	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK && openFileDialog1->FileName->Length > 0)
	{
		if (System::IO::Path::GetExtension(openFileDialog1->FileName) != ".BMP")
			label1->Text = "Not BMP";
		Image1 = safe_cast<Bitmap^>(Image::FromFile(openFileDialog1->FileName));	//將選取的檔案讀取並且存至Image1
		pictureBox1->Image = Image1;
		int debug = 0;
	}
}

System::Void Form1::waveletTransformToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
	if (openFileDialog1->FileName != ""){
		if (myWavelet != NULL)
			delete myWavelet;
		myWavelet = new Wavelet((char *)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->openFileDialog1->FileName));
		pictureBox2->Image = myWavelet->getWavelet((char *)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(this->openFileDialog1->FileName));
	}
	else{
		label1->Text = "Src Error!";
	}
}