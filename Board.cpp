#include "stdafx.h"
#include "Board.h"
#include <string>

using namespace std;

/* *********************************************************************
Function Name: Board
Purpose: 
	Default constructor for Board class. Uses a board size of 5. 
	Added as it was requested that each class to have a default constructor.
Parameters:
	None
Return Value: 
	None
Local Variables:
	m_boardSize - private data member storing the size of the board
	m_directions - private data member storing a list of directions
Algorithm:
Assistance Received: none
********************************************************************* */
Board::Board()
{
	// Default constructor. Use size 5 for board size
	m_boardSize = 5;
	InitBoard(5);
	InitBoardValues(5);
	m_directions.push_back("SE");
	m_directions.push_back("SW");
	m_directions.push_back("NE");
	m_directions.push_back("NW");
}

/* *********************************************************************
Function Name: Board
Purpose:
	Overloaded constructor for Board class. Board size is passed as parameter
Parameters:
	all parameters passed by value
	int size - board size
Return Value:
	None
Local Variables:
	m_boardSize - private data member storing the size of the board
	m_directions - private data member storing a list of directions
Algorithm:
Assistance Received: none
********************************************************************* */
Board::Board(int size)
{
	// Overloaded constructor. This time we pass the size of the board.
	InitBoard(size);
	InitBoardValues(size);
	m_directions.push_back("SE");
	m_directions.push_back("SW");
	m_directions.push_back("NE");
	m_directions.push_back("NW");
}

/* *********************************************************************
Function Name: GetBoard
Purpose: 
	To return a pointer to the data structure storing board layout
Parameters:
	all parameters passed by value
	None
Return Value: 
	None
Local Variables:
Algorithm:
Assistance Received: none
********************************************************************* */
string** Board::GetBoard() {
	return m_board;
}

/* *********************************************************************
Function Name: SetBoard
Purpose:
	To set a pointer to the data structure describing the board layout
Parameters:
	all parameters passed by value
	string ** savedBoard - pointer to a pointer of an array of strings
Return Value:
	None
Local Variables:
Algorithm:
Assistance Received: none
********************************************************************* */
void Board::SetBoard(string ** savedBoard)
{
	m_board = savedBoard;
}

/* *********************************************************************
Function Name: SetBoardPiece
Purpose:
	To update the board layout structure with new info for the player that moved to a new destination position
Parameters:
	all parameters passed by value
	pair<int, int> startPos - pair of integers describing the start position 
	pair<int, int> stopPos	- pair of integers describing the destination position 
	string playerColor		- color of the player that moves
Return Value:
	bool - true if the info update has been executed correctly 
Local Variables:
	string powerPlayerColor  - string storing the symbol for a poewr player
Algorithm:
	- if player is already a power player, it will be a power player at the new position
	- if the player reaches a power position becomes a power player 
Assistance Received: none
********************************************************************* */
bool Board::SetBoardPiece(pair<int, int> startPos, pair<int, int> stopPos, string playerColor)
{
	// We start from the assumption that player with color W (can be any of the two players) moves
	// from North to South. From row 1 to maximum board size.
	string powerPlayerColor = playerColor + playerColor;
	if (GetSquareColor(startPos.first, startPos.second) == powerPlayerColor) {
		m_board[stopPos.first][stopPos.second] = powerPlayerColor;
		return true;
	}
	if (playerColor == "W") {
		if (stopPos.first == m_boardSize - 1) {
			// The player reaches last row and becomes a power player.
			if (m_board[stopPos.first][stopPos.second] != powerPlayerColor) {
				m_board[stopPos.first][stopPos.second] = powerPlayerColor;
			}
		}
		else if (stopPos.first == m_boardSize - 2 && (stopPos.second == 0 || stopPos.second == m_boardSize - 1)) {
			// The player reaches positions on the row before the last row that allow to become a power player.
			if (m_board[stopPos.first][stopPos.second] != powerPlayerColor) {
				m_board[stopPos.first][stopPos.second] = powerPlayerColor;
			}
		}
		else {
			// Stays a regular player
			m_board[stopPos.first][stopPos.second] = playerColor;
		}
	}
	// Same reasoning for the player playing with the B (Black) pieces.
	// It is just that this player can become a power player on the first and partially on the second rows.
	if (playerColor == "B") {
		if (stopPos.first == 0) {
			// The player reaches last row and becomes a power player.
			if (m_board[stopPos.first][stopPos.second] != powerPlayerColor) {
				m_board[stopPos.first][stopPos.second] = powerPlayerColor;
			}
		}
		else if (stopPos.first == 1 && (stopPos.second == 0 || stopPos.second == m_boardSize - 1)) {
			// The player reaches positions on the row before the last row that allow to become a power player.
			if (m_board[stopPos.first][stopPos.second] != powerPlayerColor) {
				m_board[stopPos.first][stopPos.second] = powerPlayerColor;
			}
		}
		else {
			// Stays a regular player
			m_board[stopPos.first][stopPos.second] = playerColor;
		}
	}
	return true;
}

/* *********************************************************************
Function Name: ResetBoardPiece
Purpose:
	To update the board layout structure with new info for a position that has been released by a player that moved
Parameters:
	all parameters passed by value
	pair<int, int> startPos - pair of integers describing the released position
Return Value:
	bool - true if the info update has been executed correctly, false otherwise
Local Variables:
string powerPlayerColor  - string storing the symbol for a poewr player
Algorithm:
- if player is already a power player, it will be a power player at the new position
- if the player reaches a power position becomes a power player
Assistance Received: none
********************************************************************* */
bool Board::ResetBoardPiece(pair<int, int> pos)
{
	int firstPos = pos.first ;
	int secondPos = pos.second;
	m_board[firstPos][secondPos] = "O";
	return true;
}

