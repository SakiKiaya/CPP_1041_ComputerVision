#include "stdafx.h"
#include "Wavelet.h"

using namespace cv;
using namespace System;

Wavelet::Wavelet(char* fileName)
{
	openPic(fileName);
}

void Wavelet::openPic(char* fileName){
	this->img_src = imread(fileName);
	this->Width_src = img_src.cols;
	this->Height_src = img_src.rows;
}

System::Drawing::Bitmap^ Wavelet::getWavelet(char* fileName){
	if (!img_src.data)
		openPic(fileName);
	doWavelet();
	return MatToBmp(img_res);
}

void Wavelet::doWavelet(){
	cv::Size input;

	//	First - Source size
	input.height = Height_src;
	input.width = Width_src;
	figureOutLH(input);

	//	Second - Half of Source 
	input.height /= 2;
	input.width /= 2;
	img_res.copyTo(img_src);
	figureOutLH(input);

	//	Third - Quarter of Source
	input.height /= 2;
	input.width /= 2;
	img_res.copyTo(img_src);
	figureOutLH(input);
}
void Wavelet::figureOutLH(cv::Size input){
	if (!img_res.data)
		img_res = cv::Mat(img_src.size(), img_src.type());
	figureOutLH_Row(input);
	figureOutLH_Col(input);
}

void Wavelet::figureOutLH_Row(cv::Size input){
	int halfWidth = input.width / 2;
	int temp, value1, value2, x_temp;
	bool isLeft = true;
	//	先做L，在做H，共做兩次
	for (int i = 0; i < 2; i++){
		for (int y = 0; y < Height_src; y++){
			for (int x = 0; x < Width_src; x += 2){
				if (x + 1 < Width_src - 1 && y + 1 < Height_src - 1){
					if (x < input.width - 1 && y < input.height - 1){
						value1 = img_src.at < Vec3b >(y, x + 1)[0];
						value2 = img_src.at < Vec3b >(y, x)[0];
						if (isLeft){
							//	ROW-L
							temp = (value1 + value2) / 2;
							x_temp = x / 2;
						}
						else{
							//	ROW-H	將從畫面的一半開始記錄
							temp = (value1 - value2) / 2 + 128;	//	類似正規化，讓它不要出現負數
							x_temp = x / 2 + halfWidth;
						}
					}
					else{
						temp = img_src.at < Vec3b >(y, x)[0];
					}
					img_res.at < Vec3b >(y, x_temp)[0] = temp;
					img_res.at < Vec3b >(y, x_temp)[1] = temp;
					img_res.at < Vec3b >(y, x_temp)[2] = temp;
				}
			}
		}
		isLeft = false;
	}
}

void Wavelet::figureOutLH_Col(cv::Size input){
	cv::Mat img_Row_Result;
	img_res.copyTo(img_Row_Result);
	int halfHeight = input.height / 2;
	int temp, value1, value2, y_temp;
	bool isLeft = true;
	//	先做L，在做H，共做兩次
	for (int i = 0; i < 2; i++){
		for (int x = 0; x < Height_src; x++){
			for (int y = 0; y < Width_src; y += 2){
				if (x + 1 < Width_src - 1 && y + 1 < Height_src - 1){
					//	在LH範圍內則進行運算
					if (x < input.width&&y < input.height){
						value1 = img_Row_Result.at < Vec3b >(y, x + 1)[0];
						value2 = img_Row_Result.at < Vec3b >(y, x)[0];
						if (isLeft){
							//	COL-L
							temp = (value1 + value2) / 2;
							y_temp = y / 2;
						}
						else{
							//	COL-H	將從畫面的一半開始記錄
							temp = (value1 - value2) / 2 + 128;	//	類似正規化，讓它不要出現負數
							y_temp = y / 2 + halfHeight;
						}
					}
					//	反之則記錄原本數值
					else{
						temp = img_Row_Result.at < Vec3b >(y, x)[0];
					}
					img_res.at < Vec3b >(y_temp, x)[0] = temp;
					img_res.at < Vec3b >(y_temp, x)[1] = temp;
					img_res.at < Vec3b >(y_temp, x)[2] = temp;
				}
			}
		}
		isLeft = false;
	}
}

System::Drawing::Bitmap^ Wavelet::MatToBmp(Mat &input)
{
	return gcnew System::Drawing::Bitmap(
		input.cols, 
		input.rows, 
		input.step, 
		System::Drawing::Imaging::PixelFormat::Format24bppRgb, 
		(System::IntPtr)input.ptr()
		);
}