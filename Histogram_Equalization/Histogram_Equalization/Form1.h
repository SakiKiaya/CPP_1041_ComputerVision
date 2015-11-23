#pragma once

namespace CPPWindowsFormsApp {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Form1 的摘要
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void);


	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  histogramToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  showToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  equalizationToolStripMenuItem;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::PictureBox^  picBox_Src;
	private: System::Windows::Forms::TabControl^  tabControl1;
	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::PictureBox^  picBox_Res;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>

#pragma region 自定義變數
		//宣告點陣圖的格式
		Bitmap^ Image1;
		//宣告圖像區域(設定為欲讀取、欲修正的圖像區域)
		Rectangle rect;
		//宣告為一BitmapData型態，表示像素值位置
		Imaging::BitmapData^ ImageData1;
		//宣告一int格式的指標
		IntPtr ptr;
		//宣告一個Byte格式的指標
		Byte* p;
		//宣告一個像素的bit長度，供指標移動參考
		int ptr_bit = 3;
		//common
		int Width_src;
		int Height_src;
		HistogramClass^ myHistogram;
		SaltPeperClass^ mySaltPepper;

		//enum

	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ToolStripMenuItem^  saltAndPaperNoiseToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  createNoiseToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem2;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem3;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem4;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem5;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem6;
	private: System::Windows::Forms::ToolStripMenuItem^  lopassFilterToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  medianFilterToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  kernel3x39ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  kernel3x310ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  kernel3x316ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  gaussToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  gaussionNoise10ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  gaussionNoise20ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  gaussionNoise50ToolStripMenuItem;

			 System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器
			 /// 修改這個方法的內容。
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
				 System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
				 System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
				 this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
				 this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->histogramToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->showToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->equalizationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->saltAndPaperNoiseToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->createNoiseToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->toolStripMenuItem2 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->toolStripMenuItem3 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->toolStripMenuItem4 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->toolStripMenuItem5 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->toolStripMenuItem6 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
				 this->gaussToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->gaussionNoise10ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->gaussionNoise20ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->gaussionNoise50ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->lopassFilterToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->kernel3x39ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->kernel3x310ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->kernel3x316ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->medianFilterToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
				 this->picBox_Src = (gcnew System::Windows::Forms::PictureBox());
				 this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
				 this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
				 this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
				 this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
				 this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
				 this->picBox_Res = (gcnew System::Windows::Forms::PictureBox());
				 this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
				 this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->menuStrip1->SuspendLayout();
				 this->groupBox1->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picBox_Src))->BeginInit();
				 this->tabControl1->SuspendLayout();
				 this->tabPage1->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
				 this->tabPage2->SuspendLayout();
				 this->groupBox2->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picBox_Res))->BeginInit();
				 this->SuspendLayout();
				 // 
				 // menuStrip1
				 // 
				 this->menuStrip1->ImageScalingSize = System::Drawing::Size(18, 18);
				 this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
					 this->fileToolStripMenuItem,
						 this->histogramToolStripMenuItem, this->saltAndPaperNoiseToolStripMenuItem
				 });
				 this->menuStrip1->Location = System::Drawing::Point(0, 0);
				 this->menuStrip1->Name = L"menuStrip1";
				 this->menuStrip1->Size = System::Drawing::Size(1056, 30);
				 this->menuStrip1->TabIndex = 0;
				 this->menuStrip1->Text = L"menuStrip1";
				 // 
				 // fileToolStripMenuItem
				 // 
				 this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
					 this->openToolStripMenuItem,
						 this->saveToolStripMenuItem
				 });
				 this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
				 this->fileToolStripMenuItem->Size = System::Drawing::Size(49, 26);
				 this->fileToolStripMenuItem->Text = L"File";
				 // 
				 // openToolStripMenuItem
				 // 
				 this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
				 this->openToolStripMenuItem->Size = System::Drawing::Size(162, 26);
				 this->openToolStripMenuItem->Text = L"Open";
				 this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::openToolStripMenuItem_Click);
				 // 
				 // saveToolStripMenuItem
				 // 
				 this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
				 this->saveToolStripMenuItem->Size = System::Drawing::Size(162, 26);
				 this->saveToolStripMenuItem->Text = L"Save";
				 this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::saveToolStripMenuItem_Click);
				 // 
				 // histogramToolStripMenuItem
				 // 
				 this->histogramToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
					 this->showToolStripMenuItem,
						 this->equalizationToolStripMenuItem
				 });
				 this->histogramToolStripMenuItem->Name = L"histogramToolStripMenuItem";
				 this->histogramToolStripMenuItem->Size = System::Drawing::Size(106, 26);
				 this->histogramToolStripMenuItem->Text = L"Histogram";
				 // 
				 // showToolStripMenuItem
				 // 
				 this->showToolStripMenuItem->Name = L"showToolStripMenuItem";
				 this->showToolStripMenuItem->Size = System::Drawing::Size(175, 26);
				 this->showToolStripMenuItem->Text = L"Show";
				 this->showToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::showToolStripMenuItem_Click);
				 // 
				 // equalizationToolStripMenuItem
				 // 
				 this->equalizationToolStripMenuItem->Name = L"equalizationToolStripMenuItem";
				 this->equalizationToolStripMenuItem->Size = System::Drawing::Size(175, 26);
				 this->equalizationToolStripMenuItem->Text = L"Equalization";
				 this->equalizationToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::equalizationToolStripMenuItem_Click);
				 // 
				 // saltAndPaperNoiseToolStripMenuItem
				 // 
				 this->saltAndPaperNoiseToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
					 this->createNoiseToolStripMenuItem,
						 this->lopassFilterToolStripMenuItem, this->medianFilterToolStripMenuItem
				 });
				 this->saltAndPaperNoiseToolStripMenuItem->Name = L"saltAndPaperNoiseToolStripMenuItem";
				 this->saltAndPaperNoiseToolStripMenuItem->Size = System::Drawing::Size(121, 26);
				 this->saltAndPaperNoiseToolStripMenuItem->Text = L"Create noise";
				 // 
				 // createNoiseToolStripMenuItem
				 // 
				 this->createNoiseToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(10) {
					 this->toolStripMenuItem2,
						 this->toolStripMenuItem3, this->toolStripMenuItem4, this->toolStripMenuItem5, this->toolStripMenuItem6, this->toolStripSeparator1,
						 this->gaussToolStripMenuItem, this->gaussionNoise10ToolStripMenuItem, this->gaussionNoise20ToolStripMenuItem, this->gaussionNoise50ToolStripMenuItem
				 });
				 this->createNoiseToolStripMenuItem->Name = L"createNoiseToolStripMenuItem";
				 this->createNoiseToolStripMenuItem->Size = System::Drawing::Size(219, 26);
				 this->createNoiseToolStripMenuItem->Text = L"Select noise Type";
				 // 
				 // toolStripMenuItem2
				 // 
				 this->toolStripMenuItem2->Name = L"toolStripMenuItem2";
				 this->toolStripMenuItem2->Size = System::Drawing::Size(243, 26);
				 this->toolStripMenuItem2->Text = L"SaltPepper 5%";
				 this->toolStripMenuItem2->Click += gcnew System::EventHandler(this, &Form1::toolStripMenuItem2_Click);
				 // 
				 // toolStripMenuItem3
				 // 
				 this->toolStripMenuItem3->Name = L"toolStripMenuItem3";
				 this->toolStripMenuItem3->Size = System::Drawing::Size(243, 26);
				 this->toolStripMenuItem3->Text = L"SaltPepper 10%";
				 this->toolStripMenuItem3->Click += gcnew System::EventHandler(this, &Form1::toolStripMenuItem3_Click);
				 // 
				 // toolStripMenuItem4
				 // 
				 this->toolStripMenuItem4->Name = L"toolStripMenuItem4";
				 this->toolStripMenuItem4->Size = System::Drawing::Size(243, 26);
				 this->toolStripMenuItem4->Text = L"SaltPepper 20%";
				 this->toolStripMenuItem4->Click += gcnew System::EventHandler(this, &Form1::toolStripMenuItem4_Click);
				 // 
				 // toolStripMenuItem5
				 // 
				 this->toolStripMenuItem5->Name = L"toolStripMenuItem5";
				 this->toolStripMenuItem5->Size = System::Drawing::Size(243, 26);
				 this->toolStripMenuItem5->Text = L"SaltPepper 50%";
				 this->toolStripMenuItem5->Click += gcnew System::EventHandler(this, &Form1::toolStripMenuItem5_Click);
				 // 
				 // toolStripMenuItem6
				 // 
				 this->toolStripMenuItem6->Name = L"toolStripMenuItem6";
				 this->toolStripMenuItem6->Size = System::Drawing::Size(243, 26);
				 this->toolStripMenuItem6->Text = L"SaltPepper 70%";
				 this->toolStripMenuItem6->Click += gcnew System::EventHandler(this, &Form1::toolStripMenuItem6_Click);
				 // 
				 // toolStripSeparator1
				 // 
				 this->toolStripSeparator1->Name = L"toolStripSeparator1";
				 this->toolStripSeparator1->Size = System::Drawing::Size(240, 6);
				 // 
				 // gaussToolStripMenuItem
				 // 
				 this->gaussToolStripMenuItem->Name = L"gaussToolStripMenuItem";
				 this->gaussToolStripMenuItem->Size = System::Drawing::Size(243, 26);
				 this->gaussToolStripMenuItem->Text = L"Gaussion Noise 5%";
				 this->gaussToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::gaussToolStripMenuItem_Click);
				 // 
				 // gaussionNoise10ToolStripMenuItem
				 // 
				 this->gaussionNoise10ToolStripMenuItem->Name = L"gaussionNoise10ToolStripMenuItem";
				 this->gaussionNoise10ToolStripMenuItem->Size = System::Drawing::Size(243, 26);
				 this->gaussionNoise10ToolStripMenuItem->Text = L"Gaussion Noise 10%";
				 this->gaussionNoise10ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::gaussionNoise10ToolStripMenuItem_Click);
				 // 
				 // gaussionNoise20ToolStripMenuItem
				 // 
				 this->gaussionNoise20ToolStripMenuItem->Name = L"gaussionNoise20ToolStripMenuItem";
				 this->gaussionNoise20ToolStripMenuItem->Size = System::Drawing::Size(243, 26);
				 this->gaussionNoise20ToolStripMenuItem->Text = L"Gaussion Noise 20%";
				 this->gaussionNoise20ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::gaussionNoise20ToolStripMenuItem_Click);
				 // 
				 // gaussionNoise50ToolStripMenuItem
				 // 
				 this->gaussionNoise50ToolStripMenuItem->Name = L"gaussionNoise50ToolStripMenuItem";
				 this->gaussionNoise50ToolStripMenuItem->Size = System::Drawing::Size(243, 26);
				 this->gaussionNoise50ToolStripMenuItem->Text = L"Gaussion Noise 50%";
				 this->gaussionNoise50ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::gaussionNoise50ToolStripMenuItem_Click);
				 // 
				 // lopassFilterToolStripMenuItem
				 // 
				 this->lopassFilterToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
					 this->kernel3x39ToolStripMenuItem,
						 this->kernel3x310ToolStripMenuItem, this->kernel3x316ToolStripMenuItem
				 });
				 this->lopassFilterToolStripMenuItem->Name = L"lopassFilterToolStripMenuItem";
				 this->lopassFilterToolStripMenuItem->Size = System::Drawing::Size(219, 26);
				 this->lopassFilterToolStripMenuItem->Text = L"Lowpass filter";
				 // 
				 // kernel3x39ToolStripMenuItem
				 // 
				 this->kernel3x39ToolStripMenuItem->Name = L"kernel3x39ToolStripMenuItem";
				 this->kernel3x39ToolStripMenuItem->Size = System::Drawing::Size(193, 26);
				 this->kernel3x39ToolStripMenuItem->Text = L"Kernel 3x3(9)";
				 this->kernel3x39ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::kernel3x39ToolStripMenuItem_Click);
				 // 
				 // kernel3x310ToolStripMenuItem
				 // 
				 this->kernel3x310ToolStripMenuItem->Name = L"kernel3x310ToolStripMenuItem";
				 this->kernel3x310ToolStripMenuItem->Size = System::Drawing::Size(193, 26);
				 this->kernel3x310ToolStripMenuItem->Text = L"Kernel 3x3(10)";
				 this->kernel3x310ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::kernel3x310ToolStripMenuItem_Click);
				 // 
				 // kernel3x316ToolStripMenuItem
				 // 
				 this->kernel3x316ToolStripMenuItem->Name = L"kernel3x316ToolStripMenuItem";
				 this->kernel3x316ToolStripMenuItem->Size = System::Drawing::Size(193, 26);
				 this->kernel3x316ToolStripMenuItem->Text = L"Kernel 3x3(16)";
				 this->kernel3x316ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::kernel3x316ToolStripMenuItem_Click);
				 // 
				 // medianFilterToolStripMenuItem
				 // 
				 this->medianFilterToolStripMenuItem->Name = L"medianFilterToolStripMenuItem";
				 this->medianFilterToolStripMenuItem->Size = System::Drawing::Size(219, 26);
				 this->medianFilterToolStripMenuItem->Text = L"Median filter";
				 this->medianFilterToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::medianFilterToolStripMenuItem_Click);
				 // 
				 // groupBox1
				 // 
				 this->groupBox1->Controls->Add(this->picBox_Src);
				 this->groupBox1->Location = System::Drawing::Point(12, 74);
				 this->groupBox1->Name = L"groupBox1";
				 this->groupBox1->Size = System::Drawing::Size(448, 506);
				 this->groupBox1->TabIndex = 1;
				 this->groupBox1->TabStop = false;
				 this->groupBox1->Text = L"Source Image";
				 // 
				 // picBox_Src
				 // 
				 this->picBox_Src->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->picBox_Src->Location = System::Drawing::Point(3, 20);
				 this->picBox_Src->Name = L"picBox_Src";
				 this->picBox_Src->Size = System::Drawing::Size(442, 483);
				 this->picBox_Src->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
				 this->picBox_Src->TabIndex = 0;
				 this->picBox_Src->TabStop = false;
				 // 
				 // tabControl1
				 // 
				 this->tabControl1->Controls->Add(this->tabPage1);
				 this->tabControl1->Controls->Add(this->tabPage2);
				 this->tabControl1->Location = System::Drawing::Point(466, 44);
				 this->tabControl1->Name = L"tabControl1";
				 this->tabControl1->SelectedIndex = 0;
				 this->tabControl1->Size = System::Drawing::Size(470, 551);
				 this->tabControl1->TabIndex = 3;
				 // 
				 // tabPage1
				 // 
				 this->tabPage1->Controls->Add(this->chart1);
				 this->tabPage1->Location = System::Drawing::Point(4, 23);
				 this->tabPage1->Name = L"tabPage1";
				 this->tabPage1->Padding = System::Windows::Forms::Padding(3);
				 this->tabPage1->Size = System::Drawing::Size(462, 524);
				 this->tabPage1->TabIndex = 0;
				 this->tabPage1->Text = L"Histogram Chart";
				 this->tabPage1->UseVisualStyleBackColor = true;
				 // 
				 // chart1
				 // 
				 chartArea1->Name = L"ChartArea1";
				 this->chart1->ChartAreas->Add(chartArea1);
				 legend1->Enabled = false;
				 legend1->Name = L"Legend1";
				 this->chart1->Legends->Add(legend1);
				 this->chart1->Location = System::Drawing::Point(6, 121);
				 this->chart1->Name = L"chart1";
				 series1->ChartArea = L"ChartArea1";
				 series1->Legend = L"Legend1";
				 series1->Name = L"Gray";
				 this->chart1->Series->Add(series1);
				 this->chart1->Size = System::Drawing::Size(450, 300);
				 this->chart1->TabIndex = 0;
				 this->chart1->Text = L"Gray Histogram";
				 // 
				 // tabPage2
				 // 
				 this->tabPage2->Controls->Add(this->groupBox2);
				 this->tabPage2->Location = System::Drawing::Point(4, 23);
				 this->tabPage2->Name = L"tabPage2";
				 this->tabPage2->Padding = System::Windows::Forms::Padding(3);
				 this->tabPage2->Size = System::Drawing::Size(462, 524);
				 this->tabPage2->TabIndex = 1;
				 this->tabPage2->Text = L"Result";
				 this->tabPage2->UseVisualStyleBackColor = true;
				 // 
				 // groupBox2
				 // 
				 this->groupBox2->Controls->Add(this->picBox_Res);
				 this->groupBox2->Location = System::Drawing::Point(7, 9);
				 this->groupBox2->Name = L"groupBox2";
				 this->groupBox2->Size = System::Drawing::Size(448, 506);
				 this->groupBox2->TabIndex = 3;
				 this->groupBox2->TabStop = false;
				 this->groupBox2->Text = L"Result Image";
				 // 
				 // picBox_Res
				 // 
				 this->picBox_Res->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->picBox_Res->Location = System::Drawing::Point(3, 20);
				 this->picBox_Res->Name = L"picBox_Res";
				 this->picBox_Res->Size = System::Drawing::Size(442, 483);
				 this->picBox_Res->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
				 this->picBox_Res->TabIndex = 1;
				 this->picBox_Res->TabStop = false;
				 // 
				 // openFileDialog1
				 // 
				 this->openFileDialog1->FileName = L"openFileDialog1";
				 // 
				 // label1
				 // 
				 this->label1->AutoSize = true;
				 this->label1->Location = System::Drawing::Point(196, 56);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(47, 15);
				 this->label1->TabIndex = 4;
				 this->label1->Text = L"label1";
				 // 
				 // Form1
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(8, 14);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(1056, 607);
				 this->Controls->Add(this->label1);
				 this->Controls->Add(this->tabControl1);
				 this->Controls->Add(this->groupBox1);
				 this->Controls->Add(this->menuStrip1);
				 this->MainMenuStrip = this->menuStrip1;
				 this->Name = L"Form1";
				 this->Text = L"Form1";
				 this->menuStrip1->ResumeLayout(false);
				 this->menuStrip1->PerformLayout();
				 this->groupBox1->ResumeLayout(false);
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picBox_Src))->EndInit();
				 this->tabControl1->ResumeLayout(false);
				 this->tabPage1->ResumeLayout(false);
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
				 this->tabPage2->ResumeLayout(false);
				 this->groupBox2->ResumeLayout(false);
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picBox_Res))->EndInit();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion
	private: System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void showToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void equalizationToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void toolStripMenuItem2_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void toolStripMenuItem3_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void toolStripMenuItem4_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void toolStripMenuItem5_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void toolStripMenuItem6_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void lopassFilterToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void medianFilterToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);

	private: System::Void kernel3x39ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void kernel3x310ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void kernel3x316ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void saveToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void gaussToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void gaussionNoise10ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void gaussionNoise20ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void gaussionNoise50ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	};
}