int** Board::GetBoardValues() {
	return m_boardValues;
}

/* *********************************************************************
Function Name: MovePiece
Purpose:
	To update source and destination location info in the structure that describes the board when a piece is moved 
Parameters:
	None
Return Value:
	None
Local Variables:
	None
Algorithm:
Assistance Received: none
********************************************************************* */
void Board::MovePiece(pair<int, int> startPos, pair<int, int> endPos, string playerColor, string oponentColor)
{
	SetBoardPiece(startPos, endPos, playerColor);
	ResetBoardPiece(startPos);
}

/* *********************************************************************
Function Name: GetSquareValue
Purpose:
	To get the value associated with a position
Parameters:
	all parameters passed by value
	pair<int, int> pos - pair of integers describing the position
Return Value:
	int value - value associated with the position
Local Variables:
	None
Algorithm:
Assistance Received: none
********************************************************************* */
int Board::GetSquareValue(pair<int, int> pos)
{
	return m_boardValues[pos.first][pos.second];
}

/* *********************************************************************
Function Name: GetSquareColor
Purpose:
	To get the color (identify the player) that holds the piece on the provided position
Parameters:
	all parameters passed by value
	int pos1 - int row value
	int pos2 - int column valu
Return Value:
	string value - color associated with the position
Local Variables:
	None
Algorithm:
Assistance Received: none
********************************************************************* */
string Board::GetSquareColor(int pos1, int pos2)
{
	return m_board[pos1][pos2];
}

/* *********************************************************************
Function Name: GetBoardSize
Purpose:
	To get the board size
Parameters:
	none
Return Value:
	int size - board size
Local Variables:
	None
Algorithm:
Assistance Received: none
********************************************************************* */
int Board::GetBoardSize() {
	return m_boardSize;
}

/* *********************************************************************
Function Name: InitBoard
Purpose:
	Initializes the structure that holds board layout as a dynamic double array of strings
Parameters:
	all parameters passed by value
	int size - board size
Return Value:
	None
Local Variables:
	m_boardSize - private data memebr used to store the board size
	m_board new string *[m_boardSize] - private data member used store an array of pointers to string data. It is used to implement a dynamic double array
Algorithm:
	Loop through the double array structure and initalize each position with either the color of the 2 players (W or B) or the O simbol for an empty position. 
Assistance Received: none
********************************************************************* */
void Board::InitBoard(int size)
{
	// Initialize the board with W, B and O

	m_boardSize = size;
	m_board = new string *[m_boardSize];

	for (int i = 0; i < m_boardSize; i++) {
		m_board[i] = new string[m_boardSize];
	}

	for (int j = 0; j < m_boardSize; j++) {
		for (int i = 0; i < m_boardSize; i++) {
			if (j == 0) {
				m_board[j][i] = "W";
			}
			else if (j == 1) {
				// setting the advanced line of the white game set.
				if (i == 0) {
					m_board[j][i] = "W";
				}
				else if (i == m_boardSize - 1) {
					m_board[j][i] = "W";
				}
				else {
					m_board[j][i] = "O";
				}
			}
			else if (j == m_boardSize - 2) {
				// setting the advanced line of the black game set.
				if (i == 0) {
					m_board[j][i] = "B";
				}
				else if (i == m_boardSize - 1) {
					m_board[j][i] = "B";
				}
				else {
					m_board[j][i] = "O";
				}
			}
			else if (j == m_boardSize - 1) {
				// setting the first line of the black game set.
				m_board[j][i] = "B";
			}
			else {
				// filling the rest of the lines with "O"
				m_board[j][i] = "O";
			}
		}
	}
}

/* *********************************************************************
Function Name: InitBoardValues
Purpose:
	Initializes the structure that holds poaition values for the board.
Parameters:
	all parameters passed by value
	int size - board size
Return Value:
	None
Local Variables:
	m_boardValues = new int *[size] - an array of pointers to int that allow us to emulate a double array of integers
Algorithm:
	Loop through the double array structure and initalize each position with the corresponding value for that position.
Assistance Received: none
********************************************************************* */
void Board::InitBoardValues(int size) {
	m_boardValues = new int *[size];
	for (int i = 0; i < size; i++) {
		m_boardValues[i] = new int[size];
	}
	int i = 0;
	for (int j = 0; j < size; j++) {
		for (i = 0; i < size; i++) {
			if (j == 0 || j == size - 1) {
				if (size == 5) {
					if (i == 0 || i == size - 1) {
						m_boardValues[j][i] = 3;
					}
					else if (i == 1 || i == size - 2) {
						m_boardValues[j][i] = 1;
					}
					else if (i == 2) {
						m_boardValues[j][i] = 5;
					}
				}
				else if (size == 7) {
					if (i == 0 || i == size - 1) {
						m_boardValues[j][i] = 3;
					}
					else if (i == 1 || i == size - 2) {
						m_boardValues[j][i] = 1;
					}
					else if (i == 2 || i == size - 3) {
						m_boardValues[j][i] = 5;
					}
					else if (i == 3) {
						m_boardValues[j][i] = 7;
					}
				}
				else if (size == 9) {
					if (i == 0 || i == size - 1) {
						m_boardValues[j][i] = 3;
					}
					else if (i == 1 || i == size - 2) {
						m_boardValues[j][i] = 1;
					}
					else if (i == 2 || i == size - 3) {
						m_boardValues[j][i] = 5;
					}
					else if (i == 3 || i == size - 4) {
						m_boardValues[j][i] = 7;
					}
					else if (i == 4) {
						m_boardValues[j][i] = 9;
					}
				}
			}
			else if (j == 1 || j == size - 2) {
				if (i == 0 || i == size - 1) {
					m_boardValues[j][i] = 1;
				}
				else {
					m_boardValues[j][i] = 0;
				}
			}
			else {
				m_boardValues[j][i] = 0;
			}
		}
	}
};

