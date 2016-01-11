#include "stdafx.h"
#include "Form1.h"

using namespace CPPWindowsFormsApp;
System::Void Form1::openImageToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
	label1->Text = "";
	openFileDialog1->Filter = "�I�}�� (*.bmp)|*.bmp|All files (*.*)|*.*";	//�]�wFilter�A�ΥH���w�ϥΪ̶}�Ҫ��ɮ�		
	openFileDialog1->FileName = "";		//�w�]�ɮצW�٬��ŭ�		
	openFileDialog1->Title = "���J�v��";	//�]�w���X��ܵ��������D�W��		
	openFileDialog1->FilterIndex = 1;	//�]�wFilter��ܼҦ�(�̷�Filter�ơA�p���ҿ��1��ܰ_�l�X�{�����I�}�ϡA���2���All filts)

	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK && openFileDialog1->FileName->Length > 0)
	{
		if (System::IO::Path::GetExtension(openFileDialog1->FileName) != ".BMP")
			label1->Text = "Not BMP";
		Image1 = safe_cast<Bitmap^>(Image::FromFile(openFileDialog1->FileName));	//�N������ɮ�Ū���åB�s��Image1
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