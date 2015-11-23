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
		picBox_Src->Image = Image1;	//顯示Image1於PictureBox1工具上

		Width_src = Image1->Width;
		Height_src = Image1->Height;
	}
}

/* Salt Peper Noise */
System::Void Form1::saltPeper5ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
	if (Image1 != nullptr){
		if (mySaltPepper == nullptr)										// if the SqltpeperClass is not setup(create)
			mySaltPepper = gcnew SaltPeperClass(openFileDialog1->FileName);	// setup SaltPeperClass
		else
			mySaltPepper->reOpen(openFileDialog1->FileName);				// else open the picture again
		Image1 = mySaltPepper->getNoise(5.0);
		picBox_Res->Image = Image1;
	}
	else{
		label1->Text = "Source Error!";
	}
}
System::Void Form1::saltPeper10ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
	if (Image1 != nullptr){
		if (mySaltPepper == nullptr)										// if the SqltpeperClass is not setup(create)
			mySaltPepper = gcnew SaltPeperClass(openFileDialog1->FileName);	// setup SaltPeperClass
		else
			mySaltPepper->reOpen(openFileDialog1->FileName);				// else open the picture again
		Image1 = mySaltPepper->getNoise(10.0);
		picBox_Res->Image = Image1;
	}
	else{
		label1->Text = "Source Error!";
	}
}
System::Void Form1::saltPeper20ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
	if (Image1 != nullptr){
		if (mySaltPepper == nullptr)										// if the SqltpeperClass is not setup(create)
			mySaltPepper = gcnew SaltPeperClass(openFileDialog1->FileName);	// setup SaltPeperClass
		else
			mySaltPepper->reOpen(openFileDialog1->FileName);				// else open the picture again
		Image1 = mySaltPepper->getNoise(20.0);
		picBox_Res->Image = Image1;
	}
	else{
		label1->Text = "Source Error!";
	}
}
System::Void Form1::saltPeper50ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
	if (Image1 != nullptr){
		if (mySaltPepper == nullptr)										// if the SqltpeperClass is not setup(create)
			mySaltPepper = gcnew SaltPeperClass(openFileDialog1->FileName);	// setup SaltPeperClass
		else
			mySaltPepper->reOpen(openFileDialog1->FileName);				// else open the picture again
		Image1 = mySaltPepper->getNoise(50.0);
		picBox_Res->Image = Image1;
	}
	else{
		label1->Text = "Source Error!";
	}
}
System::Void Form1::saltPeper70ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
	if (Image1 != nullptr){
		if (mySaltPepper == nullptr)										// if the SqltpeperClass is not setup(create)
			mySaltPepper = gcnew SaltPeperClass(openFileDialog1->FileName);	// setup SaltPeperClass
		else
			mySaltPepper->reOpen(openFileDialog1->FileName);				// else open the picture again
		Image1 = mySaltPepper->getNoise(70.0);
		picBox_Res->Image = Image1;
	}
	else{
		label1->Text = "Source Error!";
	}
}

/* Gaussion Noise */
System::Void Form1::gaussionNoise5ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
	if (Image1 != nullptr){
		if (mySaltPepper == nullptr)
			mySaltPepper = gcnew SaltPeperClass(openFileDialog1->FileName);
		else
			mySaltPepper->reOpen(openFileDialog1->FileName);

		/*float mean = 127;	// 中間值?
		float sigma = 50;	// 標準差*/
		picBox_Res->Image = this->mySaltPepper->getGaussianNoise(0.05);
	}
	else{
		label1->Text = "Source Error!";
	}
}
System::Void Form1::gaussionNoise10ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
	if (Image1 != nullptr){
		if (mySaltPepper == nullptr)
			mySaltPepper = gcnew SaltPeperClass(openFileDialog1->FileName);
		else
			mySaltPepper->reOpen(openFileDialog1->FileName);

		/*float mean = 127;	// 中間值?
		float sigma = 50;	// 標準差*/
		picBox_Res->Image = this->mySaltPepper->getGaussianNoise(0.10);
	}
	else{
		label1->Text = "Source Error!";
	}
}
System::Void Form1::gaussionNoise20ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
	if (Image1 != nullptr){
		if (mySaltPepper == nullptr)
			mySaltPepper = gcnew SaltPeperClass(openFileDialog1->FileName);
		else
			mySaltPepper->reOpen(openFileDialog1->FileName);

		/*float mean = 127;	// 中間值?
		float sigma = 50;	// 標準差*/
		picBox_Res->Image = this->mySaltPepper->getGaussianNoise(0.20);
	}
	else{
		label1->Text = "Source Error!";
	}
}
System::Void Form1::gaussionNoise5ToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e){
	if (Image1 != nullptr){
		if (mySaltPepper == nullptr)
			mySaltPepper = gcnew SaltPeperClass(openFileDialog1->FileName);
		else
			mySaltPepper->reOpen(openFileDialog1->FileName);

		/*float mean = 127;	// 中間值?
		float sigma = 50;	// 標準差*/
		picBox_Res->Image = this->mySaltPepper->getGaussianNoise(0.50);
	}
	else{
		label1->Text = "Source Error!";
	}
}

/* Low-Pass Filter */
System::Void  Form1::kernel3x39ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
	if (Image1 != nullptr){
		if (mySaltPepper == nullptr)
			mySaltPepper = gcnew SaltPeperClass(openFileDialog1->FileName);
		else
			mySaltPepper->reOpen(openFileDialog1->FileName);
		picBox_Res->Image = mySaltPepper->getLowpassFilter(0);	//level = 0 use 3x3(9) kernel
	}
	else{
		label1->Text = "Source Error!";
	}
}
System::Void  Form1::kernel3x310ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
	if (Image1 != nullptr){
		if (mySaltPepper == nullptr)
			mySaltPepper = gcnew SaltPeperClass(openFileDialog1->FileName);
		else
			mySaltPepper->reOpen(openFileDialog1->FileName);
		picBox_Res->Image = mySaltPepper->getLowpassFilter(1);	//level = 0 use 3x3(9) kernel
	}
	else{
		label1->Text = "Source Error!";
	}
}
System::Void  Form1::kernel3x316ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
	if (Image1 != nullptr){
		if (mySaltPepper == nullptr)
			mySaltPepper = gcnew SaltPeperClass(openFileDialog1->FileName);
		else
			mySaltPepper->reOpen(openFileDialog1->FileName);
		picBox_Res->Image = mySaltPepper->getLowpassFilter(2);	//level = 0 use 3x3(9) kernel
	}
	else{
		label1->Text = "Source Error!";
	}
}

/* Median Filter  */
System::Void  Form1::medianFilterToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
	if (Image1 != nullptr && mySaltPepper != nullptr){
		picBox_Res->Image = mySaltPepper->getMedianFilter();
	}
	else{
		label1->Text = "Source Error!";
	}
}