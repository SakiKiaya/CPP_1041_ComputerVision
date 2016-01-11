// CPPWindowsFormsApp.cpp: 主要專案檔。

#include "stdafx.h"
#include "Form1.h"

using namespace System;
using namespace CPPWindowsFormsApp;

[STAThreadAttribute]

int main(array<System::String ^> ^args)
{
	//建立控制項前，先啟用windows的視覺化效果
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	//建立主視窗並執行
	Application::Run(gcnew Form1());	//填入剛剛新增的UI Form
    return 0;
}