/* *********************************************************************
Function Name: GetListOfPieces
Purpose:
	Get a list of positions for each available piece belonging to a player
Parameters:
	all parameters passed by value
	char color - color of the player for which we want to get the list of available pieces on board
Return Value:
	vector<std::pair<int, int>> - a vector of pairs of integers. Each pair contains the row and the column describing the position
Local Variables:
	vector<std::pair<int, int>> - a vector of pairs of integers. Each pair contains the row and the column describing the position
								  Cumulates the positions and will be returned to the calling fucntion
	pair<int, int> myPair		- working variable. Pair of integers that stores a position
Algorithm:
	Loops through the structure and returns the positions for pieces belonging to the provided player.
Assistance Received: none
********************************************************************* */
vector<std::pair<int, int>> Board::GetListOfPieces(char myColor)
{
	vector<std::pair<int, int>> myList;
	pair<int, int> myPair;
	for (int i = 0; i < m_boardSize; i++) {
		for (int j = 0; j < m_boardSize; j++) {
			if (m_board[i][j][0] == myColor) {
				myPair = make_pair(i, j);
				myList.push_back(myPair);
			}

		}
	}
	return myList;
}

/* *********************************************************************
Function Name: IsValuePos
Purpose:
	Returns true if this is a position that can be captured by an opponent. It also signifies that the position has a value greater than 0.
Parameters:
	all parameters passed by value
	int pos1 - row value for the posi
	int pos2 - column value for the position
	char color - color of the player for which we want to get the list of available pieces on board
Return Value:
	bool value - true if this position has a value greater than 0
Local Variables:
	None
Algorithm:
	- verifies the coordinates and if they correspons to the first row for the opponent or the second row first and last column, returns true.
Assistance Received: none
********************************************************************* */
bool Board::IsValuePos(int pos1, int pos2, char color)
{
	// B moves from m_BoardSize to 0. Value positions are at line o and 1 for player with color B
	if (color == 'B') {

		if (pos1 == 0) {
			return true;
		}
		if (pos1 == 1 && (pos2 == 0 || pos2 == m_boardSize - 1)) {
			return true;
		}
	}
	// W moves from 0 to m_BoardSize. Value positions are at line m_boardSize and m_boardSize - 1 for player with color W
	if (color == 'W') {
		if (pos1 == m_boardSize - 1) {
			return true;
		}
		if (pos1 == m_boardSize - 2 && (pos2 == 0 || pos2 == m_boardSize - 1)) {
			return true;
		}
	}
	return false;
}

/* *********************************************************************
Function Name: CharToString
Purpose:
	Converts a character to a string format. Needed as the player color is stored in a char and we might need to transform it into a string.
Parameters:
	all parameters passed by value
	char input - character to be converted to a string.
Return Value:
	string value - converted value
Local Variables:
	string output	- converted character into string
	stringstream ss	- stringstream type variable that makes the conversion
Algorithm:
Assistance Received: none
********************************************************************* */
string Board::CharToString(char input) {
	string output;
	stringstream ss;
	ss << input;
	ss >> output;
	return output;
}

/* *********************************************************************
Function Name: CanDestBeCaptured
Purpose:
	If any of the adjacent positions can capture provided position, return true
Parameters:
	all parameters passed by value
	int pos1			- row value for position
	int pos2			- column value for position
	char myColor		- color of the player that has to move
	char oponentColor	- color of the opponent player
Return Value:
	pair<bool,pair<int,int>> - a pair of bool and pair of integers
								- bool value will be true if the position can be captured by an opponent on the adjacent values and false otherwise
								- if the position can be captured the pair of integers pair<int,int> will contain the coordinates of the position that can capture the provided position.
Local Variables:
	pair<int, int> adjacentPos	- pair of integers describing any of the adjacent positions
	int adjacentPos1			- integer describing the row value of the adjacent position 
	int adjacentPos2			- integer describing the column value of the adjacent position
	string oponentSuperPiece	- string describing the symbol that identifies the opponent super piece.
Algorithm:
	- find all fiagonally adjacent positions for the provided position
	- check if the adjacent position is occupied by an opponent super piece
	- check if provided position is a position that can be captured by a regular opponent piece
	- return true and the coordinates of the piece that can capture provided position or false and <-1, -1> otherwise.
Assistance Received: none
********************************************************************* */
pair<bool,pair<int,int>> Board::CanDestBeCaptured(int pos1, int pos2, char myColor, char oponentColor) {
	for (int i = 0; i < m_directions.size(); i++) {
		pair<int, int> adjacentPos = GetPosByDirection(make_pair(pos1, pos2), m_directions[i]);
		int adjacentPos1 = adjacentPos.first;
		int adjacentPos2 = adjacentPos.second;
		string oponentSuperPiece = CharToString(oponentColor) + CharToString(oponentColor);
		if (adjacentPos1 >= 0 && adjacentPos1 < m_boardSize && adjacentPos2 >= 0 && adjacentPos2 < m_boardSize) {
			// If the adjacent position is an opponent super piece this piece can be captured 
			if (m_board[adjacentPos1][adjacentPos2] == oponentSuperPiece) {
					return make_pair(true,make_pair(adjacentPos1, adjacentPos2));
			}
			else {
				// If the adjacent position is not a super piece, this position can still be captured if it is a value position. The opponent can capture this piece and become a super piece.
				if (m_board[adjacentPos1][adjacentPos2][0] == oponentColor && IsValuePos(pos1, pos2, oponentColor)) {
					return make_pair(true, make_pair(adjacentPos1, adjacentPos2));
				}
			}
		}
	}
	return make_pair(false, make_pair(-1,-1));
}

