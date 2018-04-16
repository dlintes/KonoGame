#pragma once

//
//		Player.h - Kono BoardView class header.
//		Liana Lintes - 01/23/2018
//


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include "Board.h" 
#include "Tournament.h"
#include "Round.h" 
#include "Human.h" 
#include "Computer.h"
#include "Util.h"

#define NE "NE"
#define SE "SE"
#define NW "NW"
#define SW "SW"

using namespace std;

class BoardView {

public:
	BoardView();
	BoardView(string statusFile);
	void RetrieveSavedGameInfo(string fileName);
	void SaveStatus(Board board, Tournament tournament, Round round, Human human, Computer computer);
	string ConvertColor(char color);
	void PrintBoard(string ** board, int boardSize);
	void PrintBoard(int ** boardValues, int boardSize);
	int const GetHumanScore();
	int const GetComputerScore();
	int const GetRound();
	int const GetBoardSize();
	string const GetHumanColor();
	string const GetComputerColor();
	string const GetNextPlayer();
	string** const GetBoard();
	pair<bool, string> ValidInfo();
	string roundMenu(string nextPlayer);
	bool PlayAnotherRound(Human human, Computer computer, Tournament tournament, Round round);
	tuple<Board, Human, Computer, Round, Tournament, bool> ComputerMoves(Board board, Human human, Computer computer, Round round, Tournament tournament);
	tuple<Board, Human, Computer, Round, Tournament, bool> HumanMoves(Board board, Human human, Computer computer, Round round, Tournament tournament);
	pair<char, string> ResumeGame();
	bool FileExists(const string fileName);
	pair<pair<char, bool>, pair<char, bool>> ChosePlayer(Human human, Computer computer, bool loadDice);
	pair<int, int> GetDiceFromFile(string fileName);
	pair<char, char> HumanChosesColor();

private:
	int m_savedHumanScore, m_savedComputerScore, m_savedRoundNr, m_savedBoardSize;
	string m_savedHumanColor, m_savedComputerColor, m_statusFile, m_nextPlayer;
	bool m_isValidData;
	string** m_savedBoard;
};
