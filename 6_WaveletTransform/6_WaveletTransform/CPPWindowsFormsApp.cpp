// CPPWindowsFormsApp.cpp: �D�n�M���ɡC

#include "stdafx.h"
#include "Form1.h"

using namespace System;
using namespace CPPWindowsFormsApp;

[STAThreadAttribute]

int main(array<System::String ^> ^args)
{
	//�إ߱���e�A���ҥ�windows����ı�ƮĪG
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	//�إߥD�����ð���
	Application::Run(gcnew Form1());	//��J���s�W��UI Form
    return 0;
}