/* *********************************************************************
Function Name: CanBeCaptured
Purpose:
	If any of the adjacent positions can capture provided position, return true. This relates to the source location of the move and not to the possible
	destination position of the move.
Parameters:
	all parameters passed by value
	int pos1			- row value for position
	int pos2			- column value for position
	char myColor		- color of the player that has to move
	char oponentColor	- color of the opponent player
Return Value:
	pair<bool,pair<int,int>> - a pair of bool and pair of integers
	- bool value will be true if the position can be captured by an opponent on the adjacent values and false otherwise
	- if the position can be captured the pair of integers pair<int,int> will contain the coordinates of the position that can capture the provided position.
Local Variables:
	pair<int, int> adjacentPos	- pair of integers describing any of the adjacent positions
	int adjacentPos1			- integer describing the row value of the adjacent position
	int adjacentPos2			- integer describing the column value of the adjacent position
	string oponentSuperPiece	- string describing the symbol that identifies the opponent super piece.
Algorithm:	
	- find all fiagonally adjacent positions for the provided position
	- check if the adjacent position is occupied by an opponent super piece
	- check if provided position is a position that can be captured by a regular opponent piece
	- return true and the coordinates of the piece that can capture provided position or false and <-1, -1> otherwise.
Assistance Received: none
********************************************************************* */
pair<bool,pair<int,int>> Board::CanBeCaptured(int pos1, int pos2, char myColor, char oponentColor) {
	for (int i = 0; i < m_directions.size(); i++) {
		pair<int, int> adjacentPos = GetPosByDirection(make_pair(pos1, pos2), m_directions[i]);
		int adjacentPos1 = adjacentPos.first;
		int adjacentPos2 = adjacentPos.second;
		string oponentSuperPiece = CharToString(oponentColor) + CharToString(oponentColor);
		if (adjacentPos1 >= 0 && adjacentPos1 < m_boardSize && adjacentPos2 >= 0 && adjacentPos2 < m_boardSize) {
			// If the adjacent position is an opponent super piece this piece can be captured 
			if (m_board[adjacentPos1][adjacentPos2] == oponentSuperPiece) {
				if (m_board[pos1][pos2][0] == myColor) {
					return make_pair(true,make_pair(adjacentPos1, adjacentPos2));
				}
			}
			else {
				// If the adjacent position is not a super piece, this position can still be captured if it is a value position. 
				// The opponent can capture this piece and become a super piece.
				if (m_board[adjacentPos1][adjacentPos2][0] == oponentColor && m_board[pos1][pos2][0] == myColor && IsValuePos(pos1, pos2, oponentColor)) {
					return make_pair(true, make_pair(adjacentPos1, adjacentPos2));
				}
			}
		}
	}
	return make_pair(false,make_pair(-1,-1));
}

/* *********************************************************************
Function Name: CanCapture
Purpose:
	If this position can capture the adjacent position provided as a desiantion parameter, return true else return false
Parameters:
	all parameters passed by value
	int startPos1			- row value for starting position
	int startPos2			- column value for starting position
	int stopPos1			- row value for possible destination position
	int stopPos2			- column value for possible destination position
	char myColor			- color of the player that has to move
	char oponentColor		- color of the opponent player
Return Value:
	bool value - true if it can capture at least one of the adjacent positions
Local Variables:
	string mySuperPiece  - string containing the symbol for super piece
Algorithm:
	 - if moving player is super piece and destination position is an opponent return true. Super piece can capture an opponent anywhere.
	 - else if moving player is not a super piece but the adjacent position is occupied by an opponent and this is a value position, it can capture it and become a super piece.
Assistance Received: none
********************************************************************* */
bool Board::CanCapture(int startPos1, int startPos2, int stopPos1, int stopPos2, char myColor, char oponentColor) {
	string mySuperPiece = CharToString(myColor) + CharToString(myColor);
	// If moving player is super piece and destination position is an opponent return true.Super piece can capture an opponent anywhere.
	if (m_board[startPos1][startPos2] == mySuperPiece) {
		if (m_board[stopPos1][stopPos2][0] == oponentColor) {
			return true;
		}
	}
	else {
		// If I am not a super piece but the adjacent position is occupied by an opponent and this is a value position, i can capture it and become a super piece.
		if (m_board[stopPos1][stopPos2][0] == oponentColor && IsValuePos(stopPos1, stopPos2, myColor)) {
			return true;
		}
	}	
	return false;
}

