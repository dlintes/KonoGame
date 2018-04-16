#pragma once
#include <string>
#include "Computer.h"

class Tournament {
public:
	Tournament();
	void SetRound(int round);
	int const GetRound();
	bool SetComputerPoints(int points);
	int const GetComputerPoints();
	bool SetHumanPoints(int points);
	int const GetHumanPoints();
	bool SetPreviousRoundWinner(string winner);
	string const GetPrevRoundWinner();

private:
	string m_prevRoundWinner;
	int m_computerPoints, m_humanPoints, m_round;
};