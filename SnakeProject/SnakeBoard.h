#pragma once
#include <vector>
#include "BoardObject.h"
#include "Cell.h"
#include "Knight.h"
#include "Pawn.h"
//class Knight;
ref class Pawn;

ref class SnakeBoard
{
public:
	SnakeBoard(int sizex, int sizey, int,int); //size of board, then numPawns, then Thinking Mode
	~SnakeBoard();
	System::Void performTurn();
	System::Void AddObject(BoardObject^*);
	std::string BoardToString();
	array<array<BoardObject^>^>^ getBoard();
	int getMode();
	void removePawn(Pawn^); //Removes the pawn
	bool getTick(); //Gettick of pawns

private: 
	int SizeX;
	int SizeY;
	cli::array<cli::array<BoardObject^>^>^ board;
	int Mode = 0; //What Algorithm is chosen
	bool Turn = false;
	cli::array<BoardObject^>^ listKnights;
	System::Collections::Generic::List<BoardObject^> listPawns;
	bool Thinking = false;
	bool tick = true; //Tick for movement of pawns
};