/* *********************************************************************
Function Name: CanBlockAdvance
Purpose:
	If this position can block any of the adjacent positions, return true else return false
Parameters:
	all parameters passed by value
	int pos1			- row value for position to check
	int pos2			- column value for position to check
	char myColor		- color of the player that has to move
	char oponentColor	- color of the opponent player
Return Value:
	pair<bool,pair<int,int>> - a pair of bool and pair of integers
	- bool value will be true if the position can block an opponent on the adjacent values to advance on that position and false otherwise
	- if the position can block an opponent the pair of integers pair<int,int> will contain the coordinates of the position that can be blocked by the provided position.
Local Variables:
	string mySuperPiece  - string containing the symbol for super piece
	bool oponentFound	- working bool variable
Algorithm:
	- verify first if adjacent to this position is an opponent super piece. If there is one return false as it cannot block.
	- else check if there are opponent pieces adjacent to this position.
		- if no opponent pieces are adjacent to this position return false
	- verifying if we can block the opponent to advance to this positions. 
		- if yes return true and the position that can be blocked else return false and <-1, -1>
Assistance Received: none
********************************************************************* */
pair<bool,pair<int,int>> Board::CanBlockAdvance(int pos1, int pos2, char myColor, char oponentColor) {
	string oponentSuperPiece = CharToString(oponentColor) + CharToString(oponentColor);
	// Verifying first if adjacent to this position is an opponent super piece. If there is one return false as it cannot block.
	bool oponentFound = false;
	for (int i = 0; i < m_directions.size(); i++) {
		pair<int, int> adjacentPos = GetPosByDirection(make_pair(pos1, pos2), m_directions[i]);
		int adjacentPos1 = adjacentPos.first;
		int adjacentPos2 = adjacentPos.second;
		if (adjacentPos1 >= 0 && adjacentPos1 < m_boardSize && adjacentPos2 >= 0 && adjacentPos2 < m_boardSize) {
			if (m_board[adjacentPos1][adjacentPos2][0] == oponentColor && m_board[adjacentPos1][adjacentPos2] == oponentSuperPiece) {
				return make_pair(false,make_pair(-1,-1));
			}
		}
	}
	// If we got here it means that there are no adjacent opponent super pieces. Check if there are opponent pieces adjacent to this position. 
	/*
	if (oponentFound == false) {
		return make_pair(false, make_pair(-1,-1));
	}
	*/
	// Now we are verifying if we can block the opponent to advance to my value positions
	// We are not checking if we can block the retreat of the opponent as we are not interested in this.
	for (int i = 0; i < m_directions.size(); i++) {
		pair<int, int> adjacentPos = GetPosByDirection(make_pair(pos1, pos2), m_directions[i]);
		// If plying with white pieces and opponent can advance to this position, we can consider it can block
		if (myColor == 'W' && (m_directions[i] == "SE" || m_directions[i] == "SW")) {
			int adjacentPos1 = adjacentPos.first;
			int adjacentPos2 = adjacentPos.second;
			if (adjacentPos1 >= 0 && adjacentPos1 < m_boardSize && adjacentPos2 >= 0 && adjacentPos2 < m_boardSize) {
				if (m_board[adjacentPos1][adjacentPos2][0] == oponentColor) {
					return make_pair(true, make_pair(adjacentPos1, adjacentPos2));
				}
			}
		}
		// If plying with black pieces and opponent can advance to this position, we can consider it can block
		if (myColor == 'B' && (m_directions[i] == "NE" || m_directions[i] == "NW")) {
			int adjacentPos1 = adjacentPos.first;
			int adjacentPos2 = adjacentPos.second;
			if (adjacentPos1 >= 0 && adjacentPos1 < m_boardSize && adjacentPos2 >= 0 && adjacentPos2 < m_boardSize) {
				if (m_board[adjacentPos1][adjacentPos2][0] == oponentColor) {
					return make_pair(true, make_pair(adjacentPos1, adjacentPos2));
				}
			}
		}
	}
	return make_pair(false, make_pair(-1,-1));
}

/* *********************************************************************
Function Name: CanAdvance
Purpose:
	Returns true if position can advance  to the  destination position. This is relative to the player's color
Parameters:
	all parameters passed by value
	int startPos1			- row value for starting position
	int startPos2			- column value for starting position
	int stopPos1			- row value for possible destination position
	int stopPos2			- column value for possible destination position
	char myColor		- color of the player that has to move
	char oponentColor	- color of the opponent player
Return Value:
	bool value - true if the starting position can advance to the destination position
Local Variables:
	string mySuperPiece		- string containing the symbol for super piece
	string direction		- string containing direction of the move (SE/SW/NE/NW)
Algorithm:
	- based on start and destination position get the direction of the move.
	- if the direction of the move is forward.
		- if I am a super piece and there is an opponent at the destination. 
			- I can advance else I am blocked
		- if I am not a super piece check if destiantion is a value position where I can advance or if destination is not occupied.
			- if yes advance == true else advance== false
Assistance Received: none
********************************************************************* */
bool Board::CanAdvance(int startPos1, int startPos2, int stopPos1, int stopPos2, char myColor, char oponentColor) {
	string mySuperPiece = CharToString(myColor) + CharToString(myColor);
	string direction = GetMoveDirection(make_pair(startPos1, startPos2), make_pair(stopPos1, stopPos2));
	if (myColor == 'W' && (direction == "SE" || direction == "SW")) {
		if (m_board[startPos1][startPos2] == mySuperPiece) {
			// If I am a super piece, I can advance even if my opponent is a super color.
			if (m_board[stopPos1][stopPos2][0] == oponentColor) {
				return true;
			}
		}
		else {
			// If I am not a super piece, I can advance only if destination is not occupied or if it is an oponenty on a value pos.
			if (m_board[stopPos1][stopPos2][0] == oponentColor && IsValuePos(stopPos1, stopPos2, myColor)) {
				return true;
			}
			if (m_board[stopPos1][stopPos2][0] == 'O') {
				return true;
			}
		}
	}

	if (myColor == 'B' && (direction == "NE" || direction == "NW")) {
		if (m_board[startPos1][startPos2] == mySuperPiece) {
			// If I am a super piece, I can advance even if my opponent is a super color.
			if (m_board[stopPos1][stopPos2][0] == oponentColor) {
				return true;
			}
		}
		else {
			// If I am not a super piece, I can advance only if destination is not occupied or if it is an opponent on a value position.
			if (m_board[stopPos1][stopPos2][0] == oponentColor && IsValuePos(stopPos1, stopPos2, myColor)) {
				return true;
			}
			// destination not occupied.
			if (m_board[stopPos1][stopPos2][0] == 'O') {
				return true;
			}
		}
	}
	return false;
}

