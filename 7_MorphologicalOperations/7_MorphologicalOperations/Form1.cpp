#include "stdafx.h"
#include "Form1.h"

using namespace CPPWindowsFormsApp;
using namespace std;

System::Void Form1::Form1_Load(System::Object^  sender, System::EventArgs^  e){
	ptr_bit = 3;
	ptr_bit2 = 3;
	isFirstrow = true;
	isHSI = false;
	isBool = true;
	isReprocess = false;
}

System::Void Form1::openFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
	//===�}�ϥD�{��===

	openFileDialog1->Filter = "�I�}�� (*.bmp)|*.bmp|All files (*.*)|*.*";	//�]�wFilter�A�ΥH���w�ϥΪ̶}�Ҫ��ɮ�		
	openFileDialog1->FileName = "";		//�w�]�ɮצW�٬��ŭ�		
	openFileDialog1->Title = "���J�v��";	//�]�w���X��ܵ��������D�W��		
	openFileDialog1->FilterIndex = 1;	//�]�wFilter��ܼҦ�(�̷�Filter�ơA�p���ҿ��1��ܰ_�l�X�{�����I�}�ϡA���2���All filts)

	//���X�ɮ׿�ܵ���(ShowDialog)�A�åB�p�G�ϥΪ��I���ɮסA�åB�ɮצW�ٶW�L0�Ӧr���A�h�P�_�O��True�A�i�J�B�z�{��
	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK && openFileDialog1->FileName->Length > 0){

		Image1 = safe_cast<Bitmap^>(Image::FromFile(openFileDialog1->FileName));	//�N������ɮ�Ū���åB�s��Image1			
		rect = Rectangle(0, 0, Image1->Width, Image1->Height);	//�]�wrect�d��j�p

		//�����Ȭ�b,g,r�覡�ƦC�U�h�A�ҥH�e�׹�ڤW��*3���ƭȤj�p			
		ByteNumber_Width = Image1->Width * 3;	//�w�]Ū��3channel�Ϲ�			
		pictureBox1->Image = Image1;	//���Image1��PictureBox1�u��W
		label1->Text = "source" + Image1->Width + "," + Image1->Height;
		isReprocess = false;
	}
}

System::Void Form1::dilationToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
	isOnePicture = true;
	if (isReady(isOnePicture)){
		MorphologicalImageProcessing(Morphological::Dilation, isReprocess);
		isReprocess = true;
		//�N�v����ܦbpictureBox1
		pictureBox2->Image = ResultImage;
		label1->Text = "source" + Image1->Width + "," + Image1->Height;
		label2->Text = "result" + ResultImageData->Width + "," + ResultImageData->Height;
	}
	else{
		label1->Text = "Source error";
	}
}

System::Void Form1::erosionToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
	isOnePicture = true;
	if (isReady(isOnePicture)){
		MorphologicalImageProcessing(Morphological::Erosion, isReprocess);
		isReprocess = true;
		//�N�v����ܦbpictureBox1
		pictureBox2->Image = ResultImage;
		label1->Text = "source" + Image1->Width + "," + Image1->Height;
		label2->Text = "result" + ResultImageData->Width + "," + ResultImageData->Height;
	}
	else{
		label1->Text = "Source error";
	}
}

System::Void Form1::openingToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
	isOnePicture = true;
	if (isReady(isOnePicture)){

		MorphologicalImageProcessing(Morphological::Opening, isReprocess);
		isReprocess = true;
		//�N�v����ܦbpictureBox1
		pictureBox2->Image = ResultImage;
		label1->Text = "source" + Image1->Width + "," + Image1->Height;
		label2->Text = "result" + ResultImageData->Width + "," + ResultImageData->Height;
	}
	else{
		label1->Text = "Source error";
	}
}

System::Void Form1::closingToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e){
	isOnePicture = true;
	if (isReady(isOnePicture)){
		MorphologicalImageProcessing(Morphological::Closing, isReprocess);
		isReprocess = true;
		//�N�v����ܦbpictureBox1
		pictureBox2->Image = ResultImage;
		label1->Text = "source" + Image1->Width + "," + Image1->Height;
		label2->Text = "result" + ResultImageData->Width + "," + ResultImageData->Height;
	}
	else{
		label1->Text = "Source error";
	}
}

