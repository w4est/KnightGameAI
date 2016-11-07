#include "stdafx.h"
#include "Pawn.h"

Pawn::Pawn(int x, int y, int sizex, int sizey, SnakeBoard^ newboard) : board(newboard){

	X = x;
	Y = y;
	sizeX = sizex;
	sizeY = sizey;
	
	direction = rand() % 2;
}

int Pawn::Move(){
	//Whether it is tick or toc changes the direction
	if (tick == true)
	{
		if (direction == 0 && X + 1 < sizeX){
			if (board->getBoard()[X + 1][Y]->print().compare("1") == 0){
				board->getBoard()[X][Y] = gcnew BoardObject();
				return 1;
			}
			else if(board->getBoard()[X + 1][Y]->print().compare("0") == 0){
				board->getBoard()[X + 1][Y] = this;
				board->getBoard()[X][Y] = gcnew BoardObject();
				X = X + 1;
			}
			
		}
		else if (direction == 1 && Y - 1 >= 0){
			if (board->getBoard()[X][Y - 1]->print().compare("1") == 0){
				board->getBoard()[X][Y] = gcnew BoardObject();
				return 1;
			}
			else if (board->getBoard()[X][Y - 1]->print().compare("0") == 0){
				board->getBoard()[X][Y - 1] = this;
				board->getBoard()[X][Y] = gcnew BoardObject();
				Y = Y - 1;
			}
			
		}
		
	}
	else {
		if (direction == 0 && X - 1 >= 0){
			if (board->getBoard()[X - 1][Y]->print().compare("1") == 0){
				board->getBoard()[X][Y] = gcnew BoardObject();
				return 1;
			}
			else if(board->getBoard()[X - 1][Y]->print().compare("0")==0){
				board->getBoard()[X - 1][Y] = this;
				board->getBoard()[X][Y] = gcnew BoardObject();
				X = X - 1;
			}
			
		}
		else if (direction == 1 && Y + 1 < sizeY){
			if (board->getBoard()[X][Y + 1]->print().compare("1") == 0){
				board->getBoard()[X][Y] = gcnew BoardObject();
				return 1;
			}
			else if (board->getBoard()[X][Y + 1]->print().compare("0") == 0){
				board->getBoard()[X][Y + 1] = this;
				board->getBoard()[X][Y] = gcnew BoardObject();
				Y = Y + 1;
			}
			
		}
		
	}
	tick = !tick;

	return 0;
}

std::string Pawn::print(){
	if (direction == 0)
	{
		return "2";
	}
	else{
		return "3";
	}
	//return "2";
}

bool Pawn::getTick(){
	return tick;
}