#pragma once
#include "BoardObject.h"
#include "SnakeBoard.h"

ref class SnakeBoard;

ref class Pawn : public BoardObject{


public:

	Pawn(int, int, int, int, SnakeBoard^); //Get your x,y coords, and board size
	int Move() override; //The move command
	std::string print() override; //Print statement for the board
	bool getTick(); //get the tick status
private:
	bool tick = true;
	int direction;
	SnakeBoard^ board;
};