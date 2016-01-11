#pragma once

class Wavelet
{
public:
	Wavelet(char* fileName);
	System::Drawing::Bitmap^ getWavelet(char* fileName);

private:
	void openPic(char* fileName);
	void doWavelet();
	
	void figureOutLH(cv::Size input);
	void figureOutLH_Row(cv::Size input);
	void figureOutLH_Col(cv::Size input);
	
	System::Drawing::Bitmap^ MatToBmp(cv::Mat &input); //mat Тр bmp
	
	cv::Mat img_src;
	cv::Mat img_res;

	char *pathChar;	
	int Width_src;
	int Height_src;
	int TotalPixel;
};

