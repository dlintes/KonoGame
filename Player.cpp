#include "stdafx.h"
#include "Board.h"
#include "Player.h"
#include <ctime>

using namespace std;

/* *********************************************************************
Function Name: SetColor
Purpose: 
	Mutator. Sets the color to W/w or B/b
	Created according to best practice to return bool but validation not actually needed
	as color is already validated when human choses it from standard input.
Parameters:
	None
Return Value:
    bool - true if color is W or B else false
Local Variables:
	m_Color - private data memebrs set.
Algorithm:
Assistance Received: none
********************************************************************* */
bool Player::SetColour(char color)
{
	m_Color = color;
	if (m_Color != 'W' && m_Color != 'B' && m_Color != 'b' && m_Color != 'w' && m_Color != ' ') {
		return false;
	}
	return true;
}

/* *********************************************************************
Function Name: RollDice
Purpose: to simulate rolling 2 dices
Parameters:
None
Return Value: 
	sum of the values of the 2 dices
Local Variables:
	int sum - total sum of the 2 dices
	int oneDice - value for one dice.
Algorithm:
	Use a function that generates random numbers between 1 and 6.
	Call it twice to emulate each dice roll.
	Calculate the sum and return it.
Assistance Received: none
********************************************************************* */
int Player::RollDice()
{
	srand(time(NULL));
	int sum, oneDice;
	sum = 0;
	oneDice = 1 + rand() % 6;
	sum = sum + oneDice;
	oneDice = 1 + rand() % 6;
	sum = sum + oneDice;
	return sum;
}
/* *********************************************************************
Function Name: EndOfGame
Purpose: To verify if all pieces of a player reached startig positions of the other
Parameters:
	all parameters passed by value
	Board board - instantiation of the board class.

Return Value: 
	bool gameStop - true if game ends and false otherwise
Local Variables:
	bool gameStop - true if game ens, false otherwise
	vector<std::pair<int, int>> listOfPieces - vector of pairs of integers holding positions for all pieces on the board
	int index - to traverse the vector
	int pos1 - stores row value
	int pos2 - stores column value
Algorithm:
	Loops through all the pieces. If at least one of them is not on one of the opponent's starting positions, the game is not finished.
Assistance Received: none
********************************************************************* */
bool Player::EndOfGame(Board board)
{
	bool gameStop = true;
	vector<std::pair<int, int>> listOfPieces = board.GetListOfPieces(m_Color);
	for (int index = 0; index < listOfPieces.size(); ++index)
	{
		int pos1 = listOfPieces[index].first;
		int pos2 = listOfPieces[index].second;
		if (board.IsValuePos(pos1, pos2, m_Color) == false) {
			gameStop = false;
		}
	}
	return gameStop;
}

/* *********************************************************************
Function Name: CalculatePositionPoints
Purpose: To calculate total points for all pieces of a player at that time
Parameters:
	all parameters passed by value
	Board board - instance of class board. Contains info about the pieces, position of pieces and value associated with each position.
Return Value: 
	pair<int,int> - a pair of integers
		- first value contains the total value for all pieces
		- second value in pair contains the number of pieces on the table at that time.
Local Variables:
	vector<std::pair<int, int>> listOfPieces - a list of pairs of integers. Contains all pieces on the board expressed by a pair of (row, column) 	 
	int myNrOfPieces - total number of pieces for that player
	int myTotalValue - integer to cumulate total value of the pieces
	int squareValue - calculated value of a square on the board
	index - index to traverse vector
Algorithm:
	collect the list positions of all pieces for the player
	cumulate the value of each piece into a total value
	increment the number of the pieces
	return a pair containing total value and number of pieces on the table.
Assistance Received: none
********************************************************************* */
pair<int,int> Player::CalculatePositionPoints(Board board)
{
	vector<std::pair<int, int>> listOfPieces = board.GetListOfPieces(m_Color);
	int myNrOfPieces = listOfPieces.size();
	int myTotalValue = 0;
	int squareValue = 0;
	for (int index = 0; index < listOfPieces.size(); ++index)
	{
		if (m_Color == 'W' ) {
			// For color white which is moving south from row = 0 to row = board_size - 1, we calculate the values only if this are on
			// the oponents home base. The opponent's home base rows are board_size - 1 and board_size - 2
			if (listOfPieces[index].first < board.GetBoardSize() - 2) {
				squareValue = 0;
			}
			else {
				squareValue = board.GetSquareValue(make_pair(listOfPieces[index].first, listOfPieces[index].second));
			}

		}
		else {
			// For player with color B which moves from South (board_size - 1) to North (row 0) we calculate the value only if theya re on rows 0 or 1. 
			if (listOfPieces[index].first > 1) {
				squareValue = 0;
			}
			else {
				squareValue = board.GetSquareValue(make_pair(listOfPieces[index].first, listOfPieces[index].second));
			}
		}
		myTotalValue = myTotalValue + squareValue; 
	}
	return make_pair(myTotalValue,myNrOfPieces);
}