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
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

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
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::PictureBox^  pictureBox4;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openFileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  houghTransformToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  getSobelToolStripMenuItem;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;

	protected:

	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;

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

		double sobel_thershold;
		int HT_thershold;

	private: System::Windows::Forms::ToolStripMenuItem^  getHoughToolStripMenuItem;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown2;
	private: System::Windows::Forms::Label^  label2;
			 mySobel^ mSobel;
#pragma endregion

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器
			 /// 修改這個方法的內容。
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
				 this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
				 this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
				 this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
				 this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
				 this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
				 this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->openFileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->houghTransformToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->getSobelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->getHoughToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
				 this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
				 this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->tableLayoutPanel1->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
				 this->menuStrip1->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->BeginInit();
				 this->SuspendLayout();
				 // 
				 // label1
				 // 
				 this->label1->AutoSize = true;
				 this->label1->Location = System::Drawing::Point(519, 2);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(52, 15);
				 this->label1->TabIndex = 0;
				 this->label1->Text = L"Sobel T";
				 // 
				 // tableLayoutPanel1
				 // 
				 this->tableLayoutPanel1->ColumnCount = 2;
				 this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 50)));
				 this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
					 50)));
				 this->tableLayoutPanel1->Controls->Add(this->pictureBox4, 1, 1);
				 this->tableLayoutPanel1->Controls->Add(this->pictureBox3, 0, 1);
				 this->tableLayoutPanel1->Controls->Add(this->pictureBox2, 1, 0);
				 this->tableLayoutPanel1->Controls->Add(this->pictureBox1, 0, 0);
				 this->tableLayoutPanel1->Location = System::Drawing::Point(12, 29);
				 this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
				 this->tableLayoutPanel1->RowCount = 2;
				 this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
				 this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
				 this->tableLayoutPanel1->Size = System::Drawing::Size(1060, 976);
				 this->tableLayoutPanel1->TabIndex = 1;
				 // 
				 // pictureBox4
				 // 
				 this->pictureBox4->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->pictureBox4->Location = System::Drawing::Point(533, 491);
				 this->pictureBox4->Name = L"pictureBox4";
				 this->pictureBox4->Size = System::Drawing::Size(524, 482);
				 this->pictureBox4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
				 this->pictureBox4->TabIndex = 3;
				 this->pictureBox4->TabStop = false;
				 // 
				 // pictureBox3
				 // 
				 this->pictureBox3->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->pictureBox3->Location = System::Drawing::Point(3, 491);
				 this->pictureBox3->Name = L"pictureBox3";
				 this->pictureBox3->Size = System::Drawing::Size(524, 482);
				 this->pictureBox3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
				 this->pictureBox3->TabIndex = 2;
				 this->pictureBox3->TabStop = false;
				 // 
				 // pictureBox2
				 // 
				 this->pictureBox2->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->pictureBox2->Location = System::Drawing::Point(533, 3);
				 this->pictureBox2->Name = L"pictureBox2";
				 this->pictureBox2->Size = System::Drawing::Size(524, 482);
				 this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
				 this->pictureBox2->TabIndex = 1;
				 this->pictureBox2->TabStop = false;
				 // 
				 // pictureBox1
				 // 
				 this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
				 this->pictureBox1->Location = System::Drawing::Point(3, 3);
				 this->pictureBox1->Name = L"pictureBox1";
				 this->pictureBox1->Size = System::Drawing::Size(524, 482);
				 this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
				 this->pictureBox1->TabIndex = 0;
				 this->pictureBox1->TabStop = false;
				 // 
				 // menuStrip1
				 // 
				 this->menuStrip1->ImageScalingSize = System::Drawing::Size(18, 18);
				 this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
					 this->fileToolStripMenuItem,
						 this->houghTransformToolStripMenuItem
				 });
				 this->menuStrip1->Location = System::Drawing::Point(0, 0);
				 this->menuStrip1->Name = L"menuStrip1";
				 this->menuStrip1->Size = System::Drawing::Size(1084, 27);
				 this->menuStrip1->TabIndex = 2;
				 this->menuStrip1->Text = L"menuStrip1";
				 // 
				 // fileToolStripMenuItem
				 // 
				 this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->openFileToolStripMenuItem });
				 this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
				 this->fileToolStripMenuItem->Size = System::Drawing::Size(45, 23);
				 this->fileToolStripMenuItem->Text = L"File";
				 // 
				 // openFileToolStripMenuItem
				 // 
				 this->openFileToolStripMenuItem->Name = L"openFileToolStripMenuItem";
				 this->openFileToolStripMenuItem->Size = System::Drawing::Size(150, 26);
				 this->openFileToolStripMenuItem->Text = L"Open File";
				 this->openFileToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::openFileToolStripMenuItem_Click);
				 // 
				 // houghTransformToolStripMenuItem
				 // 
				 this->houghTransformToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
					 this->getSobelToolStripMenuItem,
						 this->getHoughToolStripMenuItem
				 });
				 this->houghTransformToolStripMenuItem->Name = L"houghTransformToolStripMenuItem";
				 this->houghTransformToolStripMenuItem->Size = System::Drawing::Size(145, 23);
				 this->houghTransformToolStripMenuItem->Text = L"Hough Transform";
				 // 
				 // getSobelToolStripMenuItem
				 // 
				 this->getSobelToolStripMenuItem->Name = L"getSobelToolStripMenuItem";
				 this->getSobelToolStripMenuItem->Size = System::Drawing::Size(159, 26);
				 this->getSobelToolStripMenuItem->Text = L"get Sobel";
				 this->getSobelToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::getSobelToolStripMenuItem_Click);
				 // 
				 // getHoughToolStripMenuItem
				 // 
				 this->getHoughToolStripMenuItem->Name = L"getHoughToolStripMenuItem";
				 this->getHoughToolStripMenuItem->Size = System::Drawing::Size(159, 26);
				 this->getHoughToolStripMenuItem->Text = L"get Hough";
				 this->getHoughToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::getHoughToolStripMenuItem_Click);
				 // 
				 // openFileDialog1
				 // 
				 this->openFileDialog1->FileName = L"openFileDialog1";
				 // 
				 // numericUpDown1
				 // 
				 this->numericUpDown1->Location = System::Drawing::Point(584, 0);
				 this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000, 0, 0, 0 });
				 this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 20, 0, 0, 0 });
				 this->numericUpDown1->Name = L"numericUpDown1";
				 this->numericUpDown1->Size = System::Drawing::Size(120, 25);
				 this->numericUpDown1->TabIndex = 3;
				 this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 400, 0, 0, 0 });
				 // 
				 // numericUpDown2
				 // 
				 this->numericUpDown2->Location = System::Drawing::Point(796, 0);
				 this->numericUpDown2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 255, 0, 0, 0 });
				 this->numericUpDown2->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 20, 0, 0, 0 });
				 this->numericUpDown2->Name = L"numericUpDown2";
				 this->numericUpDown2->Size = System::Drawing::Size(120, 25);
				 this->numericUpDown2->TabIndex = 4;
				 this->numericUpDown2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 120, 0, 0, 0 });
				 // 
				 // label2
				 // 
				 this->label2->AutoSize = true;
				 this->label2->Location = System::Drawing::Point(710, 2);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(39, 15);
				 this->label2->TabIndex = 5;
				 this->label2->Text = L"HT T";
				 // 
				 // Form1
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(1084, 1027);
				 this->Controls->Add(this->label2);
				 this->Controls->Add(this->numericUpDown2);
				 this->Controls->Add(this->numericUpDown1);
				 this->Controls->Add(this->tableLayoutPanel1);
				 this->Controls->Add(this->label1);
				 this->Controls->Add(this->menuStrip1);
				 this->MainMenuStrip = this->menuStrip1;
				 this->Name = L"Form1";
				 this->Text = L"Form1";
				 this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
				 this->tableLayoutPanel1->ResumeLayout(false);
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
				 this->menuStrip1->ResumeLayout(false);
				 this->menuStrip1->PerformLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->EndInit();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion
	private: System::Void setThershold();
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Void getSobelToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void openFileToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void getHoughToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void numericUpDown1_ValueChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void numericUpDown2_ValueChanged(System::Object^  sender, System::EventArgs^  e);
	};
}
