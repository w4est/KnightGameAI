#pragma once
#include "SnakeBoard.h"
namespace SnakeProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::Label^  NumberLabel;
	private: System::Windows::Forms::TextBox^  xBox;

	private: System::Windows::Forms::Timer^  SnakeTimer;
	private: System::Windows::Forms::Label^  SizeLabel;
	private: System::Windows::Forms::TextBox^  yBox;

	private: System::Windows::Forms::Label^  ByLabel;
	private: System::Windows::Forms::Button^  StartButton;
	private: System::Windows::Forms::Label^  ObstacleLabel;
	private: System::Windows::Forms::TextBox^  ObstacleBox;


	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::Timer^  GraphicTimer;
	private: System::Windows::Forms::RadioButton^  slowButton;
	private: System::Windows::Forms::RadioButton^  normalButton;
	private: System::Windows::Forms::RadioButton^  fastButton;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Label^  speedlabel;
	private: System::Windows::Forms::Label^  thinkinglabel;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::RadioButton^  BFSButton;
	private: System::Windows::Forms::RadioButton^  AButton;
	private: System::Windows::Forms::RadioButton^  DFSButton;



	protected:


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		SnakeBoard^ board;
	private: System::Windows::Forms::RadioButton^  AAverageButton;
	private: System::Windows::Forms::RadioButton^  AButton2;
			 int ThinkingMode = 0;

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Required method for Designer support - do not modify
			 /// the contents of this method with the code editor.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->components = (gcnew System::ComponentModel::Container());
				 this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
				 this->NumberLabel = (gcnew System::Windows::Forms::Label());
				 this->xBox = (gcnew System::Windows::Forms::TextBox());
				 this->SnakeTimer = (gcnew System::Windows::Forms::Timer(this->components));
				 this->SizeLabel = (gcnew System::Windows::Forms::Label());
				 this->yBox = (gcnew System::Windows::Forms::TextBox());
				 this->ByLabel = (gcnew System::Windows::Forms::Label());
				 this->StartButton = (gcnew System::Windows::Forms::Button());
				 this->ObstacleLabel = (gcnew System::Windows::Forms::Label());
				 this->ObstacleBox = (gcnew System::Windows::Forms::TextBox());
				 this->GraphicTimer = (gcnew System::Windows::Forms::Timer(this->components));
				 this->slowButton = (gcnew System::Windows::Forms::RadioButton());
				 this->normalButton = (gcnew System::Windows::Forms::RadioButton());
				 this->fastButton = (gcnew System::Windows::Forms::RadioButton());
				 this->panel1 = (gcnew System::Windows::Forms::Panel());
				 this->speedlabel = (gcnew System::Windows::Forms::Label());
				 this->thinkinglabel = (gcnew System::Windows::Forms::Label());
				 this->panel2 = (gcnew System::Windows::Forms::Panel());
				 this->AAverageButton = (gcnew System::Windows::Forms::RadioButton());
				 this->AButton2 = (gcnew System::Windows::Forms::RadioButton());
				 this->BFSButton = (gcnew System::Windows::Forms::RadioButton());
				 this->AButton = (gcnew System::Windows::Forms::RadioButton());
				 this->DFSButton = (gcnew System::Windows::Forms::RadioButton());
				 this->panel1->SuspendLayout();
				 this->panel2->SuspendLayout();
				 this->SuspendLayout();
				 // 
				 // comboBox1
				 // 
				 this->comboBox1->FormattingEnabled = true;
				 this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"One Knight", L"Two Knights (Unimplemented)" });
				 this->comboBox1->Location = System::Drawing::Point(55, 88);
				 this->comboBox1->Name = L"comboBox1";
				 this->comboBox1->Size = System::Drawing::Size(121, 21);
				 this->comboBox1->TabIndex = 0;
				 this->comboBox1->Text = L"One Knight";
				 // 
				 // NumberLabel
				 // 
				 this->NumberLabel->AutoSize = true;
				 this->NumberLabel->Location = System::Drawing::Point(55, 69);
				 this->NumberLabel->Name = L"NumberLabel";
				 this->NumberLabel->Size = System::Drawing::Size(96, 13);
				 this->NumberLabel->TabIndex = 1;
				 this->NumberLabel->Text = L"Number Of Knights";
				 // 
				 // xBox
				 // 
				 this->xBox->Location = System::Drawing::Point(343, 88);
				 this->xBox->Name = L"xBox";
				 this->xBox->Size = System::Drawing::Size(100, 20);
				 this->xBox->TabIndex = 2;
				 this->xBox->Text = L"10";
				 // 
				 // SnakeTimer
				 // 
				 this->SnakeTimer->Interval = 500;
				 this->SnakeTimer->Tick += gcnew System::EventHandler(this, &MyForm::SnakeTimer_Tick);
				 // 
				 // SizeLabel
				 // 
				 this->SizeLabel->AutoSize = true;
				 this->SizeLabel->Location = System::Drawing::Point(343, 69);
				 this->SizeLabel->Name = L"SizeLabel";
				 this->SizeLabel->Size = System::Drawing::Size(30, 13);
				 this->SizeLabel->TabIndex = 3;
				 this->SizeLabel->Text = L"Size:";
				 // 
				 // yBox
				 // 
				 this->yBox->Location = System::Drawing::Point(472, 88);
				 this->yBox->Name = L"yBox";
				 this->yBox->Size = System::Drawing::Size(100, 20);
				 this->yBox->TabIndex = 4;
				 this->yBox->Text = L"10";
				 // 
				 // ByLabel
				 // 
				 this->ByLabel->AutoSize = true;
				 this->ByLabel->Location = System::Drawing::Point(448, 88);
				 this->ByLabel->Name = L"ByLabel";
				 this->ByLabel->Size = System::Drawing::Size(18, 13);
				 this->ByLabel->TabIndex = 5;
				 this->ByLabel->Text = L"by";
				 // 
				 // StartButton
				 // 
				 this->StartButton->Location = System::Drawing::Point(243, 383);
				 this->StartButton->Name = L"StartButton";
				 this->StartButton->Size = System::Drawing::Size(102, 50);
				 this->StartButton->TabIndex = 6;
				 this->StartButton->Text = L"Start";
				 this->StartButton->UseVisualStyleBackColor = true;
				 this->StartButton->Click += gcnew System::EventHandler(this, &MyForm::StartButton_Click);
				 // 
				 // ObstacleLabel
				 // 
				 this->ObstacleLabel->AutoSize = true;
				 this->ObstacleLabel->Location = System::Drawing::Point(200, 69);
				 this->ObstacleLabel->Name = L"ObstacleLabel";
				 this->ObstacleLabel->Size = System::Drawing::Size(96, 13);
				 this->ObstacleLabel->TabIndex = 7;
				 this->ObstacleLabel->Text = L"Number Of Pawns:";
				 // 
				 // ObstacleBox
				 // 
				 this->ObstacleBox->Location = System::Drawing::Point(203, 89);
				 this->ObstacleBox->Name = L"ObstacleBox";
				 this->ObstacleBox->Size = System::Drawing::Size(100, 20);
				 this->ObstacleBox->TabIndex = 8;
				 this->ObstacleBox->Text = L"2";
				 // 
				 // GraphicTimer
				 // 
				 this->GraphicTimer->Tick += gcnew System::EventHandler(this, &MyForm::GraphicTimer_Tick);
				 // 
				 // slowButton
				 // 
				 this->slowButton->AutoSize = true;
				 this->slowButton->Checked = true;
				 this->slowButton->Location = System::Drawing::Point(3, 3);
				 this->slowButton->Name = L"slowButton";
				 this->slowButton->Size = System::Drawing::Size(48, 17);
				 this->slowButton->TabIndex = 9;
				 this->slowButton->TabStop = true;
				 this->slowButton->Text = L"Slow";
				 this->slowButton->UseVisualStyleBackColor = true;
				 this->slowButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::slowButton_CheckedChanged);
				 // 
				 // normalButton
				 // 
				 this->normalButton->AutoSize = true;
				 this->normalButton->Location = System::Drawing::Point(3, 27);
				 this->normalButton->Name = L"normalButton";
				 this->normalButton->Size = System::Drawing::Size(58, 17);
				 this->normalButton->TabIndex = 10;
				 this->normalButton->Text = L"Normal";
				 this->normalButton->UseVisualStyleBackColor = true;
				 this->normalButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::normalButton_CheckedChanged);
				 // 
				 // fastButton
				 // 
				 this->fastButton->AutoSize = true;
				 this->fastButton->Location = System::Drawing::Point(3, 51);
				 this->fastButton->Name = L"fastButton";
				 this->fastButton->Size = System::Drawing::Size(45, 17);
				 this->fastButton->TabIndex = 11;
				 this->fastButton->Text = L"Fast";
				 this->fastButton->UseVisualStyleBackColor = true;
				 this->fastButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::fastButton_CheckedChanged);
				 // 
				 // panel1
				 // 
				 this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->panel1->Controls->Add(this->slowButton);
				 this->panel1->Controls->Add(this->fastButton);
				 this->panel1->Controls->Add(this->normalButton);
				 this->panel1->Location = System::Drawing::Point(203, 180);
				 this->panel1->Name = L"panel1";
				 this->panel1->Size = System::Drawing::Size(200, 133);
				 this->panel1->TabIndex = 12;
				 // 
				 // speedlabel
				 // 
				 this->speedlabel->AutoSize = true;
				 this->speedlabel->Location = System::Drawing::Point(203, 161);
				 this->speedlabel->Name = L"speedlabel";
				 this->speedlabel->Size = System::Drawing::Size(107, 13);
				 this->speedlabel->TabIndex = 13;
				 this->speedlabel->Text = L"Set simulation speed:";
				 // 
				 // thinkinglabel
				 // 
				 this->thinkinglabel->AutoSize = true;
				 this->thinkinglabel->Location = System::Drawing::Point(52, 161);
				 this->thinkinglabel->Name = L"thinkinglabel";
				 this->thinkinglabel->Size = System::Drawing::Size(100, 13);
				 this->thinkinglabel->TabIndex = 14;
				 this->thinkinglabel->Text = L"Set Thinking Mode:";
				 // 
				 // panel2
				 // 
				 this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
				 this->panel2->Controls->Add(this->AAverageButton);
				 this->panel2->Controls->Add(this->AButton2);
				 this->panel2->Controls->Add(this->BFSButton);
				 this->panel2->Controls->Add(this->AButton);
				 this->panel2->Controls->Add(this->DFSButton);
				 this->panel2->Location = System::Drawing::Point(55, 180);
				 this->panel2->Name = L"panel2";
				 this->panel2->Size = System::Drawing::Size(130, 133);
				 this->panel2->TabIndex = 15;
				 // 
				 // AAverageButton
				 // 
				 this->AAverageButton->AutoSize = true;
				 this->AAverageButton->Location = System::Drawing::Point(3, 97);
				 this->AAverageButton->Name = L"AAverageButton";
				 this->AAverageButton->Size = System::Drawing::Size(116, 17);
				 this->AAverageButton->TabIndex = 16;
				 this->AAverageButton->Text = L"Average of Both A*";
				 this->AAverageButton->UseVisualStyleBackColor = true;
				 this->AAverageButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::AAverageButton_CheckedChanged);
				 // 
				 // AButton2
				 // 
				 this->AButton2->AutoSize = true;
				 this->AButton2->Location = System::Drawing::Point(3, 74);
				 this->AButton2->Name = L"AButton2";
				 this->AButton2->Size = System::Drawing::Size(90, 17);
				 this->AButton2->TabIndex = 16;
				 this->AButton2->Text = L"A* (Varient of)";
				 this->AButton2->UseVisualStyleBackColor = true;
				 this->AButton2->CheckedChanged += gcnew System::EventHandler(this, &MyForm::AButton2_CheckedChanged);
				 // 
				 // BFSButton
				 // 
				 this->BFSButton->AutoSize = true;
				 this->BFSButton->Checked = true;
				 this->BFSButton->Location = System::Drawing::Point(3, 3);
				 this->BFSButton->Name = L"BFSButton";
				 this->BFSButton->Size = System::Drawing::Size(45, 17);
				 this->BFSButton->TabIndex = 9;
				 this->BFSButton->TabStop = true;
				 this->BFSButton->Text = L"BFS";
				 this->BFSButton->UseVisualStyleBackColor = true;
				 this->BFSButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::BFSButton_CheckedChanged);
				 // 
				 // AButton
				 // 
				 this->AButton->AutoSize = true;
				 this->AButton->Location = System::Drawing::Point(3, 51);
				 this->AButton->Name = L"AButton";
				 this->AButton->Size = System::Drawing::Size(36, 17);
				 this->AButton->TabIndex = 11;
				 this->AButton->Text = L"A*";
				 this->AButton->UseVisualStyleBackColor = true;
				 this->AButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::AButton_CheckedChanged);
				 // 
				 // DFSButton
				 // 
				 this->DFSButton->AutoSize = true;
				 this->DFSButton->Location = System::Drawing::Point(3, 27);
				 this->DFSButton->Name = L"DFSButton";
				 this->DFSButton->Size = System::Drawing::Size(46, 17);
				 this->DFSButton->TabIndex = 10;
				 this->DFSButton->Text = L"DFS";
				 this->DFSButton->UseVisualStyleBackColor = true;
				 this->DFSButton->CheckedChanged += gcnew System::EventHandler(this, &MyForm::DFSButton_CheckedChanged);
				 // 
				 // MyForm
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(584, 462);
				 this->Controls->Add(this->panel2);
				 this->Controls->Add(this->thinkinglabel);
				 this->Controls->Add(this->speedlabel);
				 this->Controls->Add(this->panel1);
				 this->Controls->Add(this->ObstacleBox);
				 this->Controls->Add(this->ObstacleLabel);
				 this->Controls->Add(this->StartButton);
				 this->Controls->Add(this->ByLabel);
				 this->Controls->Add(this->yBox);
				 this->Controls->Add(this->SizeLabel);
				 this->Controls->Add(this->xBox);
				 this->Controls->Add(this->NumberLabel);
				 this->Controls->Add(this->comboBox1);
				 this->DoubleBuffered = true;
				 this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
				 this->Name = L"MyForm";
				 this->Text = L"Knight Game";
				 this->panel1->ResumeLayout(false);
				 this->panel1->PerformLayout();
				 this->panel2->ResumeLayout(false);
				 this->panel2->PerformLayout();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion





	private: System::Void StartButton_Click(System::Object^, System::EventArgs^);
			 System::Void SnakeTimer_Tick(System::Object^, System::EventArgs^);
			 System::Void drawGraphics();
			 System::Void GraphicTimer_Tick(System::Object^, System::EventArgs^);
			 System::Void slowButton_CheckedChanged(System::Object^, System::EventArgs^);
			 System::Void normalButton_CheckedChanged(System::Object^, System::EventArgs^);
			 System::Void fastButton_CheckedChanged(System::Object^, System::EventArgs^);
			 System::Void BFSButton_CheckedChanged(System::Object^, System::EventArgs^);
			 System::Void DFSButton_CheckedChanged(System::Object^, System::EventArgs^);
			 System::Void AButton_CheckedChanged(System::Object^, System::EventArgs^);
			 System::Void AButton2_CheckedChanged(System::Object^, System::EventArgs^);
			 System::Void AAverageButton_CheckedChanged(System::Object^, System::EventArgs^);
	};
}