/* *********************************************************************
Function Name: CanMoveBackward
Purpose:
	Returns true if position can move backward to the  destination position. This is relative to the player's color
Parameters:
	all parameters passed by value
	int startPos1			- row value for starting position
	int startPos2			- column value for starting position
	int stopPos1			- row value for possible destination position
	int stopPos2			- column value for possible destination position
	char myColor		- color of the player that has to move
	char oponentColor	- color of the opponent player
Return Value:
	bool value - true if the starting position can advance to the destination position
Local Variables:
	string mySuperPiece		- string containing the symbol for super piece
	string direction		- string containing direction of the move (SE/SW/NE/NW)
Algorithm:
	- based on start and destination position get the direction of the move.
	- if the direction of the move is backward.
		- if I am a super piece and there is an opponent at the destination.
			- I can advance else I am blocked
		- if I am not a super piece check if destiantion is a value position where I can advance or if destination is not occupied.
			- if yes advance == true else advance== false
Assistance Received: none
********************************************************************* */
bool Board::CanMoveBackward(int startPos1, int startPos2, int stopPos1, int stopPos2, char myColor, char oponentColor) {
	string mySuperPiece = CharToString(myColor) + CharToString(myColor);
	string direction = GetMoveDirection(make_pair(startPos1, startPos2), make_pair(stopPos1, stopPos2));
	if (myColor == 'W' && (direction == "NE" || direction == "NW")) {
		if (m_board[startPos1][startPos2] == mySuperPiece) {
			// If I am a super piece, I can advance even if my opponent is a super color.
			if (m_board[stopPos1][stopPos2][0] == oponentColor) {
				return true;
			}
		}
		else {
			// If I am not a super piece, I can advance only if destination is not occupied or if it is an oponenty on a value pos.
			if (m_board[stopPos1][stopPos2][0] == oponentColor && IsValuePos(stopPos1, stopPos2, myColor)) {
				return true;
			}
			if (m_board[stopPos1][stopPos2][0] == 'O') {
				return true;
			}
		}
	}

	if (myColor == 'B' && (direction == "SE" || direction == "SW")) {
		if (m_board[startPos1][startPos2] == mySuperPiece) {
			// If I am a super piece, I can advance even if my opponent is a super color.
			if (m_board[stopPos1][stopPos2][0] == oponentColor) {
				return true;
			}
		}
		else {
			// If I am not a super piece, I can advance only if destination is not occupied or if it is an opponent on a value position.
			if (m_board[stopPos1][stopPos2][0] == oponentColor && IsValuePos(stopPos1, stopPos2, myColor)) {
				return true;
			}
			// destination not occupied.
			if (m_board[stopPos1][stopPos2][0] == 'O') {
				return true;
			}
		}
	}
	return false;
}

