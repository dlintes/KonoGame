#include "stdafx.h"
#include "Util.h"

using namespace std;


/* *********************************************************************
Function Name: CharToString
Purpose: 
	Convert a character to string and returns it
Parameters:
	all parameters passed by value
	char input - character to be converted
Return Value: 
	string value - string representation of the provided character
Local Variables:
	string output	- converted string
	stringstream ss - stringstream type object to do the conversion
Algorithm:
Assistance Received: none
********************************************************************* */
string Util::CharToString(char input) {
	string output;
	stringstream ss;
	ss << input;
	ss >> output;
	return output;
}

/* *********************************************************************
Function Name: ToString
Purpose:
	Convert an integer to string and returns it
Parameters:
	all parameters passed by value
	int input - integer to be converted
Return Value:
	string value - string representation of the provided integer to be converted
Local Variables:
	stringstream ss - stringstream type object to do the conversion
Algorithm:
Assistance Received: none
********************************************************************* */
string Util::ToString(int input) {
	stringstream ss;
	ss << input;
	return ss.str();
}

/* *********************************************************************
Function Name: ValidatePosition
Purpose:
	Compares the input position with valid positions given the table size.
Parameters:
	all parameters passed by value
	pair<int,int> pos	- pair of integers representing the position to be validate
	int boardSize		- size of the board
Return Value:
	bool value - true if position is valid, false otherwise
Local Variables:
	int pos1,pos2 - row and column components of the position
Algorithm:
Assistance Received: none
********************************************************************* */
bool Util::ValidatePosition(pair<int,int> pos, int boardSize) {
	int pos1, pos2;
	pos1 = pos.first;
	pos2 = pos.second;
	if (pos1 < 0 || pos1 >= boardSize || pos2 < 0 || pos2 >= boardSize) {
		return false;
	}
	return true;
}

/* *********************************************************************
Function Name: ValidatePosition
Purpose:
	Compares the input position with valid positions given the table size.
Parameters:
	all parameters passed by value
	int pos1		- row position
	int pos2		- column position
	int boardSize	- size of the board
Return Value:
bool value - true if position is valid, false otherwise
Local Variables:
int pos1,pos2 - row and column components of the position
Algorithm:
Assistance Received: none
********************************************************************* */
bool Util::ValidatePosition(int pos1, int pos2, int boardSize) {
	if (pos1 < 0 || pos1 >= boardSize || pos2 < 0 || pos2 >= boardSize) {
		return false;
	}
	return true;
}

/* *********************************************************************
Function Name: ValidateDirectionValue
Purpose:
	Compares the moving direction with accepted values (NE/NW/SE/SW)
Parameters:
	all parameters passed by value
	string direction - direction of the move
Return Value:
	bool value - true if direction is valid, false otherwise
Local Variables:
Algorithm:
Assistance Received: none
********************************************************************* */
bool Util::ValidateDirectionValue(string direction) {
	if (direction != NE && direction != NW && direction != SE && direction != SW) {
		return false;
	}
	return true;
}