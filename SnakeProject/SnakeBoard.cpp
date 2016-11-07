#include "stdafx.h"
#include "SnakeBoard.h"
#include <sstream>
#include <msclr\marshal_cppstd.h>
#include <time.h>
SnakeBoard::SnakeBoard(int sizex, int sizey, int numPawns, int ThinkingMode)
{
	SizeX = sizex;
	SizeY = sizey;
	board = gcnew array<array<BoardObject^>^>(sizex);
	listKnights = gcnew array<Knight^>(1);
	
	//Initialize each element
	for (int i = 0; i < SizeX; i++){
		//Create an array for each array element
		board[i] = gcnew array<BoardObject^>(sizey);
		for (int j = 0; j < SizeY; j++){
			board[i][j] = gcnew BoardObject();	
		}
	}
	/* initialize random seed: */
	srand((unsigned) time(NULL));

	int tempx = rand() % SizeX;
	int tempy = rand() % SizeY;
	
	board[tempx][tempy] = gcnew Knight(tempx, tempy, SizeX, SizeY, this, ThinkingMode);
	listKnights[0] = (Knight^) board[tempx][tempy];

	//board[0][1] = gcnew Knight(0, 1, SizeX, SizeY, this, ThinkingMode);
	//listKnights[0] = (Knight^)board[0][1];
	//board[9][9] = gcnew Pawn(9, 9, SizeX, SizeY, this);
	//listPawns.Add(board[9][9]);

	if (numPawns > SizeX * SizeY)
	{

	}
	else{
		int i = 0;
		while (i != numPawns)
		{
			tempx = 1 + (rand() % (SizeX-1));
			tempy = 1 + (rand() % (SizeY-1));
			if (board[tempx][tempy]->print() == "0") //If it's a clear spot. add a pawn
			{
				board[tempx][tempy] = gcnew Pawn(tempx, tempy, SizeX, SizeY, this);
				listPawns.Add(board[tempx][tempy]);
				i++;
			}
		}
	}
}
/*
Obsolete
*/
System::Void SnakeBoard::AddObject(BoardObject^* newObject){
	//Add a Object.
	//Make sure a spot is available, then place
	board[1][1] = gcnew Knight(1, 1, SizeX, SizeY, this,0);
}

//Board to string function, so graphics function knows what to draw!

std::string SnakeBoard::BoardToString(){
	
	std::string s = "";
	for (int i = 0; i < SizeY; i++) //print is line by line, for each y, print X line
	{
		for (int j = 0; j < SizeX; j++){
				//Print out the boardobject's type
				std::stringstream a;
				a << board[j][i]->print();
				s = s + a.str();
			
		}
		s = s + '|';
	}
	
	return s;
}

SnakeBoard::~SnakeBoard(){
	System::GC::KeepAlive(board);
}

array<array<BoardObject^>^>^ SnakeBoard::getBoard(){
	return board;
}

System::Void SnakeBoard::performTurn(){
	int xP = 0;
	if (Thinking == false){ //Make sure we don't have double calls while thinking.
		if (Turn == false) //Knight's turn
		{
			Thinking = true;
			//If one or two knights
			if (listKnights[0]->Move() == 2)
			{
				//Tell MyForm to reset!
			}
			

			Turn = true;
			Thinking = false;
		}
		else{
			
			Thinking = true;
			//Move Pawns
			
			System::Collections::Generic::List<BoardObject^> tempList;
			for each(BoardObject^ thePawn in listPawns){
				
				xP = thePawn->Move();
				if (xP == 1)
				{
					tempList.Add(thePawn);
				}
			}
			for each(BoardObject^ thePawn in tempList){
				removePawn((Pawn^) thePawn);
			}
			tempList.Clear();
			
			tick = !tick;
			Turn = false;
			Thinking = false;
		}
	}
}

void SnakeBoard::removePawn(Pawn^ thePawn){ //Remove Pawns
	listPawns.Remove(thePawn);
}


int SnakeBoard::getMode(){
	return Mode;
}

bool SnakeBoard::getTick(){
	return tick;
}