int Form1::pixelbit(System::Drawing::Imaging::PixelFormat pixelformat){
		switch (pixelformat){
		case System::Drawing::Imaging::PixelFormat::Format24bppRgb://�T�q�D
			return 3;
			break;
		case System::Drawing::Imaging::PixelFormat::Format32bppRgb://�|�q�D
			return 4;
			break;
		default:
			return 3;
			break;
		}
	}

int Form1::resize(int res, int num){
		switch (res){
		case 0://���G�A�����ɫh+1
			if (num % 2 != 0)
				return num / 2 + 1;
			else
				return num / 2;
			break;
		}

	}

int Form1::HSIConverttoBOOL(bool isHSI, int vaule){
	switch (isHSI)
	{
	case true:
		if (vaule == 255)
			return 1;
		else if (vaule == 0)
			return 0;
		else
			return 1;
		break;
	case false:
		if (vaule == 1)
			return 255;
		else if (vaule == 0)
			return 0;
		else
			return 1;
		break;
	}
}

bool Form1::isReady(bool isOnePicture){
	if (isOnePicture){
		if (Image1 != nullptr){
			return true;
		}
		else
			return false;
	}
	else{
		if (Image2 != nullptr&&Image1 != nullptr){
			return true;
		}
		else
			return false;
	}
}

void Form1::MorphologicalImageProcessing(Morphological func, bool isReprocess){
		int DrawIn;
		switch (func){
		case Morphological::Dilation:
			DrawIn = 255;//white
			doMorphologicalProcessing(DrawIn, isReprocess);
			break;
		case Morphological::Erosion:
			DrawIn = 0;//black
			doMorphologicalProcessing(DrawIn, isReprocess);
			break;
		case Morphological::Opening:

			MorphologicalImageProcessing(Morphological::Erosion, isReprocess);
			MorphologicalImageProcessing(Morphological::Dilation, true);
			break;
		case Morphological::Closing:

			MorphologicalImageProcessing(Morphological::Dilation, isReprocess);
			MorphologicalImageProcessing(Morphological::Erosion, true);
			break;
		}
	}

