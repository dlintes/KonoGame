#pragma once
//
//		Computer.h - Kono Computer class header.
//		Liana Lintes - 01/24/2018
//

#include <string>
#include "Player.h"
#include <vector>
#include <tuple>
#include <functional>
#include <map>
#include "Board.h"
#include "Move.h"


class Computer : public Player {

public:


	Computer() {};
	Move CalculateMove(Board board, char compColor, char humanColor);
	Move GetBestMove(vector<Move> allPlayerMoves);
	string GetMoveDirection(pair<int, int> startPos, pair<int, int> endPos);

private:
};