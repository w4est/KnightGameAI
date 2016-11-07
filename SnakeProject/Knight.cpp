#include "stdafx.h"
#include "Knight.h"
#include <msclr\marshal_cppstd.h>
#include <iostream>
#include <regex>
#include <tuple>
#include "math.h"

Knight::Knight(int x, int y, int sizex, int sizey, SnakeBoard^ newboard, int theMode) : board(newboard){

	X = x;
	Y = y;
	sizeX = sizex;
	sizeY = sizey;
	//board = newboard;
	thinkingMode = theMode;
}

int Knight::Move(){ //Move on the board.

	if (moveList->Equals("") && WinCondition() == -1)
	{
		if (thinkingMode == 0){
			ThinkBreadthFirst();
		}
		else if (thinkingMode == 1){
			ThinkDepthFirst(); 
		}
		else if (thinkingMode ==2){
			ThinkAStar();
		}
		else if (thinkingMode == 3){
			ThinkAStar2();
		}
		else if (thinkingMode == 4){
			ThinkAverage();
		}
	}
	if (!moveList->Equals("D")){ //If the moves are not done...
		int tempX = 0;
		int tempY = 0;

		//Get the first two integers.
		msclr::interop::marshal_context context;
		std::string tempStr = context.marshal_as<std::string>(moveList);


		std::string::size_type sz;

		tempX = std::stoi(tempStr, &sz);
		//std::cout << (boardValues[layer - 1].at(f).substr(sz+1));
		tempY = std::stoi(tempStr.substr(sz + 1), &sz);
		std::cout << std::to_string(tempX) + "|" + std::to_string(tempY) << std::endl;

		std::string findStr = std::to_string(tempX) + "|" + std::to_string(tempY) + "M";
		size_t index = tempStr.find(findStr);
		size_t size = findStr.length();
		tempStr.replace(index, size, "");

		moveList = msclr::interop::marshal_as<System::String^>(tempStr);
		System::Console::WriteLine(moveList);

		if (board->getBoard()[tempX][tempY]->print() == "2" || board->getBoard()[tempX][tempY]->print() == "3"){ //If pawn. 
			
			board->removePawn((Pawn^)board->getBoard()[tempX][tempY] );
		}
		
		board->getBoard()[tempX][tempY] = this; //Update your position on board
		board->getBoard()[X][Y] = gcnew BoardObject(); //Replace old self with a blank
		X = tempX; //Tell yourself you've moved
		Y = tempY;
		DebugPath += 1;
	}
	if (moveList == "D"){
		if (DebugPrintStatus == false){
			System::Console::WriteLine("The Total Number of States used:" + DebugStates);
			System::Console::WriteLine("The number of Moves the knight takes: " + DebugPath);
			DebugPrintStatus = true;
		}
		return 1; //We can reset now!
	}
	return 0; //Everything is good
}
/*
Breadth First Search, 
Uses a Queue system

*/
void Knight::ThinkBreadthFirst(){

	//Manage a statespace
	std::string Moves = "";

	int tempX = X;
	int tempY = Y;
	int done = -1;

	movementTick = board->getTick(); //Synchronize the tick?
	//Create a Queue, Grab pawns and add them to the statespace
	std::vector<std::string> boardValues;

	Moves = std::to_string(tempX) + "|" + std::to_string(tempY) + "K";
	for (int i = 0; i < sizeX; i++){
		for (int j = 0; j < sizeY; j++){

			if (board->getBoard()[i][j]->print() == "2") //If it detects a pawn
			{
				//Add to initial statespace
				Moves += "|" + std::to_string(i) + "|" + std::to_string(j) + "P";
			}
			else if (board->getBoard()[i][j]->print() == "3")
			{
				//Add to initial statespace
				Moves += "|" + std::to_string(i) + "|" + std::to_string(j) + "Q";
			}
		}

	}
	if (movementTick == true){
		Moves.append("T");
	}
	else{
		Moves.append("F");
	}
	Moves.append("||");
	
	//Now add initial state to the vector
	boardValues.push_back(Moves); //Push initial state
	
	

	//test to see if working
	if (boardValues[0].compare(Moves) == 0){
		System::Console::WriteLine("Looking for next pawn");
		}
	//For each layer...
	int layer = 0; //Initialize layer
	 //Count how many pawns are on the board
	size_t count = std::count(boardValues.at(0).begin(), boardValues.at(0).end(), 'P');
	count += std::count(boardValues.at(0).begin(), boardValues.at(0).end(), 'Q');
	size_t current = 0;

	//Variables to hold states and add them
	std::string tempString;
	bool addState = false;

	if (count == 0){ //If nothing on board, we good
		done = 1;
	}
	while (done == -1)
	{
		//Increment layer if needed another layer of depth



					//Update the tempX and tempY based on parent
					std::string::size_type sz;

					tempX = std::stoi(boardValues[layer], &sz);
					//std::cout << (boardValues[layer - 1].at(f).substr(sz+1));
					tempY = std::stoi(boardValues[layer].substr(sz + 1), &sz);
					//std::cout << "tempY:" << tempY;

					addState = true;
					tempString = (checkMove(boardValues[layer], tempX, tempY, 2, 1));

					if (tempString.compare("") != 0){ //If an empty string is made. do not continue this path


						for (size_t i = 0, tempsize = boardValues.size(); i < tempsize; i++)
						{
							if (checkState(boardValues[i], tempString))
							{
								addState = false;
								break;
							}
						}
						if (addState == true){

							boardValues.push_back(tempString);
							current = std::count(boardValues.back().begin(), boardValues.back().end(), 'P');
							current += std::count(boardValues.back().begin(), boardValues.back().end(), 'Q');
							if (current < count)
							{
								//We done!
								done = 1;
								break;
							}
						}
					}

					addState = true;
					tempString = (checkMove(boardValues[layer], tempX, tempY, 2, -1));

					if (tempString.compare("") != 0){ //If an empty string is made. do not continue this path


						for (size_t i = 0, tempsize = boardValues.size(); i < tempsize; i++)
						{
							if (checkState(boardValues[i], tempString))
							{
								addState = false;
								break;
							}
						}
						if (addState == true){
							boardValues.push_back(tempString);
							current = std::count(boardValues.back().begin(), boardValues.back().end(), 'P');
							current += std::count(boardValues.back().begin(), boardValues.back().end(), 'Q');
							if (current < count)
							{
								//We done!
								done = 1;
								break;
							}
						}
					}

					addState = true;
					tempString = (checkMove(boardValues[layer], tempX, tempY, 1, -2));

					if (tempString.compare("") != 0){ //If an empty string is made. do not continue this path


						for (size_t i = 0, tempsize = boardValues.size(); i < tempsize; i++)
						{
							if (checkState(boardValues[i], tempString))
							{
								addState = false;
								break;
							}
						}
						if (addState == true){
							boardValues.push_back(tempString);
							current = std::count(boardValues.back().begin(), boardValues.back().end(), 'P');
							current += std::count(boardValues.back().begin(), boardValues.back().end(), 'Q');
							if (current < count)
							{
								//We done!
								done = 1;
								break;
							}
						}
					}

					addState = true;
					tempString = (checkMove(boardValues[layer], tempX, tempY, -1, -2));

					if (tempString.compare("") != 0){ //If an empty string is made. do not continue this path


						for (size_t i = 0, tempsize = boardValues.size(); i < tempsize; i++)
						{
							if (checkState(boardValues[i], tempString))
							{
								addState = false;
								break;
							}
						}
						if (addState == true){
							boardValues.push_back(tempString);
							current = std::count(boardValues.back().begin(), boardValues.back().end(), 'P');
							current += std::count(boardValues.back().begin(), boardValues.back().end(), 'Q');
							if (current < count)
							{
								//We done!
								done = 1;
								break;
							}
						}
					}

					addState = true;
					tempString = (checkMove(boardValues[layer], tempX, tempY, -2, -1));

					if (tempString.compare("") != 0){ //If an empty string is made. do not continue this path


						for (size_t i = 0, tempsize = boardValues.size(); i < tempsize; i++)
						{
							if (checkState(boardValues[i], tempString))
							{
								addState = false;
								break;
							}
						}
						if (addState == true){
							boardValues.push_back(tempString);
							current = std::count(boardValues.back().begin(), boardValues.back().end(), 'P');
							current += std::count(boardValues.back().begin(), boardValues.back().end(), 'Q');
							if (current < count)
							{
								//We done!
								done = 1;
								break;
							}
						}
					}

					addState = true;
					tempString = (checkMove(boardValues[layer], tempX, tempY, -2, 1));

					if (tempString.compare("") != 0){ //If an empty string is made. do not continue this path


						for (size_t i = 0, tempsize = boardValues.size(); i < tempsize; i++)
						{
							if (checkState(boardValues[i], tempString))
							{
								addState = false;
								break;
							}
						}
						if (addState == true){
							boardValues.push_back(tempString);
							current = std::count(boardValues.back().begin(), boardValues.back().end(), 'P');
							current += std::count(boardValues.back().begin(), boardValues.back().end(), 'Q');
							if (current < count)
							{
								//We done!
								done = 1;
								break;
							}
						}
					}

					addState = true;
					tempString = (checkMove(boardValues[layer], tempX, tempY, -1, 2));

					if (tempString.compare("") != 0){ //If an empty string is made. do not continue this path


						for (size_t i = 0, tempsize = boardValues.size(); i < tempsize; i++)
						{
							if (checkState(boardValues[i], tempString))
							{
								addState = false;
								break;
							}
						}
						if (addState == true){
							boardValues.push_back(tempString);
							current = std::count(boardValues.back().begin(), boardValues.back().end(), 'P');
							current += std::count(boardValues.back().begin(), boardValues.back().end(), 'Q');
							if (current < count)
							{
								//We done!
								done = 1;
								break;
							}
						}
					}

					addState = true;
					tempString = (checkMove(boardValues[layer], tempX, tempY, 1, 2));

					if (tempString.compare("") != 0){ //If an empty string is made. do not continue this path


						for (size_t i = 0, tempsize = boardValues.size(); i < tempsize; i++)
						{
							if (checkState(boardValues[i], tempString))
							{
								addState = false;
								break;
							}
						}
						if (addState == true){
							boardValues.push_back(tempString);
							current = std::count(boardValues.back().begin(), boardValues.back().end(), 'P');
							current += std::count(boardValues.back().begin(), boardValues.back().end(), 'Q');
							if (current < count)
							{
								//We done!
								done = 1;
								break;
							}
						}
					}
				
			
		



		layer++;

		//std::cout << "Layer" << layer << std::endl;
		


	}
	std::string newMoveList; //Set end character

	size_t index = boardValues.back().find("||");
	newMoveList = boardValues.back().substr(index + 2);
	if (current == 0){
		newMoveList.append("D");
	}
	moveList = msclr::interop::marshal_as<System::String^>(newMoveList); //Assign the movelist
	System::Console::WriteLine("Result is" + moveList); //Output to verify
	std::cout << "Number BoardStates : " << boardValues.size() << std::endl;
	DebugStates += (int)boardValues.size();
}

