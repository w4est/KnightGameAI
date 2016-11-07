#include "stdafx.h"
#include "MyForm.h"
#include <msclr\marshal_cppstd.h>
using namespace SnakeProject;

System::Void MyForm::StartButton_Click(System::Object^  sender, System::EventArgs^  e) {
	this->StartButton->Enabled = false;
	this->StartButton->Visible = false;
	this->comboBox1->Enabled = false;
	this->comboBox1->Visible = false;
	this->ByLabel->Enabled = false;
	this->ByLabel->Visible = false;
	this->SizeLabel->Enabled = false;
	this->SizeLabel->Visible = false;
	this->xBox->Enabled = false;
	this->xBox->Visible = false;
	this->yBox->Enabled = false;
	this->yBox->Visible = false;
	this->ObstacleBox->Enabled = false;
	this->ObstacleBox->Visible = false;
	this->ObstacleLabel->Enabled = false;
	this->ObstacleLabel->Visible = false;
	this->NumberLabel->Enabled = false;
	this->NumberLabel->Visible = false;
	this->slowButton->Visible = false;
	this->normalButton->Visible = false;
	this->fastButton->Visible = false;
	this->slowButton->Enabled = false;
	this->normalButton->Enabled = false;
	this->fastButton->Enabled = false;
	this->panel1->Visible = false;
	this->panel1->Enabled = false;
	this->speedlabel->Visible = false;
	this->thinkinglabel->Visible = false;
	this->thinkinglabel->Enabled = false;
	this->panel2->Visible = false;
	this->panel2->Enabled = false;
	this->AButton->Visible = false;
	this->AButton->Enabled = false;
	this->DFSButton->Visible = false;
	this->DFSButton->Enabled = false;
	this->AButton2->Visible = false;
	this->AButton2->Enabled = false;
	this->AAverageButton->Visible = false;
	this->AAverageButton->Enabled = false;

	board = gcnew SnakeBoard(Convert::ToInt16(xBox->Text), Convert::ToInt16(yBox->Text), Convert::ToInt16(ObstacleBox->Text), ThinkingMode); //Get input
	
	this->DoubleBuffered = true;
	this->SetStyle(ControlStyles::AllPaintingInWmPaint, true);
	this->SetStyle(ControlStyles::OptimizedDoubleBuffer, true);
	this->SetStyle(ControlStyles::UserPaint, true);

	drawGraphics();
	//Draw then activate the timer simulation!
	this->SnakeTimer->Enabled = true; 
	this->GraphicTimer->Enabled = true;
	

}

System::Void MyForm::SnakeTimer_Tick(System::Object^  sender, System::EventArgs^  e){
	//Do Brain ticks here. Have a slider to adjust simulation speed.
	board->performTurn();

}

System::Void MyForm::GraphicTimer_Tick(System::Object^  sender, System::EventArgs^  e){
	drawGraphics();
}

System::Void MyForm::drawGraphics(){
	std::string s = board->BoardToString(); 
	
	Graphics^ g = this->CreateGraphics();
	//Console::WriteLine(msclr::interop::marshal_as<String^>(s));
	// Create solid brush.
	
	SolidBrush^ blueBrush = gcnew SolidBrush(Color::Azure);
	SolidBrush^ redBrush = gcnew SolidBrush(Color::Red);
	SolidBrush^ greenBrush = gcnew SolidBrush(Color::Green);
	Pen^ blackPen = gcnew Pen(Color::Black);

	int x = 0;
	int y = 0;
	if (s.length() > 3600) //Larger Maps
	{
		for (int i = 0; i < (int)(s.length()); i++)
		{
			if (s[i].Equals('0'))
			{

				// Create rectangle.
				System::Drawing::Rectangle rect = System::Drawing::Rectangle(30 + y, 30 + x, 10, 10);

				g->FillRectangle(blueBrush, rect);
				g->DrawRectangle(blackPen, rect);

				y += 10;
			}
			else if (s[i].Equals('1'))
			{
				//Knights Are drawn

				// Create rectangle.
				System::Drawing::Rectangle rect = System::Drawing::Rectangle(30 + y, 30 + x, 10, 10);

				g->FillRectangle(greenBrush, rect);
				g->DrawRectangle(blackPen, rect);

				y += 10;
			}
			else if (s[i].Equals('2') || s[i].Equals('3'))
			{
				//Pawns Are drawn

				// Create rectangle.
				System::Drawing::Rectangle rect = System::Drawing::Rectangle(30 + y, 30 + x, 10, 10);

				g->FillRectangle(redBrush, rect);
				g->DrawRectangle(blackPen, rect);

				y += 10;
			}
			else if (s[i].Equals('|'))
			{
				x = x + 10;
				y = 0;
			}
		}
	}
	else{
		for (int i = 0; i < (int)(s.length()); i++)
		{
			if (s[i].Equals('0'))
			{

				// Create rectangle.
				System::Drawing::Rectangle rect = System::Drawing::Rectangle(30 + y, 30 + x, 20, 20);

				g->FillRectangle(blueBrush, rect);
				g->DrawRectangle(blackPen, rect);

				y += 20;
			}
			else if (s[i].Equals('1'))
			{
				//Knights Are drawn

				// Create rectangle.
				System::Drawing::Rectangle rect = System::Drawing::Rectangle(30 + y, 30 + x, 20, 20);

				g->FillRectangle(greenBrush, rect);
				g->DrawRectangle(blackPen, rect);

				y += 20;
			}
			else if (s[i].Equals('2') || s[i].Equals('3'))
			{
				//Pawns Are drawn

				// Create rectangle.
				System::Drawing::Rectangle rect = System::Drawing::Rectangle(30 + y, 30 + x, 20, 20);

				g->FillRectangle(redBrush, rect);
				g->DrawRectangle(blackPen, rect);

				y += 20;
			}
			else if (s[i].Equals('|'))
			{
				x = x + 20;
				y = 0;
			}
		}
	}
	

	delete g;
	GC::KeepAlive(board);
}


//Timing Controls

System::Void MyForm::slowButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	SnakeTimer->Interval = 900;
}
System::Void MyForm::normalButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	SnakeTimer->Interval = 400;
}
System::Void MyForm::fastButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	SnakeTimer->Interval = 100;
}

System::Void MyForm::BFSButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e){
	ThinkingMode = 0; //Set to bfs
}

System::Void MyForm::DFSButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e){
	ThinkingMode = 1; //Set to DFS
}
System::Void MyForm::AButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e){
	ThinkingMode = 2; //Set to A*
}
System::Void MyForm::AButton2_CheckedChanged(System::Object^  sender, System::EventArgs^  e){
	ThinkingMode = 3; //Set to A* 2
}
System::Void MyForm::AAverageButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e){
	ThinkingMode = 4; //Set to Average of A*
}