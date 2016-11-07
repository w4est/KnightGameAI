#pragma once
#include "BoardObject.h"
#include "SnakeBoard.h"

ref class SnakeBoard;

ref class Knight : public BoardObject{


public:

	Knight(int, int,int,int, SnakeBoard^, int); //Get your x,y coords, and board size then finallythinking mode
	int Move() override; //The move command
	std::string print() override; //Print statement for the board
private:
	void ThinkBreadthFirst(); //Think command
	void ThinkDepthFirst();// Think DFS
	void ThinkAStar();
	void ThinkAStar2();
	void ThinkAverage();
	std::string checkMove(std::string, int,int,int,int); //Check Cell command , take a string of state now, and where you want to go in next state.
	int WinCondition();
	bool checkState(std::string, std::string);
	System::String^ moveList = "";
	SnakeBoard^ board;
	bool movementTick = true;
	int thinkingMode = 0;
	int DebugStates = 0;
	int DebugPath = 0;
	bool DebugPrintStatus = false;
};