#pragma once
//
//		Player.h - Kono Player class header.
//		Liana Lintes - 01/22/2018
//

#include <string>
#include "Board.h"

class Player {

public:

	Player() {
		m_Color = ' ';
	};

	// Prints the current status of the game board
	virtual char GetColour() { return m_Color; };
	virtual bool SetColour(char color) ;
	virtual int RollDice();
	virtual bool EndOfGame(Board board);
	virtual pair<int,int> CalculatePositionPoints(Board board);

private:
	// stores the colour of the game set for this player.
    char m_Color;
};