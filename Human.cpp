#include "stdafx.h"
#include "Human.h"
#include "Board.h"

using namespace std;

/* *********************************************************************
Function Name: ConvertInputToPosition
Purpose: 
	To convert starting position and direction to destination position
Parameters:
	all parameters passed by value
	int startPos1 - row for starting position
	int startPos2 - column for starting position
	string direction - direction of the move (NE/NW/SE/SW)
Return Value: 
	pair<int, int> - pair of integers representing row and column for the destination position
Local Variables:
	int endPos1				- row value of destination position
	int endPos2				- column value of destination position
Algorithm:
	For each possible directions, calculate destination position by adding substracting 1 from roe and column values of the starting positions.
Assistance Received: none
********************************************************************* */
pair<int, int> Human::ConvertInputToPosition(int startPos1, int startPos2, string direction)
{
	int endPos1, endPos2;
	endPos1 = -1;
	endPos2 = -1;
	//Moving from North to South.
	if (direction == "NE") {
		endPos1 = startPos1 - 1;
		endPos2 = startPos2 + 1;
	}
	else if (direction == "SE") {
		endPos1 = startPos1 + 1;
		endPos2 = startPos2 + 1;
	}
	else if (direction == "NW") {
		endPos1 = startPos1 - 1;
		endPos2 = startPos2 - 1;
	}
	else if (direction == "SW") {
		endPos1 = startPos1 + 1;
		endPos2 = startPos2 - 1;
	}
    
	return make_pair(endPos1, endPos2);
}

/* *********************************************************************
Function Name: ValidateInput
Purpose:
	To validate the move entered by human. Make sure it is a valid move that respects the game's rules.
	- moves only diagonaly
	- moves only one square
	- can move over an opponent piece and capture it only inc ertain conditions
Parameters:
	all parameters passed by value
	Board board - instance of class board representing board status at this moment
	pair<int,int> startPos - pair of integeres representing starting position
	pair<int,int> endPos - pair of integers representing destination position
	char playerColor - color of the pieces of the player that makes the move
	char oponentColor - color of the pieces of the opponent player.
Return Value:
	pair<bool, string> - pair of a variable fo type bool and one of type string
		- bool variable		- true if move is possible and false otherwise.
		- string variable	- if move is not possible it will contain the reason for invalidating the move. 
Local Variables:
	int endPos1, endPos2		- integers to store the row and column for starting position
	int startPos1, startPos2	- integers to store the row and column for destination position
		- they are needed as they are required for input parameters for other functions called in this method. 
Algorithm:
	- if the starting position is not occupied by a piece that belongs to the player that moves, return error.
	- if player attempts to move over his own piece, return error
	- if destination position is not valid for this board size, return error
	- if an attempt is done to move over opponent's piece and this is not a piece that can be captured, return error
Assistance Received: none
********************************************************************* */

pair<bool, string> Human::ValidateInput(Board board, pair<int,int> startPos, pair<int,int> endPos, char playerColor, char oponentColor)
{
	int endPos1, endPos2;
	int startPos1, startPos2;
	startPos1 = startPos.first;
	startPos2 = startPos.second;
	endPos1 = endPos.first;
	endPos2 = endPos.second;
	bool playerIsSuperPiece = false;
	int boardSize = board.GetBoardSize();
	string playerSuperPiece = board.CharToString(playerColor) + board.CharToString(playerColor);
	string oponentSuperPiece = board.CharToString(oponentColor) + board.CharToString(oponentColor);
	if (board.GetSquareColor(startPos1, startPos2) == playerSuperPiece) {
		playerIsSuperPiece = true;
	}
	if (startPos1 < 0 || startPos1 >= boardSize || startPos2 < 0 || startPos2 >= boardSize) {
		// if this is not a valid position on the table, return false
		return make_pair(false, "Start position is outside of the board.");
	}
	if (endPos1 < 0 || endPos1 >= boardSize || endPos2 < 0 || endPos2 >= boardSize) {
		// if this is not a valid position on the table, return false
		return make_pair(false, "End position is outside of the board.");
	}
	// if the starting position is not occupied by a piece that belongs to the player that moves, return error.
	if (board.GetSquareColor(startPos1, startPos2)[0] != playerColor) {
		return make_pair(false, "Starting position is occupied by this player's piece.");;
	}
	// At this stage we can get access the end pos color as we made sure end pos is already on the board.
	char posColor = board.GetSquareColor(endPos1, endPos2)[0];
	if (posColor == playerColor) {
		// Human cannot move over his own piece.
		return make_pair(false, "You cannot move over your own piece.");
	}
	if (posColor == oponentColor) {
		// If human tries to move over an opponent piece, verify if it is a piece that can be taken
		// board.IsValue() function returns true if the piece can be taken or false if not.
		if (playerIsSuperPiece == true) {
			// If player is super piece the oponent can be taken.
			return make_pair(true, "");
		}
		else {
			// If current player is not supper piece the oponent cannot be taken if the oponent is not on a 
			// home position that has a value.
			if (board.IsValuePos(endPos1, endPos2, playerColor) == false) {
				return make_pair(false, "Oponent's piece cannot be taken from that position.");
			}
		}
	}
	return make_pair(true,"");
}