int Knight::WinCondition(){
	
	//If no more pawns....
	
	//return 0;

	//Else
	return -1;
}

std::string Knight::print(){
	return "1";
}

//Enter the current state vectors, function will look to see if that state exists already 
std::string Knight::checkMove(std::string inStr, int tempX, int tempY, int x, int y){
	std::string holderstr = inStr;

	//Movementtick update
	if (std::count(inStr.begin(), inStr.end(), 'T') == 1){
		movementTick = true;
	}
	else{
		movementTick = false;
	}

	if (tempX + x >= 0 && tempX + x < sizeX && tempY + y >= 0 && tempY + y < sizeY){


		//Find and update the Knight
		//For effieciency, use appends instead of +'s
		std::string findstr = std::to_string(tempX);
		findstr += "|";
		findstr += std::to_string(tempY);
		findstr += "K";
		size_t size = findstr.length();
		size_t index;
		index = holderstr.find(findstr);
		if (index == std::string::npos)
		{
			System::Console::WriteLine("we dun goofed");
		}
		holderstr.replace(index, size, std::to_string(tempX + x) + "|" + std::to_string(tempY + y) + "K");
		holderstr.append(std::to_string(tempX + x) + "|" + std::to_string(tempY + y) + "M");

		//Look for pawns, if they exist, remove it.
		//Cut down the Moves string, remove the pawn!
		//Also, for effieciency, use append instead of + to reduce buffer overhead.
		findstr = "|";
		findstr += std::to_string(tempX + x);
		findstr += "|";
		findstr += std::to_string(tempY + y);
		findstr += "P";
		size = findstr.length();
		index = holderstr.find(findstr);
		if (index != std::string::npos)
		{
			holderstr.replace(index, size, "");
		}
		//Look for pawns, if they exist, remove it.
		//Cut down the Moves string, remove the pawn!
		//Also, for effieciency, use append instead of + to reduce buffer overhead.
		findstr = "|";
		findstr += std::to_string(tempX + x);
		findstr += "|";
		findstr += std::to_string(tempY + y);
		findstr += "Q";
		size = findstr.length();
		index = holderstr.find(findstr);
		if (index != std::string::npos)
		{
			holderstr.replace(index, size, "");
		}
		
		//std::cout << holderstr << std::endl;
		//std::cout << "1: " << holderstr <<std::endl;
		
		//Now let's move the pawns!
		
		std::smatch m;
		std::regex e = std::regex("\\|(\\d)\\|(\\d)([PQ])");
		std::sregex_iterator next(holderstr.begin(), holderstr.end(), e);
		std::sregex_iterator end;
		std::string resultStr = holderstr;
		while (next != end) {
			
			std::smatch match = *next;
			std::regex finderE = std::regex("\\|" + match.str(1) + "\\|" + match.str(2) + match.str(3));
			//next++;
			
			
				if (strcmp(match.str(3).c_str(), "Q") == 0){ // Up and down

					if (std::stoi(match.str(2)) > 0 && movementTick == true){//Up check
						if (std::stoi(match.str(1)) == tempX + x && std::stoi(match.str(2)) - 1 == tempY + y)
						{
							//Kill the pawn entry. don't move it.
							resultStr = regex_replace(resultStr, finderE, "");
							
						}
						else{
							resultStr = regex_replace(resultStr, finderE, "|" + match.str(1) + "|" + std::to_string(std::stoi(match.str(2)) - 1) + "Q");
							
						}
					}
					else if (std::stoi(match.str(2)) < sizeY && movementTick == false){ //Down check
						if (std::stoi(match.str(1)) == tempX + x && std::stoi(match.str(2)) + 1 == tempY + y)
						{
							//Kill the pawn entry. don't move it.
							resultStr = regex_replace(resultStr, finderE, "");
							
						}
						else{
							resultStr = regex_replace(resultStr, finderE, "|" + match.str(1) + "|" + std::to_string(std::stoi(match.str(2)) + 1) + "Q");
							
						}
					}

				}
				if (strcmp(match.str(3).c_str(), "P") == 0){// Left and Right

					if (std::stoi(match.str(2)) > 0 && movementTick == false){//Left check
						if (std::stoi(match.str(1)) - 1 == tempX + x && std::stoi(match.str(2)) == tempY + y)
						{
							//Kill the pawn entry. don't move it.
							resultStr = regex_replace(resultStr, finderE, "");
							
						}
						else{
							resultStr = regex_replace(resultStr, finderE, "|" + std::to_string(std::stoi(match.str(1)) - 1) + "|" + match.str(2) + "P");
							
						}
					}
					else if (std::stoi(match.str(2)) < sizeX && movementTick == true){ //Right check
						if (std::stoi(match.str(1)) + 1 == tempX + x && std::stoi(match.str(2)) == tempY + y)
						{
							//Kill the pawn entry. don't move it.
							resultStr = regex_replace(resultStr, finderE, "");
							
						}
						else{
							resultStr = std::regex_replace(resultStr, finderE, "|" + std::to_string(std::stoi(match.str(1)) + 1) + "|" + match.str(2) + "P");
							
						}
					}
				}
			
			//std::cout << match.str(3) << "\n";
			next++;
		}
		 
		//Now Redo the statespace turn tick
		if (movementTick == true){
			resultStr = std::regex_replace(resultStr, std::regex("T"), "F");
		}
		else{
			resultStr = std::regex_replace(resultStr, std::regex("F"), "T");
		}

		
		holderstr = resultStr;
		//std::cout << "2: " << holderstr << std::endl;
		//Write this state to stack
		return holderstr;

		
		


	}
	return ""; //Not a valid state
}

