#include "stdafx.h"
#include "Form1.h"
#include <iostream>

using namespace System;
using namespace CPPWindowsFormsApp;
Void Form1::Form1_Load(System::Object^  sender, System::EventArgs^  e){

}

System::Void Form1::openFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
	//===�}�ϥD�{��===

	openFileDialog1->Filter = "�I�}�� (*.bmp)|*.bmp|All files (*.*)|*.*";	//�]�wFilter�A�ΥH���w�ϥΪ̶}�Ҫ��ɮ�		
	openFileDialog1->FileName = "";		//�w�]�ɮצW�٬��ŭ�		
	openFileDialog1->Title = "���J�v��";	//�]�w���X��ܵ��������D�W��		
	openFileDialog1->FilterIndex = 1;	//�]�wFilter��ܼҦ�(�̷�Filter�ơA�p���ҿ��1��ܰ_�l�X�{�����I�}�ϡA���2���All filts)

	//���X�ɮ׿�ܵ���(ShowDialog)�A�åB�p�G�ϥΪ��I���ɮסA�åB�ɮצW�ٶW�L0�Ӧr���A�h�P�_�O��True�A�i�J�B�z�{��
	if (openFileDialog1->ShowDialog() == Windows::Forms::DialogResult::OK && openFileDialog1->FileName->Length > 0){

		Image1 = safe_cast<Bitmap^>(Image::FromFile(openFileDialog1->FileName));	//�N������ɮ�Ū���åB�s��Image1			
		rect = Rectangle(0, 0, Image1->Width, Image1->Height);	//�]�wrect�d��j�p

		//�����Ȭ�b,g,r�覡�ƦC�U�h�A�ҥH�e�׹�ڤW��*3���ƭȤj�p		
		pictureBox1->Image = Image1;	//���Image1��PictureBox1�u��W

		Width_src = Image1->Width;
		Height_src = Image1->Height;
	}
}

System::Void Form1::getSobelToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
	if (mSobel == nullptr){
		mSobel = gcnew mySobel(70); // setup threshold
	}
	else
		mSobel->reOpen(openFileDialog1->FileName);

	pictureBox2->Image = mSobel->getSobelResult(openFileDialog1->FileName);
	pictureBox3->Image = mSobel->getdoX();
	pictureBox4->Image = mSobel->getdoY();	
}
