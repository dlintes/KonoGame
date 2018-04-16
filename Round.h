#pragma once
//
//		Round.h - Kono Round class header.
//		Liana Lintes - 01/24/2018
//

#include <string>
#include <iostream>
#include <algorithm>
#include "Board.h"
#include "Human.h"
#include "Computer.h"


using namespace std;

class Round {

public:

	Round();
	~Round() {};

	bool SetWinner(string winner);
	string const GetWinner();
	int const GetComputerPoints();
	int const GetHumanPoints();
	int const GetWinerBonus() ;
	bool SetWinnerBonus(int winnerBonus) ;
	bool SetNextPlayer(string nextPlayer) ;
	string GetNextPlayer();
	bool SetExitGamePlayer(string player);
	string const GetExitGamePlayer() ;
	void CalculatePoints(Board board, Human human, Computer computer);

private:	
	int m_number;
	int m_winnerBonus;
	int m_computerPoints, m_humanPoints;
	string m_winner, m_nextPlayer, m_exitGamePlayer;
};