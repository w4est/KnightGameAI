#pragma once
#include <string>

ref class BoardObject
{
public:
	BoardObject();
	virtual int Move();
	virtual std::string print();
protected:
	 //We can have either knights or pawns...
	int X;
	int Y;
	int sizeX;
	int sizeY;

};