void Form1::doMorphologicalProcessing(int DrawIn, bool isReprocess){
		rect = Rectangle(0, 0, Image1->Width, Image1->Height);
		if (isReprocess){
			//Src
			Image2 = gcnew Bitmap(Width_src, Height_src, System::Drawing::Imaging::PixelFormat::Format24bppRgb);
			Image2 = ResultImage;
			Width_src = Image2->Width;
			Height_src = Image2->Height;
			ImageData2 = Image2->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, Image2->PixelFormat);
			//Res
			ResultImage = gcnew Bitmap(Width_src, Height_src, System::Drawing::Imaging::PixelFormat::Format24bppRgb);
			ResultImageData = ResultImage->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, ResultImage->PixelFormat);

			ResultPtr = ResultImageData->Scan0;
			ptr = ImageData2->Scan0;
			R = (Byte*)(ResultPtr.ToPointer());
			p = (Byte*)(ptr.ToPointer());
		}
		else{
			//Src
			Width_src = Image1->Width;
			Height_src = Image1->Height;
			ImageData1 = Image1->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, Image1->PixelFormat);
			//Res
			ResultImage = gcnew Bitmap(Width_src, Height_src, System::Drawing::Imaging::PixelFormat::Format24bppRgb);
			ResultImageData = ResultImage->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, ResultImage->PixelFormat);
			ResultPtr = ResultImageData->Scan0;
			ptr = ImageData1->Scan0;
			R = (Byte*)(ResultPtr.ToPointer());
			p = (Byte*)(ptr.ToPointer());
		}

		ptr_bit = pixelbit(Image1->PixelFormat);
		ptr_bit2 = pixelbit(ResultImage->PixelFormat);
		for (int y = 0; y < Height_src; y++){
			for (int x = 0; x < Width_src; x++){
				if (x != 0 && y != 0 && x != Width_src - 1 && y != Height_src - 1){
					bool findEdge = false;
					if (p[ptr_bit*(x + Width_src*y)] == 255)
						findEdge = true;
					if (findEdge){
						for (int i = 0; i < 3; i++){
							vector<int> pixelTemp(9);
#pragma region pixelTemp
							pixelTemp[0] =
								HSIConverttoBOOL(isHSI, p[ptr_bit*((x - 1) + Width_src*(y - 1)) + i]);
							pixelTemp[1] =
								HSIConverttoBOOL(isHSI, p[ptr_bit*(x + Width_src*(y - 1)) + i]);
							pixelTemp[2] =
								HSIConverttoBOOL(isHSI, p[ptr_bit*((x + 1) + Width_src*(y - 1)) + i]);

							pixelTemp[3] =
								HSIConverttoBOOL(isHSI, p[ptr_bit*((x - 1) + Width_src*y) + i]);
							pixelTemp[4] =
								HSIConverttoBOOL(isHSI, p[ptr_bit*(x + Width_src*y) + i]);
							pixelTemp[5] =
								HSIConverttoBOOL(isHSI, p[ptr_bit*((x + 1) + Width_src*y) + i]);

							pixelTemp[6] =
								HSIConverttoBOOL(isHSI, p[ptr_bit*((x - 1) + Width_src*(y + 1)) + i]);
							pixelTemp[7] =
								HSIConverttoBOOL(isHSI, p[ptr_bit*(x + Width_src*(y + 1)) + i]);
							pixelTemp[8] =
								HSIConverttoBOOL(isHSI, p[ptr_bit*((x + 1) + Width_src*(y + 1)) + i]);
#pragma endregion
							bool isOnEdge = false;

							int j = 0;
							do{
								if (pixelTemp[j] == 0){
									isOnEdge = true;
									break;
								}
								else
									j++;
							} while (j < 9);

							if (isOnEdge){
								R[ptr_bit*((x - 1) + Width_src*(y - 1) + i)] = DrawIn;
								R[ptr_bit*(x + Width_src*(y - 1)) + i] = DrawIn;
								R[ptr_bit*((x + 1) + Width_src*(y - 1)) + i] = DrawIn;

								R[ptr_bit*((x - 1) + Width_src*y) + i] = DrawIn;
								R[ptr_bit*(x + Width_src*y) + i] = DrawIn;
								R[ptr_bit*((x + 1) + Width_src*y) + i] = DrawIn;

								R[ptr_bit*((x - 1) + Width_src*(y + 1)) + i] = DrawIn;
								R[ptr_bit*(x + Width_src*(y + 1)) + i] = DrawIn;
								R[ptr_bit*((x + 1) + Width_src*(y + 1)) + i] = DrawIn;
							}
							else{
								R[3 * (x + Width_src*y) + i] = p[3 * (x + Width_src*y) + i];
							}
						}
					}
					else{
						if (R[3 * (x + Width_src*y) + 0] != 255){
							R[3 * (x + Width_src*y) + 0] = p[3 * (x + Width_src*y) + 0];
							R[3 * (x + Width_src*y) + 1] = p[3 * (x + Width_src*y) + 1];
							R[3 * (x + Width_src*y) + 2] = p[3 * (x + Width_src*y) + 2];
						}
					}
				}
				else {
					if (R[3 * (x + Width_src*y) + 0] != 255){
						R[3 * (x + Width_src*y) + 0] = p[3 * (x + Width_src*y) + 0];
						R[3 * (x + Width_src*y) + 1] = p[3 * (x + Width_src*y) + 1];
						R[3 * (x + Width_src*y) + 2] = p[3 * (x + Width_src*y) + 2];
					}
				}
			}
		}
		//Unlock
		if (!isReprocess){
			Image1->UnlockBits(ImageData1);
			ResultImage->UnlockBits(ResultImageData);
		}
		else
		{
			Image2->UnlockBits(ImageData2);
			ResultImage->UnlockBits(ResultImageData);
		}
	}