/* *********************************************************************
Function Name: GetOneMove
Purpose:
	Verify if a move from start to destination position is possible. If yes, return an object of type Move with all the information
	that would allow us later to take a decision and pick the best possible move. 
Parameters:
	all parameters passed by value
	int startPos1			- row value for starting position
	int startPos2			- column value for starting position
	int stopPos1			- row value for possible destination position
	int stopPos2			- column value for possible destination position
	char myColor		- color of the player that has to move
	char oponentColor	- color of the opponent player
Return Value:
	Move object - an object of type Move with all the information that would allow us later to take a decision and pick the best possible move. 
Local Variables:
	Move possibleMove - instance of class move storing info about the current move
	string mySuperPiece		- string containing the symbol for super piece
Algorithm:
	- if the move is possible (falls inside the board).
		- yes 
			- if destination position is not occupied by my piece and it is empty
				- yes -> collect move info, store it in the move object and return it to calling function
				- no -> position is occupied by an opponent
					- am I a super piece
						- yes - move is possible, collect info, return an empty move.
						- no -> 
							- is the opponent on a value position that can be captured
								yes -> move is possible, collect info, return move object
								no  -> move is not possible. Return an empty move.
		- no - return an empty move object
Assistance Received: none
********************************************************************* */
Move Board::GetOneMove(int startPos1, int startPos2, int stopPos1, int stopPos2, char myColor, char oponentColor, string direction) {
	Move possibleMove;
	string mySuperPiece = CharToString(myColor) + CharToString(myColor);
	//Position objStartPos, objEndPos;
	if (stopPos1 >= 0 && stopPos1 < m_boardSize && stopPos2 >= 0 && stopPos2 < m_boardSize) {
		if (m_board[stopPos1][stopPos2][0] != myColor) {
			if (m_board[stopPos1][stopPos2][0] == 'O') {

				possibleMove.SetStartPos(make_pair(startPos1, startPos2));
				possibleMove.SetEndPos(make_pair(stopPos1, stopPos2));
				possibleMove.SetDirection(direction);
				// We are moving on an unoccupied position so we are just checking for value pos.
				if (IsValuePos(stopPos1, stopPos2, myColor)) {
					// If we are moving on a position that has value, we check the start value vs stop value.
					// We will assign a value to this move only if the stop value is higher than the start value
					// Otherwise assign 0 value. It is a move like any other. 
					if (GetSquareValue(make_pair(stopPos1, stopPos2)) > GetSquareValue(make_pair(startPos1, startPos2))) {
						possibleMove.SetValue(GetSquareValue(make_pair(stopPos1, stopPos2)));
					}
					else {
						possibleMove.SetValue(0);
					}
				}
				else {
					possibleMove.SetValue(0);
				}

				possibleMove.SetCanCapture(CanCapture(startPos1, startPos2, stopPos1, stopPos2, myColor, oponentColor));
				pair<bool, pair<int, int>> canBeCaptured = CanBeCaptured(startPos1, startPos2, myColor, oponentColor);
				possibleMove.SetCanBeCaptured(canBeCaptured.first);
				possibleMove.SetCanCaptureSrc(canBeCaptured.second);
				pair<bool, pair<int, int>> canDestBeCapture = CanDestBeCaptured(stopPos1, stopPos2, myColor, oponentColor);
				possibleMove.SetCanDestBeCaptured(canDestBeCapture.first);
				possibleMove.SetCanCaptureDst(canDestBeCapture.second);
				// next sequence sets info about next move being able to block the advance of the opponent as well as the opponent that can be blocked.
				//pair<bool, pair<int, int>> canBlockAdvance = CanBlockAdvance(startPos1, startPos2, myColor, oponentColor);
				pair<bool, pair<int, int>> canBlockAdvance = CanBlockAdvance(stopPos1, stopPos2, myColor, oponentColor);
				possibleMove.SetCanBlockAdvance(canBlockAdvance.first);
				possibleMove.SetBlockedOponent(canBlockAdvance.second);
				possibleMove.SetCanAdvance(CanAdvance(startPos1, startPos2, stopPos1, stopPos2, myColor, oponentColor));
				possibleMove.SetCanMoveBackward(CanMoveBackward(startPos1, startPos2, stopPos1, stopPos2, myColor, oponentColor));
				return possibleMove;
			}
			else {
				// If on the destination position is an opponent, this move is possible only if I am a super piece. 
				if (m_board[startPos1][startPos2] == mySuperPiece) {
					possibleMove.SetStartPos(make_pair(startPos1, startPos2));
					possibleMove.SetEndPos(make_pair(stopPos1, stopPos2));
					possibleMove.SetDirection(direction);
					// If I am a super piece I get 5 pointsautomatically for capturing an opponent plus the eventual value of the 
					if (IsValuePos(stopPos1, stopPos2, myColor)) {
						possibleMove.SetValue(GetSquareValue(make_pair(stopPos1, stopPos2)) + 5);
					} else {
						possibleMove.SetValue(0);
					}

					possibleMove.SetCanCapture(CanCapture(startPos1, startPos2, stopPos1, stopPos2, myColor, oponentColor));
					pair<bool, pair<int, int>> canBeCaptured = CanBeCaptured(startPos1, startPos2, myColor, oponentColor);
					possibleMove.SetCanBeCaptured(canBeCaptured.first);
					possibleMove.SetCanCaptureSrc(canBeCaptured.second);
					pair<bool, pair<int, int>> canDestBeCapture = CanDestBeCaptured(stopPos1, stopPos2, myColor, oponentColor);
					possibleMove.SetCanDestBeCaptured(canDestBeCapture.first);
					possibleMove.SetCanCaptureDst(canDestBeCapture.second);
					//pair<bool, pair<int, int>> canBlockAdvance = CanBlockAdvance(startPos1, startPos2, myColor, oponentColor);
					pair<bool, pair<int, int>> canBlockAdvance = CanBlockAdvance(stopPos1, stopPos2, myColor, oponentColor);
					possibleMove.SetCanBlockAdvance(canBlockAdvance.first);
					possibleMove.SetBlockedOponent(canBlockAdvance.second);
					possibleMove.SetCanAdvance(CanAdvance(startPos1, startPos2, stopPos1, stopPos2, myColor, oponentColor));
					possibleMove.SetCanMoveBackward(CanMoveBackward(startPos1, startPos2, stopPos1, stopPos2, myColor, oponentColor));
					return possibleMove ;
				}
				else {
					// If I am not a super piece, I can move on an opponent position only if it is a value position.
					if (IsValuePos(stopPos1, stopPos2, myColor)) {
						possibleMove.SetStartPos(make_pair(startPos1, startPos2));
						possibleMove.SetEndPos(make_pair(stopPos1, stopPos2));
						possibleMove.SetDirection(direction);
						// I already know the position is a value position and occupied by an opponent.
						possibleMove.SetValue(GetSquareValue(make_pair(stopPos1, stopPos2)) + 5);
						possibleMove.SetCanCapture(CanCapture(startPos1, startPos2, stopPos1, stopPos2, myColor, oponentColor));
						pair<bool, pair<int, int>> canBeCaptured = CanBeCaptured(startPos1, startPos2, myColor, oponentColor);
						possibleMove.SetCanBeCaptured(canBeCaptured.first);
						possibleMove.SetCanCaptureSrc(canBeCaptured.second);
						pair<bool, pair<int, int>> canDestBeCapture = CanDestBeCaptured(stopPos1, stopPos2, myColor, oponentColor);
						possibleMove.SetCanDestBeCaptured(canDestBeCapture.first);
						possibleMove.SetCanCaptureDst(canDestBeCapture.second);
						//pair<bool, pair<int, int>> canBlockAdvance = CanBlockAdvance(startPos1, startPos2, myColor, oponentColor);
						pair<bool, pair<int, int>> canBlockAdvance = CanBlockAdvance(stopPos1, stopPos2, myColor, oponentColor);
						possibleMove.SetCanBlockAdvance(canBlockAdvance.first);
						possibleMove.SetBlockedOponent(canBlockAdvance.second);
						possibleMove.SetCanAdvance(CanAdvance(startPos1, startPos2, stopPos1, stopPos2, myColor, oponentColor));
						possibleMove.SetCanMoveBackward(CanMoveBackward(startPos1, startPos2, stopPos1, stopPos2, myColor, oponentColor));
						return possibleMove;
					}
				}
			}
		}
	}
	return possibleMove;
}

