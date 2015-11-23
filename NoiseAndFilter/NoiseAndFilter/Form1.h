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
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected:
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  createNoiseToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  selectNoiseTypeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saltPeper5ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saltPeper10ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saltPeper20ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saltPeper50ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saltPeper70ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  gaussionNoise5ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  gaussionNoise10ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  gaussionNoise20ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  gaussionNoise5ToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  lowpassFilterToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  medianFilterToolStripMenuItem;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::PictureBox^  picBox_Src;

	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::PictureBox^  picBox_Res;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::ToolStripMenuItem^  kernel3x39ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  kernel3x310ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  kernel3x316ToolStripMenuItem;


	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
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
		SaltPeperClass^ mySaltPepper;

		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器
		/// 修改這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->createNoiseToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->selectNoiseTypeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saltPeper5ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saltPeper10ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saltPeper20ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saltPeper50ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saltPeper70ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->gaussionNoise5ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->gaussionNoise10ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->gaussionNoise20ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->gaussionNoise5ToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->lowpassFilterToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->medianFilterToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->picBox_Src = (gcnew System::Windows::Forms::PictureBox());
			this->picBox_Res = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->kernel3x39ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->kernel3x310ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->kernel3x316ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picBox_Src))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picBox_Res))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(18, 18);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->fileToolStripMenuItem,
					this->createNoiseToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1056, 30);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->openToolStripMenuItem });
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(49, 26);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(125, 26);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::openToolStripMenuItem_Click);
			// 
			// createNoiseToolStripMenuItem
			// 
			this->createNoiseToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->selectNoiseTypeToolStripMenuItem,
					this->lowpassFilterToolStripMenuItem, this->medianFilterToolStripMenuItem
			});
			this->createNoiseToolStripMenuItem->Name = L"createNoiseToolStripMenuItem";
			this->createNoiseToolStripMenuItem->Size = System::Drawing::Size(121, 26);
			this->createNoiseToolStripMenuItem->Text = L"Create noise";
			// 
			// selectNoiseTypeToolStripMenuItem
			// 
			this->selectNoiseTypeToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(10) {
				this->saltPeper5ToolStripMenuItem,
					this->saltPeper10ToolStripMenuItem, this->saltPeper20ToolStripMenuItem, this->saltPeper50ToolStripMenuItem, this->saltPeper70ToolStripMenuItem,
					this->toolStripSeparator1, this->gaussionNoise5ToolStripMenuItem, this->gaussionNoise10ToolStripMenuItem, this->gaussionNoise20ToolStripMenuItem,
					this->gaussionNoise5ToolStripMenuItem1
			});
			this->selectNoiseTypeToolStripMenuItem->Name = L"selectNoiseTypeToolStripMenuItem";
			this->selectNoiseTypeToolStripMenuItem->Size = System::Drawing::Size(219, 26);
			this->selectNoiseTypeToolStripMenuItem->Text = L"Select noise Type";
			// 
			// saltPeper5ToolStripMenuItem
			// 
			this->saltPeper5ToolStripMenuItem->Name = L"saltPeper5ToolStripMenuItem";
			this->saltPeper5ToolStripMenuItem->Size = System::Drawing::Size(243, 26);
			this->saltPeper5ToolStripMenuItem->Text = L"SaltPeper 5%";
			this->saltPeper5ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::saltPeper5ToolStripMenuItem_Click);
			// 
			// saltPeper10ToolStripMenuItem
			// 
			this->saltPeper10ToolStripMenuItem->Name = L"saltPeper10ToolStripMenuItem";
			this->saltPeper10ToolStripMenuItem->Size = System::Drawing::Size(243, 26);
			this->saltPeper10ToolStripMenuItem->Text = L"SaltPeper 10%";
			this->saltPeper10ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::saltPeper10ToolStripMenuItem_Click);
			// 
			// saltPeper20ToolStripMenuItem
			// 
			this->saltPeper20ToolStripMenuItem->Name = L"saltPeper20ToolStripMenuItem";
			this->saltPeper20ToolStripMenuItem->Size = System::Drawing::Size(243, 26);
			this->saltPeper20ToolStripMenuItem->Text = L"SaltPeper 20%";
			this->saltPeper20ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::saltPeper20ToolStripMenuItem_Click);
			// 
			// saltPeper50ToolStripMenuItem
			// 
			this->saltPeper50ToolStripMenuItem->Name = L"saltPeper50ToolStripMenuItem";
			this->saltPeper50ToolStripMenuItem->Size = System::Drawing::Size(243, 26);
			this->saltPeper50ToolStripMenuItem->Text = L"SaltPeper 50%";
			this->saltPeper50ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::saltPeper50ToolStripMenuItem_Click);
			// 
			// saltPeper70ToolStripMenuItem
			// 
			this->saltPeper70ToolStripMenuItem->Name = L"saltPeper70ToolStripMenuItem";
			this->saltPeper70ToolStripMenuItem->Size = System::Drawing::Size(243, 26);
			this->saltPeper70ToolStripMenuItem->Text = L"SaltPeper 70%";
			this->saltPeper70ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::saltPeper70ToolStripMenuItem_Click);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(240, 6);
			// 
			// gaussionNoise5ToolStripMenuItem
			// 
			this->gaussionNoise5ToolStripMenuItem->Name = L"gaussionNoise5ToolStripMenuItem";
			this->gaussionNoise5ToolStripMenuItem->Size = System::Drawing::Size(243, 26);
			this->gaussionNoise5ToolStripMenuItem->Text = L"Gaussion Noise 5%";
			this->gaussionNoise5ToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::gaussionNoise5ToolStripMenuItem_Click);
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
			// gaussionNoise5ToolStripMenuItem1
			// 
			this->gaussionNoise5ToolStripMenuItem1->Name = L"gaussionNoise5ToolStripMenuItem1";
			this->gaussionNoise5ToolStripMenuItem1->Size = System::Drawing::Size(243, 26);
			this->gaussionNoise5ToolStripMenuItem1->Text = L"Gaussion Noise 50%";
			this->gaussionNoise5ToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::gaussionNoise5ToolStripMenuItem1_Click);
			// 
			// lowpassFilterToolStripMenuItem
			// 
			this->lowpassFilterToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->kernel3x39ToolStripMenuItem,
					this->kernel3x310ToolStripMenuItem, this->kernel3x316ToolStripMenuItem
			});
			this->lowpassFilterToolStripMenuItem->Name = L"lowpassFilterToolStripMenuItem";
			this->lowpassFilterToolStripMenuItem->Size = System::Drawing::Size(219, 26);
			this->lowpassFilterToolStripMenuItem->Text = L"Lowpass filter";
			// 
			// medianFilterToolStripMenuItem
			// 
			this->medianFilterToolStripMenuItem->Name = L"medianFilterToolStripMenuItem";
			this->medianFilterToolStripMenuItem->Size = System::Drawing::Size(219, 26);
			this->medianFilterToolStripMenuItem->Text = L"Median filter";
			this->medianFilterToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::medianFilterToolStripMenuItem_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->picBox_Src);
			this->groupBox1->Location = System::Drawing::Point(12, 93);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(500, 500);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Source Image";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->picBox_Res);
			this->groupBox2->Location = System::Drawing::Point(533, 93);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(500, 500);
			this->groupBox2->TabIndex = 2;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Result Image";
			// 
			// picBox_Src
			// 
			this->picBox_Src->Dock = System::Windows::Forms::DockStyle::Fill;
			this->picBox_Src->Location = System::Drawing::Point(3, 20);
			this->picBox_Src->Name = L"picBox_Src";
			this->picBox_Src->Size = System::Drawing::Size(494, 477);
			this->picBox_Src->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->picBox_Src->TabIndex = 0;
			this->picBox_Src->TabStop = false;
			// 
			// picBox_Res
			// 
			this->picBox_Res->Dock = System::Windows::Forms::DockStyle::Fill;
			this->picBox_Res->Location = System::Drawing::Point(3, 20);
			this->picBox_Res->Name = L"picBox_Res";
			this->picBox_Res->Size = System::Drawing::Size(494, 477);
			this->picBox_Res->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->picBox_Res->TabIndex = 0;
			this->picBox_Res->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(505, 53);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(47, 15);
			this->label1->TabIndex = 3;
			this->label1->Text = L"label1";
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
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 14);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1056, 607);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picBox_Src))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->picBox_Res))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void saltPeper5ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void saltPeper10ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void saltPeper20ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void saltPeper50ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void saltPeper70ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void gaussionNoise5ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void gaussionNoise10ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void gaussionNoise20ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void gaussionNoise5ToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void kernel3x39ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void kernel3x310ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void kernel3x316ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void medianFilterToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
	};
}