bool Knight::checkState(std::string a, std::string b){

	size_t indexa = a.find("||");
	size_t indexb = b.find("||");

	if (a.substr(0, indexa).compare(b.substr(0, indexb)) == 0)
	{
		return true;
	}

	return false;
}


/*
Depth First Search,
Uses a Queue system

*/
void Knight::ThinkDepthFirst(){

	//Manage a statespace
	std::string Moves = "";

	int tempX = X;
	int tempY = Y;
	int done = -1;

	movementTick = board->getTick(); //Synchronize the tick?
	//Create a Queue, Grab pawns and add them to the statespace
	std::vector<std::string> boardValues;

	//State Space holder, will hold all previously done spaces.
	std::vector<std::string> previousValues;

	//Direction Holder for depth first search
	std::vector<int> previousDirection;

	Moves = std::to_string(tempX) + "|" + std::to_string(tempY) + "K";
	for (int i = 0; i < sizeX; i++){
		for (int j = 0; j < sizeY; j++){

			if (board->getBoard()[i][j]->print() == "2") //If it detects a pawn
			{
				//Add to initial statespace
				Moves += "|" + std::to_string(i) + "|" + std::to_string(j) + "P";
			}
			else if (board->getBoard()[i][j]->print() == "3")
			{
				//Add to initial statespace
				Moves += "|" + std::to_string(i) + "|" + std::to_string(j) + "Q";
			}
		}

	}
	if (movementTick == true){
		Moves.append("T");
	}
	else{
		Moves.append("F");
	}
	Moves.append("||");

	//Now add initial state to the vector
	boardValues.push_back(Moves); //Push initial state
	previousValues.push_back(Moves);
	previousDirection.push_back(0);

	//test to see if working
	if (boardValues[0].compare(Moves) == 0){
		System::Console::WriteLine("Looking for pawns");
	}
	//For each layer...
	int layer = 0; //Initialize layer
	//Count how many pawns are on the board
	size_t count = std::count(boardValues.at(0).begin(), boardValues.at(0).end(), 'P');
	count += std::count(boardValues.at(0).begin(), boardValues.at(0).end(), 'Q');
	size_t current = 0;

	if (count == 0){ //If nothing on board, we good
		done = 1;
	}
	
	std::string tempString;
	bool addState = false;
	
	while (done == -1)
	{
		//Increment layer if needed another layer of depth



		//Update the tempX and tempY based on parent
		std::string::size_type sz;

		tempX = std::stoi(boardValues.back(), &sz);
		//std::cout << (boardValues[layer - 1].at(f).substr(sz+1));
		tempY = std::stoi(boardValues.back().substr(sz + 1), &sz);
		//std::cout << "tempY:" << tempY;

		if (previousDirection.back() == 0){
			//Reset values
			addState = true;
			tempString = checkMove(boardValues.back(), tempX, tempY, 2, 1);
			previousDirection.back()++;

			if (tempString.compare("") != 0){ //If an empty string is made. do not continue this path
				for (size_t i = 0, tempsize = previousValues.size(); i < tempsize; i++)
				{
					if (checkState(previousValues[i], tempString))
					{
						
						addState = false;
						break;
					}
				}
				if (addState == true){
					//Add state and check it
					boardValues.push_back(tempString);
					previousValues.push_back(tempString);
					
					previousDirection.push_back(0);

					current = std::count(boardValues.back().begin(), boardValues.back().end(), 'P');
					current += std::count(boardValues.back().begin(), boardValues.back().end(), 'Q');
					if (current < count)
					{
						//We done!
						done = 1;
						break;
					}
				}
			}
		}

		if (previousDirection.back() == 1){
			//Reset values
			addState = true;
			tempString = checkMove(boardValues.back(), tempX, tempY, 2, -1);
			previousDirection.back()++;

			if (tempString.compare("") != 0){ //If an empty string is made. do not continue this path
				for (size_t i = 0, tempsize = previousValues.size(); i < tempsize; i++)
				{
					if (checkState(previousValues[i], tempString))
					{
						
						addState = false;
						break;
					}
				}
				if (addState == true){
					//Add state and check it
					boardValues.push_back(tempString);
					previousValues.push_back(tempString);
					
					previousDirection.push_back(0);

					current = std::count(boardValues.back().begin(), boardValues.back().end(), 'P');
					current += std::count(boardValues.back().begin(), boardValues.back().end(), 'Q');
					if (current < count)
					{
						//We done!
						done = 1;
						break;
					}
				}
			}
		}

		if (previousDirection.back() == 2){
			//Reset values
			addState = true;
			tempString = checkMove(boardValues.back(), tempX, tempY, 1, -2);
			previousDirection.back()++;

			if (tempString.compare("") != 0){ //If an empty string is made. do not continue this path
				for (size_t i = 0, tempsize = previousValues.size(); i < tempsize; i++)
				{
					if (checkState(previousValues[i], tempString))
					{
						
						addState = false;
						break;
					}
				}
				if (addState == true){
					//Add state and check it
					boardValues.push_back(tempString);
					previousValues.push_back(tempString);
					
					previousDirection.push_back(0);

					current = std::count(boardValues.back().begin(), boardValues.back().end(), 'P');
					current += std::count(boardValues.back().begin(), boardValues.back().end(), 'Q');
					if (current < count)
					{
						//We done!
						done = 1;
						break;
					}
				}
			}
		}

		if (previousDirection.back() == 3){
			//Reset values
			addState = true;
			tempString = checkMove(boardValues.back(), tempX, tempY, -1, -2);
			previousDirection.back()++;

			if (tempString.compare("") != 0){ //If an empty string is made. do not continue this path
				for (size_t i = 0, tempsize = previousValues.size(); i < tempsize; i++)
				{
					if (checkState(previousValues[i], tempString))
					{
						
						addState = false;
						break;
					}
				}
				if (addState == true){
					//Add state and check it
					boardValues.push_back(tempString);
					previousValues.push_back(tempString);
					
					previousDirection.push_back(0);

					current = std::count(boardValues.back().begin(), boardValues.back().end(), 'P');
					current += std::count(boardValues.back().begin(), boardValues.back().end(), 'Q');
					if (current < count)
					{
						//We done!
						done = 1;
						break;
					}
				}
			}
		}

		if (previousDirection.back() == 4){
			//Reset values
			addState = true;
			tempString = checkMove(boardValues.back(), tempX, tempY, -2, -1);
			previousDirection.back()++;

			if (tempString.compare("") != 0){ //If an empty string is made. do not continue this path
				for (size_t i = 0, tempsize = previousValues.size(); i < tempsize; i++)
				{
					if (checkState(previousValues[i], tempString))
					{
						
						addState = false;
						break;
					}
				}
				if (addState == true){
					//Add state and check it
					boardValues.push_back(tempString);
					previousValues.push_back(tempString);
				
					previousDirection.push_back(0);

					current = std::count(boardValues.back().begin(), boardValues.back().end(), 'P');
					current += std::count(boardValues.back().begin(), boardValues.back().end(), 'Q');
					if (current < count)
					{
						//We done!
						done = 1;
						break;
					}
				}
			}
		}

		if (previousDirection.back() == 5){
			//Reset values
			addState = true;
			tempString = checkMove(boardValues.back(), tempX, tempY, -2, 1);
			previousDirection.back()++;

			if (tempString.compare("") != 0){ //If an empty string is made. do not continue this path
				for (size_t i = 0, tempsize = previousValues.size(); i < tempsize; i++)
				{
					if (checkState(previousValues[i], tempString))
					{
						
						addState = false;
						break;
					}
				}
				if (addState == true){
					//Add state and check it
					boardValues.push_back(tempString);
					previousValues.push_back(tempString);
					
					previousDirection.push_back(0);

					current = std::count(boardValues.back().begin(), boardValues.back().end(), 'P');
					current += std::count(boardValues.back().begin(), boardValues.back().end(), 'Q');
					if (current < count)
					{
						//We done!
						done = 1;
						break;
					}
				}
			}
		}
		
		if (previousDirection.back() == 6){
			//Reset values
			addState = true;
			tempString = checkMove(boardValues.back(), tempX, tempY, -1, 2);
			previousDirection.back()++;

			if (tempString.compare("") != 0){ //If an empty string is made. do not continue this path
				for (size_t i = 0, tempsize = previousValues.size(); i < tempsize; i++)
				{
					if (checkState(previousValues[i], tempString))
					{
						
						addState = false;
						break;
					}
				}
				if (addState == true){
					//Add state and check it
					boardValues.push_back(tempString);
					previousValues.push_back(tempString);
					
					previousDirection.push_back(0);

					current = std::count(boardValues.back().begin(), boardValues.back().end(), 'P');
					current += std::count(boardValues.back().begin(), boardValues.back().end(), 'Q');
					if (current < count)
					{
						//We done!
						done = 1;
						break;
					}
				}
			}
		}

		if (previousDirection.back() == 7){
			//Reset values
			addState = true;
			tempString = checkMove(boardValues.back(), tempX, tempY, 1, 2);
			previousDirection.back()++;

			if (tempString.compare("") != 0){ //If an empty string is made. do not continue this path
				for (size_t i = 0, tempsize = previousValues.size(); i < tempsize; i++)
				{
					if (checkState(previousValues[i], tempString))
					{
						
						addState = false;
						break;
					}
				}
				if (addState == true){
					//Add state and check it
					boardValues.push_back(tempString);
					previousValues.push_back(tempString);
					
					previousDirection.push_back(0);

					current = std::count(boardValues.back().begin(), boardValues.back().end(), 'P');
					current += std::count(boardValues.back().begin(), boardValues.back().end(), 'Q');
					if (current < count)
					{
						//We done!
						done = 1;
						break;
					}
				}
			}
		}

		if (previousDirection.back() == 8){
			boardValues.pop_back();
			previousDirection.pop_back();
		}






		layer++;

		//std::cout << "Layer" << layer << std::endl;



	}
	std::string newMoveList; //Set end character

	size_t index = boardValues.back().find("||");
	newMoveList = boardValues.back().substr(index + 2);
	if (current == 0){
		newMoveList.append("D");
	}
	moveList = msclr::interop::marshal_as<System::String^>(newMoveList); //Assign the movelist
	System::Console::WriteLine("Result is" + moveList); //Output to verify
	std::cout << "Number BoardStates : " << previousValues.size() << std::endl;
	DebugStates += (int)boardValues.size();
}

