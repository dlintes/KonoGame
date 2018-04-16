#pragma once

//
//		Human.h - Kono Human class header.
//		Liana Lintes - 01/22/2018
//

#include <string>
#include "Player.h"
#include <utility>
#include "Board.h"


class Human: public Player {

public:

	Human() {};
	pair<bool, string> ValidateInput(Board board, pair<int,int> startPos, pair<int,int> endPos, char playerColor, char oponentColor);
	pair<int, int> ConvertInputToPosition(int startPos1, int startPos2, string direction);

private:
};