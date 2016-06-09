// ConsoleAppWithOpenCV249.cpp : 定義主控台應用程式的進入點。
//

#include "stdafx.h"
#include "Method.h"

using namespace cv;
using namespace std;

int stage = 0;
string select_Method;

string getFileName(int argc, char* argv[]){
	string pathString, temp;
	char pathChar[8192];

	if (argc > 0 && argv[1] != NULL){
		strcpy_s(pathChar, argv[1]); //Pointer to Char
		cout << pathChar << endl;
		pathString.assign(pathChar); //Char to String
	}
	else{
		cout << "拖曳檔案至視窗，或是輸入檔案路徑" << endl;
		getline(cin, temp);
		if (temp.size() == 0)
			temp = "D:\\Works\\0_Homework\\1042 視訊處理\\testv.avi";
		//-- Remove the " mark in head and tail
		if (pathString.assign(temp, 0, 1) == "\""){
			pathString = pathString.assign(temp, 1, temp.length() - 2);
		}
		else{
			pathString = temp;
		}
		cout << endl << "[Open file link : " << pathString << "]";
		do{
			cout << "選擇搜尋方式：" << endl
				<< "(1) TSS(Three step search)" << endl
				<< "(2) UCBDS(Unrestricted center-biased diamond search)" << endl;
			cin >> stage;
		} while (stage <= 0 || stage >= 3);
	}
	if (stage == 1)
		select_Method = "TSS(Three step search)";
	else if (stage == 2)
		select_Method = "UCBDS(Unrestricted center-biased diamond search)";
	return pathString;
}

int main(const int argc, char* argv[])
{
	Method myMethod;
	VideoCapture capture;
	string pathString = getFileName(argc, argv);
	Mat res;
	capture.open(pathString);
	if (capture.isOpened())
	{
		int count = 0;
		for (;;)
		{
			res;
			capture >> res;
			if (!res.empty())
			{
				//-- Do something here
				imshow("Source", res);

				unsigned long start = clock();
				myMethod.doSomethingAndShow(res, stage);
				unsigned long end = clock();

				system("cls");
				cout << select_Method << endl;
				printf("(R)ed arrow is from left to right\n(Y)ellow arrow is from right to left\n(B)lue point is show no movement block\n\nNow frame =%5d\nProcess time=%1.3f seconds", count, (end - start) / 1000.0);
				count++;
			}
			else
			{
				printf(" --(!) No captured frame -- Break!");
				system("pause");
				count = 0;
			}
			int c = waitKey(1);
			if ((char)c == 'c') { waitKey(0); }
		}
	}
	else{
		cout << "where is camera";
	}
	system("pause");
	return 0;
}