void Knight::ThinkAStar(){
	//Manage a statespace
	std::string Moves = "";

	int tempX = X;
	int tempY = Y;
	int done = -1;

	movementTick = board->getTick(); //Synchronize the tick?
	//Create a Queue, Grab pawns and add them to the statespace
	std::vector<std::string> boardValues;

	//Create A Vector of Pawn Spaces
	std::vector<std::tuple<int, int>> PawnList;
	

	Moves = std::to_string(tempX) + "|" + std::to_string(tempY) + "K";
	for (int i = 0; i < sizeX; i++){
		for (int j = 0; j < sizeY; j++){

			if (board->getBoard()[i][j]->print() == "2") //If it detects a pawn
			{
				//Add to initial statespace
				Moves += "|" + std::to_string(i) + "|" + std::to_string(j) + "P";
				PawnList.push_back(std::make_tuple(i, j));
			}
			else if (board->getBoard()[i][j]->print() == "3")
			{
				//Add to initial statespace
				Moves += "|" + std::to_string(i) + "|" + std::to_string(j) + "Q";
				PawnList.push_back(std::make_tuple(i, j));
			}
		}

	}
	if (movementTick == true){
		Moves.append("T");
	}
	else{
		Moves.append("F");
	}
	Moves.append("||");

	//Now add initial state to the vector
	boardValues.push_back(Moves); //Push initial state



	//test to see if working
	if (boardValues[0].compare(Moves) == 0){
		System::Console::WriteLine("Looking for next pawn");
	}
	//For each layer...
	int layer = 0; //Initialize layer
	//Count how many pawns are on the board
	size_t count = std::count(boardValues.at(0).begin(), boardValues.at(0).end(), 'P');
	count += std::count(boardValues.at(0).begin(), boardValues.at(0).end(), 'Q');
	size_t current = count;
	
	//Variables to hold states and add them
	std::string tempString;
	bool addState = false;
	int xCounter = 0;
	int yCounter = 0;
	int xMax = 9000;
	int yMax = 9000;
	int xCheck = 0;
	int yCheck = 0;
	int BFSMode = 0;

	if (count == 0){ //If nothing on board, we good
		done = 1;
	}
	


		//Calculate closest pawn heuristic.
		for (size_t i = 0, tempsize = PawnList.size(); i < tempsize; i++)
		{
			xCounter = std::get<0>(PawnList.at(i)); //Get distances
			yCounter = std::get<1>(PawnList.at(i));
			xCheck = xCounter - tempX;
			yCheck = yCounter - tempY;
			xCheck = abs(xCheck);
			yCheck = abs(yCheck);
			if ((xCheck + yCheck) < (abs(xMax-tempX) + abs(yMax-tempY)))
			{
				xMax = xCounter;
				yMax = yCounter; //Hold maxes for searching pawns! (mins in this case)
			}
		}


		while (done == -1)
		{
			//Increment layer if needed another layer of depth
			if (layer == boardValues.size()){
				System::Console::WriteLine("we donezo");
			}
			

			//Update the tempX and tempY based on parent
			std::string::size_type sz;

			tempX = std::stoi(boardValues[layer], &sz);
			//std::cout << (boardValues[layer - 1].at(f).substr(sz+1));
			tempY = std::stoi(boardValues[layer].substr(sz + 1), &sz);
			//std::cout << "tempY:" << tempY;
			xCounter = std::abs((xMax - tempX));
			yCounter = std::abs((yMax - tempY));


			addState = true;
			if (xCounter + yCounter < 4 || BFSMode == 1) //If we are close!
			{
				BFSMode = 1;
				for (int j = 0; j < 8; j++){
					

					if (j == 0)
					{
						addState = true;
						tempString = (checkMove(boardValues[layer], tempX, tempY, 2, 1));
					}
					if (j == 1)
					{
						addState = true;
						tempString = (checkMove(boardValues[layer], tempX, tempY, 2, -1));
					}
					if (j == 2)
					{
						addState = true;
						tempString = (checkMove(boardValues[layer], tempX, tempY, 1, -2));
					}
					if (j == 3)
					{
						addState = true;
						tempString = (checkMove(boardValues[layer], tempX, tempY, -1, -2));
					}
					if (j == 4)
					{
						addState = true;
						tempString = (checkMove(boardValues[layer], tempX, tempY, -2, -1));
					}
					if (j == 5)
					{
						addState = true;
						tempString = (checkMove(boardValues[layer], tempX, tempY, -2, 1));
					}
					if (j == 6)
					{
						addState = true;
						tempString = (checkMove(boardValues[layer], tempX, tempY, -1, 2));
					}
					if (j == 7)
					{
						addState = true;
						tempString = (checkMove(boardValues[layer], tempX, tempY, 1, 2));
					}

					if (tempString.compare("") != 0){ //If an empty string is made. do not continue this path


						for (size_t i = 0, tempsize = boardValues.size(); i < tempsize; i++)
						{
							if (checkState(boardValues[i], tempString))
							{
								addState = false;
								break;
							}
						}
						if (addState == true){
							boardValues.push_back(tempString);
							current = std::count(boardValues.back().begin(), boardValues.back().end(), 'P');
							current += std::count(boardValues.back().begin(), boardValues.back().end(), 'Q');
							if (current < count)
							{
								//We done!
								done = 1;
								break;
							}
						}
					}
				}
			}
			else if(BFSMode != 1){
				
					addState = true;
					
					if (xMax - tempX <= 0 && yMax - tempY <= 0){
						if (xCounter > yCounter)
						{
							//Go more left
							tempString = (checkMove(boardValues[layer], tempX, tempY, -2, -1));
						}
						else{
							//Go more down
							tempString = (checkMove(boardValues[layer], tempX, tempY, -1, -2));
						}
					}

					else if (xMax - tempX <= 0 && yMax - tempY >= 0){
						if (xCounter > yCounter)
						{
							//Go more left
							tempString = (checkMove(boardValues[layer], tempX, tempY, -2, 1));
						}
						else{
							//Go more Up
							tempString = (checkMove(boardValues[layer], tempX, tempY, -1, 2));
						}
					}
					else if (xMax - tempX >= 0 && yMax - tempY <= 0){
						if (xCounter > yCounter)
						{
							//Go more Right
							tempString = (checkMove(boardValues[layer], tempX, tempY, 2, -1));
						}
						else{
							//Go more down
							tempString = (checkMove(boardValues[layer], tempX, tempY, 1, -2));
						}
					}
					else if (xMax - tempX >= 0 && yMax - tempY >= 0){
						if (xCounter > yCounter)
						{
							//Go more Right
							tempString = (checkMove(boardValues[layer], tempX, tempY, 2, 1));
						}
						else{
							//Go more Up
							tempString = (checkMove(boardValues[layer], tempX, tempY, 1, 2));
						}
					}
					/*
					Weird edge cases
					*/
					
					if (xMax - tempX == 0){
						if (yMax - tempY > 0)
						{
							//Go more Up
							tempString = (checkMove(boardValues[layer], tempX, tempY, 1, 2));
							if (tempString.compare("") == 0)
							{

								//Go more Up... to the left
								tempString = (checkMove(boardValues[layer], tempX, tempY, -1, 2));
							}
							if (tempString.compare("") == 0)
							{

								//Go more Up... to the left
								tempString = (checkMove(boardValues[layer], tempX, tempY, -2, 1));
							}
							if (tempString.compare("") == 0)
							{

								//Go more Up... to the left
								tempString = (checkMove(boardValues[layer], tempX, tempY, 2, 1));
							}
						}



						if (yMax - tempY < 0)
						{
							//Go more down
							tempString = (checkMove(boardValues[layer], tempX, tempY, 1, -2));
							if (tempString.compare("") == 0)
							{
								//Go more down... 2nd attempt
								tempString = (checkMove(boardValues[layer], tempX, tempY, -1, -2));
							}
							if (tempString.compare("") == 0)
							{
								//Go more down... 2nd attempt
								tempString = (checkMove(boardValues[layer], tempX, tempY, -2, -1));
							}
							if (tempString.compare("") == 0)
							{
								//Go more down... 2nd attempt
								tempString = (checkMove(boardValues[layer], tempX, tempY, 2, -1));
							}
						}
					}
					if (yMax - tempY == 0){
						if (xMax - tempX > 0)
						{
							//Go more Right
							tempString = (checkMove(boardValues[layer], tempX, tempY, 2, 1));
							if (tempString.compare("") == 0)
							{
								//Go more Right...again
								tempString = (checkMove(boardValues[layer], tempX, tempY, 2, -1));
							}
							if (tempString.compare("") == 0)
							{
								//Go more Right...again
								tempString = (checkMove(boardValues[layer], tempX, tempY, 1, -2));
							}
							if (tempString.compare("") == 0)
							{
								//Go more Right...again
								tempString = (checkMove(boardValues[layer], tempX, tempY, 1, 2));
							}
						}
						if (xMax - tempX < 0)
						{
							//Go more Left
							tempString = (checkMove(boardValues[layer], tempX, tempY, -2, 1));
							if (tempString.compare("") == 0)
							{
								//Go more Left... 2nd attempt
								tempString = (checkMove(boardValues[layer], tempX, tempY, -2, -1));
							}
							if (tempString.compare("") == 0)
							{
								//Go more Left... 2nd attempt
								tempString = (checkMove(boardValues[layer], tempX, tempY, -1, -2));
							}
							if (tempString.compare("") == 0)
							{
								//Go more Left... 2nd attempt
								tempString = (checkMove(boardValues[layer], tempX, tempY, -1, 2));
							}
						}
					}
					
					if (tempString.compare("") != 0){ //If an empty string is made. do not continue this path


						/*for (size_t i = 0, tempsize = boardValues.size(); i < tempsize; i++)
						{
							if (checkState(boardValues[i], tempString))
							{
								addState = false;
								
								break;
							}
						}*/
						if (addState == true){

							boardValues.push_back(tempString);
							current = std::count(boardValues.back().begin(), boardValues.back().end(), 'P');
							current += std::count(boardValues.back().begin(), boardValues.back().end(), 'Q');
							if (current < count)
							{

								//We done!
								done = 1;
								break;
							}
						}
					}
				
			}
	
			layer++;

			//std::cout << "Layer" << layer << std::endl;



		}
	
	std::string newMoveList; //Set end character

	size_t index = boardValues.back().find("||");
	newMoveList = boardValues.back().substr(index + 2);
	if (current == 0){
		newMoveList.append("D");
	}
	moveList = msclr::interop::marshal_as<System::String^>(newMoveList); //Assign the movelist
	System::Console::WriteLine("Result is" + moveList); //Output to verify
	std::cout << "Number BoardStates : " << boardValues.size() << std::endl;
	DebugStates += (int)boardValues.size();
}



