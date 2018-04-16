#pragma once

//
//		Board.h - Kono game board class header.
//		assembler
//		Liana Lintes - 01/22/2018
//

#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <sstream>
#include "Move.h"

using namespace std;

class Board {

public:

	Board() ;
	Board(int size) ;

	void InitBoard(int size);
	void InitBoardValues(int size);
	int GetBoardSize();
	string** GetBoard();
	void SetBoard(string** savedBoard) ;
	bool SetBoardPiece(pair<int, int> startPos, pair<int, int> stopPos,string playerColor);
	bool ResetBoardPiece(pair<int, int> pos);
	int ** GetBoardValues();
	void MovePiece(pair<int, int> startPos, pair<int, int> endPos, string playerColor, string oponentColor);
	int GetSquareValue(pair<int, int> pos);
	string GetSquareColor(int pos1, int pos2);
	vector<std::pair<int, int>> GetListOfPieces(char myColor);
	pair<int, int> GetPosByDirection(pair<int, int> pos, string direction);
	string GetMoveDirection(pair<int, int> startPos, pair<int, int> endPos);
	bool IsValuePos(int pos1, int pos2, char color);
	string CharToString(char input);
	pair<bool, pair<int, int>> CanDestBeCaptured(int pos1, int pos2, char myColor, char oponentColor);
	pair<bool,pair<int,int>> CanBeCaptured(int pos1, int pos2, char myColor, char oponentColor);
	bool CanCapture(int startPos1, int startPos2, int stopPos1, int stopPos2, char myColor, char oponentColor);
	pair<bool, pair<int, int>> CanBlockAdvance(int pos1, int pos2, char myColor, char oponentColor);
	bool CanAdvance(int startPos1, int startPos2, int stopPos1, int stopPos2, char myColor, char oponentColor);
	bool CanMoveBackward(int startPos1, int startPos2, int stopPos1, int stopPos2, char myColor, char oponentColor);
	Move GetOneMove(int startPos1, int startPos2, int stopPos1, int stopPos2, char myColor, char oponentColor, string direction);
	vector<Move> GetAllMovesForOnePos(int startPos1, int startPos2, char myColor, char oponentColor);

private:	
	string **m_board;
	int **m_boardValues;
	int m_boardSize;
	// a list containing all 4 possible directions to move (SE, SW, NE, NW)
	vector<string> m_directions;
};