/* *********************************************************************
Function Name: GetAllMovesForOnePos
Purpose:
	Given a position return all available moves from that position. By available means, moves that can actually happen.
Parameters:
	all parameters passed by value
	int startPos1			- row value for starting position
	int startPos2			- column value for starting position
	char myColor		- color of the player that has to move
	char oponentColor	- color of the opponent player
Return Value:
	vector<Move> -  a list of possible moves for the provided position
Local Variables:
	vector<Move> allMovesForOnePos -  a list of possible moves from provided position
	Move possibleMove - instance of class move storing info about the current move atempt
	string mySuperPiece		- string containing the symbol for super piece
Algorithm:
	- check all 4 possible directions to move from the starting position
	- if this is a possible move
		- collect all info and add it to the list of possible moves
	- at the end return the list of possible moves
Assistance Received: none
********************************************************************* */
vector<Move> Board::GetAllMovesForOnePos(int startPos1, int startPos2, char myColor, char oponentColor) {
	vector<Move> allMovesForOnePos;
	Move possibleMove;
	//string mySuperPiece = CharToString(myColor) + CharToString(myColor);
	// Checking all 4 directions (SE, SW, NE, NW) and verify if they are possible moves
	for (int i = 0; i < m_directions.size(); i++) {
		pair<int, int> adjacentPos = GetPosByDirection(make_pair(startPos1, startPos2), m_directions[i]);
		int stopPos1 = adjacentPos.first;
		int stopPos2 = adjacentPos.second;
		possibleMove = GetOneMove(startPos1, startPos2, stopPos1, stopPos2, myColor, oponentColor, m_directions[i]);
		if (possibleMove.GetDirection() != "") {
			allMovesForOnePos.push_back(possibleMove);
		}
	}
	return allMovesForOnePos;
}

/* *********************************************************************
Function Name: GetPosByDirection
Purpose:
	Given a position and a direction of move, return the coordinates
Parameters:
	all parameters passed by value
	int startPos1			- row value for starting position
	int startPos2			- column value for starting position
	string direction		- direction of the move
Return Value:
	pair<int, int> -  cordinates of the destination based on starting position and the move.
Local Variables:	
	int pos1		- row for starting position
	int pos2		- column for starting position
	int endPos1		- row for destination position
	int endPos2		- column for destination position
Algorithm:
	For starting position, check each possible direction and calculate coordinates of the possible direction
Assistance Received: none
********************************************************************* */
pair<int, int> Board::GetPosByDirection(pair<int, int> pos, string direction) {
	int pos1, pos2, endPos1, endPos2;
	pos1 = pos.first;
	pos2 = pos.second;
	if (direction == "SE") {
		endPos1 = pos1 + 1;
		endPos2 = pos2 + 1;
	}
	else if (direction == "SW") {
		endPos1 = pos1 + 1;
		endPos2 = pos2 - 1;
	}
	else if (direction == "NW") {
		endPos1 = pos1 - 1;
		endPos2 = pos2 - 1;
	}
	else if (direction == "NE") {
		endPos1 = pos1 - 1;
		endPos2 = pos2 + 1;
	}
	return make_pair(endPos1, endPos2);
}

/* *********************************************************************
Function Name: GetMoveDirection
Purpose:
	Given a start and destination positionreturn the direction as a string having possible values of SE/SW/NE/NW
Parameters:
	all parameters passed by value
	pair<int,int> startPos			- pair of integers describing the starting position
	pair<int,int> endPos			- pair of integers describing the destination position
Return Value:
	string direction - string containing direction of the move
Local Variables:
	int startPos1	- row for starting position
	int startPos2	- column for starting position
	int endPos1		- row for destination position
	int endPos2		- column for destination position
Algorithm:
	Compare starting and destination positions and return corresponding direction
Assistance Received: none
********************************************************************* */
string Board::GetMoveDirection(pair<int, int> startPos, pair<int, int> endPos) {
	int startPos1, startPos2, endPos1, endPos2;
	startPos1 = startPos.first;
	startPos2 = startPos.second;
	endPos1 = endPos.first;
	endPos2 = endPos.second;
	if (endPos1 == startPos1 + 1 && endPos2 == startPos2 + 1) {
		// SE - SouthEast
		return "SE";
	}
	else if (endPos1 == startPos1 + 1 && endPos2 == startPos2 - 1) {
		// SW - SouthWest
		return "SW";
	}
	else if (endPos1 == startPos1 - 1 && endPos2 == startPos2 - 1) {
		// NW - NorthWest
		return "NW";
	}
	else if (endPos1 == startPos1 - 1 && endPos2 == startPos2 + 1) {
		// NE - NorthEast
		return "NE";
	}
	else {
		// This is an invalid code. It will be tested when function is called.
		// NA stands for Not Available code
		return "NA";
	}
}