void Knight::ThinkAStar2(){
	//Manage a statespace
	std::string Moves = "";

	int tempX = X;
	int tempY = Y;
	int done = -1;

	movementTick = board->getTick(); //Synchronize the tick?
	//Create a Queue, Grab pawns and add them to the statespace
	std::vector<std::string> boardValues;

	//Create A Vector of Pawn Spaces
	std::vector<std::tuple<int, int>> PawnList;


	Moves = std::to_string(tempX) + "|" + std::to_string(tempY) + "K";
	for (int i = 0; i < sizeX; i++){
		for (int j = 0; j < sizeY; j++){

			if (board->getBoard()[i][j]->print() == "2") //If it detects a pawn
			{
				//Add to initial statespace
				Moves += "|" + std::to_string(i) + "|" + std::to_string(j) + "P";
				PawnList.push_back(std::make_tuple(i, j));
			}
			else if (board->getBoard()[i][j]->print() == "3")
			{
				//Add to initial statespace
				Moves += "|" + std::to_string(i) + "|" + std::to_string(j) + "Q";
				PawnList.push_back(std::make_tuple(i, j));
			}
		}

	}
	if (movementTick == true){
		Moves.append("T");
	}
	else{
		Moves.append("F");
	}
	Moves.append("||");

	//Now add initial state to the vector
	boardValues.push_back(Moves); //Push initial state



	//test to see if working
	if (boardValues[0].compare(Moves) == 0){
		System::Console::WriteLine("Looking for next pawn");
	}
	//For each layer...
	int layer = 0; //Initialize layer
	//Count how many pawns are on the board
	size_t count = std::count(boardValues.at(0).begin(), boardValues.at(0).end(), 'P');
	count += std::count(boardValues.at(0).begin(), boardValues.at(0).end(), 'Q');
	size_t current = count;

	//Variables to hold states and add them
	std::string tempString;
	bool addState = false;
	int xCounter = 0;
	int yCounter = 0;
	int xMax = tempX;
	int yMax = tempY;
	int xCheck = 0;
	int yCheck = 0;
	int BFSMode = 0;

	if (count == 0){ //If nothing on board, we good
		done = 1;
	}



	//Calculate closest pawn heuristic.
	for (size_t i = 0, tempsize = PawnList.size(); i < tempsize; i++)
	{
		xCounter = std::get<0>(PawnList.at(i)); //Get distances
		yCounter = std::get<1>(PawnList.at(i));
		xCheck = xCounter - tempX;
		yCheck = yCounter - tempY;
		xCheck = abs(xCheck);
		yCheck = abs(yCheck);
		if ((xCheck + yCheck) > (abs(xMax - tempX) + abs(yMax - tempY)))
		{
			xMax = xCounter;
			yMax = yCounter; //Hold maxes for searching pawns! (mins in this case)
		}
	}


	while (done == -1)
	{
		//Increment layer if needed another layer of depth
		if (layer == boardValues.size()){
			System::Console::WriteLine("we donezo");
		}


		//Update the tempX and tempY based on parent
		std::string::size_type sz;

		tempX = std::stoi(boardValues[layer], &sz);
		//std::cout << (boardValues[layer - 1].at(f).substr(sz+1));
		tempY = std::stoi(boardValues[layer].substr(sz + 1), &sz);
		//std::cout << "tempY:" << tempY;
		xCounter = std::abs((xMax - tempX));
		yCounter = std::abs((yMax - tempY));


		addState = true;
		if (xCounter + yCounter < 4 || BFSMode == 1) //If we are close!
		{
			BFSMode = 1;
			for (int j = 0; j < 8; j++){


				if (j == 0)
				{
					addState = true;
					tempString = (checkMove(boardValues[layer], tempX, tempY, 2, 1));
				}
				if (j == 1)
				{
					addState = true;
					tempString = (checkMove(boardValues[layer], tempX, tempY, 2, -1));
				}
				if (j == 2)
				{
					addState = true;
					tempString = (checkMove(boardValues[layer], tempX, tempY, 1, -2));
				}
				if (j == 3)
				{
					addState = true;
					tempString = (checkMove(boardValues[layer], tempX, tempY, -1, -2));
				}
				if (j == 4)
				{
					addState = true;
					tempString = (checkMove(boardValues[layer], tempX, tempY, -2, -1));
				}
				if (j == 5)
				{
					addState = true;
					tempString = (checkMove(boardValues[layer], tempX, tempY, -2, 1));
				}
				if (j == 6)
				{
					addState = true;
					tempString = (checkMove(boardValues[layer], tempX, tempY, -1, 2));
				}
				if (j == 7)
				{
					addState = true;
					tempString = (checkMove(boardValues[layer], tempX, tempY, 1, 2));
				}

				if (tempString.compare("") != 0){ //If an empty string is made. do not continue this path


					for (size_t i = 0, tempsize = boardValues.size(); i < tempsize; i++)
					{
						if (checkState(boardValues[i], tempString))
						{
							addState = false;
							break;
						}
					}
					if (addState == true){
						boardValues.push_back(tempString);
						current = std::count(boardValues.back().begin(), boardValues.back().end(), 'P');
						current += std::count(boardValues.back().begin(), boardValues.back().end(), 'Q');
						if (current < count)
						{
							//We done!
							done = 1;
							break;
						}
					}
				}
			}
		}
		else if (BFSMode != 1){

			addState = true;

			if (xMax - tempX <= 0 && yMax - tempY <= 0){
				if (xCounter > yCounter)
				{
					//Go more left
					tempString = (checkMove(boardValues[layer], tempX, tempY, -2, -1));
				}
				else{
					//Go more down
					tempString = (checkMove(boardValues[layer], tempX, tempY, -1, -2));
				}
			}

			else if (xMax - tempX <= 0 && yMax - tempY >= 0){
				if (xCounter > yCounter)
				{
					//Go more left
					tempString = (checkMove(boardValues[layer], tempX, tempY, -2, 1));
				}
				else{
					//Go more Up
					tempString = (checkMove(boardValues[layer], tempX, tempY, -1, 2));
				}
			}
			else if (xMax - tempX >= 0 && yMax - tempY <= 0){
				if (xCounter > yCounter)
				{
					//Go more Right
					tempString = (checkMove(boardValues[layer], tempX, tempY, 2, -1));
				}
				else{
					//Go more down
					tempString = (checkMove(boardValues[layer], tempX, tempY, 1, -2));
				}
			}
			else if (xMax - tempX >= 0 && yMax - tempY >= 0){
				if (xCounter > yCounter)
				{
					//Go more Right
					tempString = (checkMove(boardValues[layer], tempX, tempY, 2, 1));
				}
				else{
					//Go more Up
					tempString = (checkMove(boardValues[layer], tempX, tempY, 1, 2));
				}
			}
			/*
			Weird edge cases
			*/

			if (xMax - tempX == 0){
				if (yMax - tempY > 0)
				{
					//Go more Up
					tempString = (checkMove(boardValues[layer], tempX, tempY, 1, 2));
					if (tempString.compare("") == 0)
					{

						//Go more Up... to the left
						tempString = (checkMove(boardValues[layer], tempX, tempY, -1, 2));
					}
					if (tempString.compare("") == 0)
					{

						//Go more Up... to the left
						tempString = (checkMove(boardValues[layer], tempX, tempY, -2, 1));
					}
					if (tempString.compare("") == 0)
					{

						//Go more Up... to the left
						tempString = (checkMove(boardValues[layer], tempX, tempY, 2, 1));
					}
				}



				if (yMax - tempY < 0)
				{
					//Go more down
					tempString = (checkMove(boardValues[layer], tempX, tempY, 1, -2));
					if (tempString.compare("") == 0)
					{
						//Go more down... 2nd attempt
						tempString = (checkMove(boardValues[layer], tempX, tempY, -1, -2));
					}
					if (tempString.compare("") == 0)
					{
						//Go more down... 2nd attempt
						tempString = (checkMove(boardValues[layer], tempX, tempY, -2, -1));
					}
					if (tempString.compare("") == 0)
					{
						//Go more down... 2nd attempt
						tempString = (checkMove(boardValues[layer], tempX, tempY, 2, -1));
					}
				}
			}
			if (yMax - tempY == 0){
				if (xMax - tempX > 0)
				{
					//Go more Right
					tempString = (checkMove(boardValues[layer], tempX, tempY, 2, 1));
					if (tempString.compare("") == 0)
					{
						//Go more Right...again
						tempString = (checkMove(boardValues[layer], tempX, tempY, 2, -1));
					}
					if (tempString.compare("") == 0)
					{
						//Go more Right...again
						tempString = (checkMove(boardValues[layer], tempX, tempY, 1, -2));
					}
					if (tempString.compare("") == 0)
					{
						//Go more Right...again
						tempString = (checkMove(boardValues[layer], tempX, tempY, 1, 2));
					}
				}
				if (xMax - tempX < 0)
				{
					//Go more Left
					tempString = (checkMove(boardValues[layer], tempX, tempY, -2, 1));
					if (tempString.compare("") == 0)
					{
						//Go more Left... 2nd attempt
						tempString = (checkMove(boardValues[layer], tempX, tempY, -2, -1));
					}
					if (tempString.compare("") == 0)
					{
						//Go more Left... 2nd attempt
						tempString = (checkMove(boardValues[layer], tempX, tempY, -1, -2));
					}
					if (tempString.compare("") == 0)
					{
						//Go more Left... 2nd attempt
						tempString = (checkMove(boardValues[layer], tempX, tempY, -1, 2));
					}
				}
			}

			if (tempString.compare("") != 0){ //If an empty string is made. do not continue this path


				/*for (size_t i = 0, tempsize = boardValues.size(); i < tempsize; i++)
				{
				if (checkState(boardValues[i], tempString))
				{
				addState = false;

				break;
				}
				}*/
				if (addState == true){

					boardValues.push_back(tempString);
					current = std::count(boardValues.back().begin(), boardValues.back().end(), 'P');
					current += std::count(boardValues.back().begin(), boardValues.back().end(), 'Q');
					if (current < count)
					{

						//We done!
						done = 1;
						break;
					}
				}
			}

		}

		layer++;

		//std::cout << "Layer" << layer << std::endl;



	}

	std::string newMoveList; //Set end character

	size_t index = boardValues.back().find("||");
	newMoveList = boardValues.back().substr(index + 2);
	if (current == 0){
		newMoveList.append("D");
	}
	moveList = msclr::interop::marshal_as<System::String^>(newMoveList); //Assign the movelist
	System::Console::WriteLine("Result is" + moveList); //Output to verify
	std::cout << "Number BoardStates : " << boardValues.size() << std::endl;
	DebugStates += (int)boardValues.size();
}

