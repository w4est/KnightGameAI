#pragma once
#include "BoardObject.h"

ref class Cell
{
public:
	Cell();

	//Bread First Search
	//void BFS();
	//Depth First Search

	//A* Search
private:
	int X;
	int Y;
	bool searched = false;

	Cell^* East;
	Cell^* West;
	Cell^* North;
	Cell^* South;

	//BoardObject^* Piece;

};