void Knight::ThinkAverage(){
	//Manage a statespace
	std::string Moves = "";

	int tempX = X;
	int tempY = Y;
	int done = -1;

	movementTick = board->getTick(); //Synchronize the tick?
	//Create a Queue, Grab pawns and add them to the statespace
	std::vector<std::string> boardValues;

	//Create A Vector of Pawn Spaces
	std::vector<std::tuple<int, int>> PawnList;


	Moves = std::to_string(tempX) + "|" + std::to_string(tempY) + "K";
	for (int i = 0; i < sizeX; i++){
		for (int j = 0; j < sizeY; j++){

			if (board->getBoard()[i][j]->print() == "2") //If it detects a pawn
			{
				//Add to initial statespace
				Moves += "|" + std::to_string(i) + "|" + std::to_string(j) + "P";
				PawnList.push_back(std::make_tuple(i, j));
			}
			else if (board->getBoard()[i][j]->print() == "3")
			{
				//Add to initial statespace
				Moves += "|" + std::to_string(i) + "|" + std::to_string(j) + "Q";
				PawnList.push_back(std::make_tuple(i, j));
			}
		}

	}
	if (movementTick == true){
		Moves.append("T");
	}
	else{
		Moves.append("F");
	}
	Moves.append("||");

	//Now add initial state to the vector
	boardValues.push_back(Moves); //Push initial state



	//test to see if working
	if (boardValues[0].compare(Moves) == 0){
		System::Console::WriteLine("Looking for next pawn");
	}
	//For each layer...
	int layer = 0; //Initialize layer
	//Count how many pawns are on the board
	size_t count = std::count(boardValues.at(0).begin(), boardValues.at(0).end(), 'P');
	count += std::count(boardValues.at(0).begin(), boardValues.at(0).end(), 'Q');
	size_t current = count;

	//Variables to hold states and add them
	std::string tempString;
	bool addState = false;
	int xCounter = 0;
	int yCounter = 0;
	int xMax = 9000;
	int yMax = 9000;
	int xCheck = 0;
	int yCheck = 0;
	int BFSMode = 0;

	if (count == 0){ //If nothing on board, we good
		done = 1;
	}

	std::vector<std::tuple<int, int>> SortedPawnList;
	size_t holderI = 0;
	bool SortLoop = false;
	while (SortLoop == false){
		//Calculate Middle pawn heuristic.
		for (size_t i = 0, tempsize = PawnList.size(); i < tempsize; i++)
		{
			xCounter = std::get<0>(PawnList.at(i)); //Get distances
			yCounter = std::get<1>(PawnList.at(i));
			xCheck = xCounter - tempX;
			yCheck = yCounter - tempY;
			xCheck = abs(xCheck);
			yCheck = abs(yCheck);
			if ((xCheck + yCheck) < (abs(xMax - tempX) + abs(yMax - tempY)))
			{
				holderI = i;
				xMax = xCounter;
				yMax = yCounter; //Hold maxes for searching pawns! (mins in this case)
			}

		}
		SortedPawnList.push_back(PawnList.at(holderI));
		if (PawnList.size() != 1){
			PawnList.erase(PawnList.begin() + holderI, PawnList.begin() + holderI + 1);
			xMax = 9000;
			yMax = 9000;
			
		}
		else{
			SortLoop = true;
		}
	}
	while (done == -1)
	{
		//Increment layer if needed another layer of depth
		if (layer == boardValues.size()){
			System::Console::WriteLine("we donezo");
		}


		//Update the tempX and tempY based on parent
		std::string::size_type sz;

		tempX = std::stoi(boardValues[layer], &sz);
		//std::cout << (boardValues[layer - 1].at(f).substr(sz+1));
		tempY = std::stoi(boardValues[layer].substr(sz + 1), &sz);
		//std::cout << "tempY:" << tempY;
		xCounter = std::abs((xMax - tempX));
		yCounter = std::abs((yMax - tempY));


		addState = true;
		if (xCounter + yCounter < 4 || BFSMode == 1) //If we are close!
		{
			BFSMode = 1;
			for (int j = 0; j < 8; j++){


				if (j == 0)
				{
					addState = true;
					tempString = (checkMove(boardValues[layer], tempX, tempY, 2, 1));
				}
				if (j == 1)
				{
					addState = true;
					tempString = (checkMove(boardValues[layer], tempX, tempY, 2, -1));
				}
				if (j == 2)
				{
					addState = true;
					tempString = (checkMove(boardValues[layer], tempX, tempY, 1, -2));
				}
				if (j == 3)
				{
					addState = true;
					tempString = (checkMove(boardValues[layer], tempX, tempY, -1, -2));
				}
				if (j == 4)
				{
					addState = true;
					tempString = (checkMove(boardValues[layer], tempX, tempY, -2, -1));
				}
				if (j == 5)
				{
					addState = true;
					tempString = (checkMove(boardValues[layer], tempX, tempY, -2, 1));
				}
				if (j == 6)
				{
					addState = true;
					tempString = (checkMove(boardValues[layer], tempX, tempY, -1, 2));
				}
				if (j == 7)
				{
					addState = true;
					tempString = (checkMove(boardValues[layer], tempX, tempY, 1, 2));
				}

				if (tempString.compare("") != 0){ //If an empty string is made. do not continue this path


					for (size_t i = 0, tempsize = boardValues.size(); i < tempsize; i++)
					{
						if (checkState(boardValues[i], tempString))
						{
							addState = false;
							break;
						}
					}
					if (addState == true){
						boardValues.push_back(tempString);
						current = std::count(boardValues.back().begin(), boardValues.back().end(), 'P');
						current += std::count(boardValues.back().begin(), boardValues.back().end(), 'Q');
						if (current < count)
						{
							//We done!
							done = 1;
							break;
						}
					}
				}
			}
		}
		else if (BFSMode != 1){

			addState = true;

			if (xMax - tempX <= 0 && yMax - tempY <= 0){
				if (xCounter > yCounter)
				{
					//Go more left
					tempString = (checkMove(boardValues[layer], tempX, tempY, -2, -1));
				}
				else{
					//Go more down
					tempString = (checkMove(boardValues[layer], tempX, tempY, -1, -2));
				}
			}

			else if (xMax - tempX <= 0 && yMax - tempY >= 0){
				if (xCounter > yCounter)
				{
					//Go more left
					tempString = (checkMove(boardValues[layer], tempX, tempY, -2, 1));
				}
				else{
					//Go more Up
					tempString = (checkMove(boardValues[layer], tempX, tempY, -1, 2));
				}
			}
			else if (xMax - tempX >= 0 && yMax - tempY <= 0){
				if (xCounter > yCounter)
				{
					//Go more Right
					tempString = (checkMove(boardValues[layer], tempX, tempY, 2, -1));
				}
				else{
					//Go more down
					tempString = (checkMove(boardValues[layer], tempX, tempY, 1, -2));
				}
			}
			else if (xMax - tempX >= 0 && yMax - tempY >= 0){
				if (xCounter > yCounter)
				{
					//Go more Right
					tempString = (checkMove(boardValues[layer], tempX, tempY, 2, 1));
				}
				else{
					//Go more Up
					tempString = (checkMove(boardValues[layer], tempX, tempY, 1, 2));
				}
			}
			/*
			Weird edge cases
			*/

			if (xMax - tempX == 0){
				if (yMax - tempY > 0)
				{
					//Go more Up
					tempString = (checkMove(boardValues[layer], tempX, tempY, 1, 2));
					if (tempString.compare("") == 0)
					{

						//Go more Up... to the left
						tempString = (checkMove(boardValues[layer], tempX, tempY, -1, 2));
					}
					if (tempString.compare("") == 0)
					{

						//Go more Up... to the left
						tempString = (checkMove(boardValues[layer], tempX, tempY, -2, 1));
					}
					if (tempString.compare("") == 0)
					{

						//Go more Up... to the left
						tempString = (checkMove(boardValues[layer], tempX, tempY, 2, 1));
					}
				}



				if (yMax - tempY < 0)
				{
					//Go more down
					tempString = (checkMove(boardValues[layer], tempX, tempY, 1, -2));
					if (tempString.compare("") == 0)
					{
						//Go more down... 2nd attempt
						tempString = (checkMove(boardValues[layer], tempX, tempY, -1, -2));
					}
					if (tempString.compare("") == 0)
					{
						//Go more down... 2nd attempt
						tempString = (checkMove(boardValues[layer], tempX, tempY, -2, -1));
					}
					if (tempString.compare("") == 0)
					{
						//Go more down... 2nd attempt
						tempString = (checkMove(boardValues[layer], tempX, tempY, 2, -1));
					}
				}
			}
			if (yMax - tempY == 0){
				if (xMax - tempX > 0)
				{
					//Go more Right
					tempString = (checkMove(boardValues[layer], tempX, tempY, 2, 1));
					if (tempString.compare("") == 0)
					{
						//Go more Right...again
						tempString = (checkMove(boardValues[layer], tempX, tempY, 2, -1));
					}
					if (tempString.compare("") == 0)
					{
						//Go more Right...again
						tempString = (checkMove(boardValues[layer], tempX, tempY, 1, -2));
					}
					if (tempString.compare("") == 0)
					{
						//Go more Right...again
						tempString = (checkMove(boardValues[layer], tempX, tempY, 1, 2));
					}
				}
				if (xMax - tempX < 0)
				{
					//Go more Left
					tempString = (checkMove(boardValues[layer], tempX, tempY, -2, 1));
					if (tempString.compare("") == 0)
					{
						//Go more Left... 2nd attempt
						tempString = (checkMove(boardValues[layer], tempX, tempY, -2, -1));
					}
					if (tempString.compare("") == 0)
					{
						//Go more Left... 2nd attempt
						tempString = (checkMove(boardValues[layer], tempX, tempY, -1, -2));
					}
					if (tempString.compare("") == 0)
					{
						//Go more Left... 2nd attempt
						tempString = (checkMove(boardValues[layer], tempX, tempY, -1, 2));
					}
				}
			}

			if (tempString.compare("") != 0){ //If an empty string is made. do not continue this path


				/*for (size_t i = 0, tempsize = boardValues.size(); i < tempsize; i++)
				{
				if (checkState(boardValues[i], tempString))
				{
				addState = false;

				break;
				}
				}*/
				if (addState == true){

					boardValues.push_back(tempString);
					current = std::count(boardValues.back().begin(), boardValues.back().end(), 'P');
					current += std::count(boardValues.back().begin(), boardValues.back().end(), 'Q');
					if (current < count)
					{

						//We done!
						done = 1;
						break;
					}
				}
			}

		}

		layer++;

		//std::cout << "Layer" << layer << std::endl;



	}

	std::string newMoveList; //Set end character

	size_t index = boardValues.back().find("||");
	newMoveList = boardValues.back().substr(index + 2);
	if (current == 0){
		newMoveList.append("D");
	}
	moveList = msclr::interop::marshal_as<System::String^>(newMoveList); //Assign the movelist
	System::Console::WriteLine("Result is" + moveList); //Output to verify
	std::cout << "Number BoardStates : " << boardValues.size() << std::endl;
	DebugStates += (int)boardValues.size();
}


