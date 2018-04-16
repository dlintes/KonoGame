#include "stdafx.h"
#include "Computer.h"
#include "Move.h"
#include "Util.h"
#include <tuple>
#include <functional>
#include <string>

#define NE "NE"
#define SE "SE"
#define NW "NW"
#define SW "SW"

using namespace std;

/* *********************************************************************
Function Name: CalculateMove
Purpose: To calculate the best possible move for all pieces of the player based on a set of criteria.
         It is intended for the computer player but it is designed to be used by the human when computer is asked for help.
Parameters:
	all parameters passed by value
	Board board		- instance of Board class containing game status
	char compColor	- computer player color of pieces
	char humanColor - human player color of pieces
Return Value: 
	Move object - an instance of class move containing info about the move ot be made.
Local Variables:
	vector<Move> allPlayerMoves		- list of objects of type Move. Contains all the possible move for the current player
	allMovesForOnePos				- list of objects of type Move. Contains all the possible move for the current player for one position
	Move bestMove					- instance of lcas smove. Contains best move out of all possible moves of the current player
	vector<pair<int, int>> result	- a list of positions representing positions of all pieces of the current player on the board
	int index						- integer variable to traverse the vectors defined in this method.
	string** boardSnapshot			- pointer to another pointer representing string values. It is used to represent as a double array of strings the color of the 
									  player's pieces on the table.

Algorithm:
	- first it verifies if the board size is 5. In this case first recommendation is a set of hard coded moves that are deemed the best in this case
	  as they will lead to capturing at least 2 opponent pieces.
	- if first recommended set of moves are not available calculate the lsit of all pieces on the board
	- calculate all available moves for one position
	- build the list of all available moves for the player.
	- iterates through all possible/available moves and picks the best one. The criteria for picking the best move is described for the GetBestMove documentation.
Assistance Received: none
********************************************************************* */
Move Computer::CalculateMove(Board board, char compColor, char humanColor)
{
	vector<Move> allPlayerMoves, allMovesForOnePos;
	Move bestMove;

	string** boardSnapshot = board.GetBoard();
	// This is a hard coded set of recommendations for the first move of either computer or human
	// on a 5 by 5 table.
	if (board.GetBoardSize() == 5) {
		if (compColor == 'W') {
			if (boardSnapshot[1][0] == "W" && boardSnapshot[2][1] == "O") {
				bestMove.SetReasonForMove("To capture opponent at (4,1)");
				bestMove.SetDirection(SE);
				bestMove.SetStartPos(make_pair(1, 0));
				bestMove.SetEndPos(make_pair(2, 1));
				bestMove.SetValue(0);
				return bestMove;
			}
			if (boardSnapshot[1][4] == "W" && boardSnapshot[2][3] == "O") {
				bestMove.SetReasonForMove("To capture opponent at (4,5)");
				bestMove.SetDirection(SW);
				bestMove.SetStartPos(make_pair(1, 4));
				bestMove.SetEndPos(make_pair(2, 3));
				bestMove.SetValue(0);
				return bestMove;
			}
		}
		else if (compColor == 'B') {
			if (boardSnapshot[3][0] == "B" && boardSnapshot[2][1] == "O") {
				bestMove.SetReasonForMove("To capture opponent at (2,1)");
				bestMove.SetDirection(NE);
				bestMove.SetStartPos(make_pair(3, 0));
				bestMove.SetEndPos(make_pair(2, 1));
				bestMove.SetValue(0);
				return bestMove;
			}
			if (boardSnapshot[3][4] == "B" && boardSnapshot[2][3] == "O") {
				bestMove.SetReasonForMove("To capture opponent at (2,5)");
				bestMove.SetDirection(NW);
				bestMove.SetStartPos(make_pair(3, 4));
				bestMove.SetEndPos(make_pair(2, 3));
				bestMove.SetValue(0);
				return bestMove;
			}
		}
	}

	// Get a list of all pieces owned by the player that moves
	vector<pair<int, int>> result = board.GetListOfPieces(compColor);
	for (int index = 0; index < result.size(); ++index)
	{
		// Moves cumulated into allMovesForOnePos are added to allPlayerMoves vector to be later analyzed and compared in order to pick the best move.
		allMovesForOnePos = board.GetAllMovesForOnePos(result[index].first, result[index].second, compColor, humanColor);
		for (int indexMove = 0; indexMove < allMovesForOnePos.size(); ++indexMove) {
			allPlayerMoves.push_back(allMovesForOnePos[indexMove]);
		}
	}

	// At this stage we have a vector that contains all possible moves for this board snapshot.
	// Analyze them and pick one.
	return GetBestMove(allPlayerMoves);
}

/*
Iterates through all possible moves and picks the best move.
*/
/* *********************************************************************
Function Name: GetBestMove
Purpose: 
	Iterates through the list of possible moves and picks the best one based on a set of criteria.
Parameters:
	all parameters passed by value
	vector<Move> allPlayerMoves - list of all possible moves for the current player.
Return Value:
	Move - object of type move containing info about the best possible move picked.
Local Variables:
	Move bestMove			- stores the best move
	Util myFunctions		- object to allow access to common functions/utilities.
	bool canCapture			- bool variable. If this move can capture an opponent set to tru, else set to false
	string captor			- stores info about the move that can be captured.
	bool higherValue		- bool variable to identify if the inspected move is of higher value
	bool advanceAndBlock	- if this move allows the piece to advance and block an opponent, set to true, else set to false.
	int indexMove			- integer to traverse the lists from this method
	bool canMoveBackward	- if this move allows the piece to move backward, set to true, else set to false.
Algorithm:
	- find the first move that can result in capturing an opponent and return it.
	- iterate again through all possible moves and find one that can be captured based on the start position and can advance and will not be captured at the destination. 
	  This will be next best move.
	- Iterate again through all possible move and find one that can be captured and can move backward. That is the next best move.
	- Iterate again through all possible moves and find one that can potentially produce the  highest possible value. This is the next best move.
	- Iterate through the possible moves and pick one that can advance block the opponent. This is the next best move.
	- If we cannot advance and block at the same time find the one that can only advance while not being captured. This is the next best move.
	- Last attempt, find one that can move backwards without being captured at the destination as all previous better options have been exhausted already.
	- if none of the above produced a best move, return an empty move.
Assistance Received: none
********************************************************************* */

Move Computer::GetBestMove(vector<Move> allPlayerMoves) {
	//Iterates through all possible moves and picks the move that can capture an opponent and values the most.
	Move bestMove;
	Util myFunctions;
	bool canCapture = false;
	for (int indexMove = 0; indexMove < allPlayerMoves.size(); ++indexMove) {
		if (allPlayerMoves[indexMove].GetCanCapture() == true) {
			canCapture = true;
			if (allPlayerMoves[indexMove].GetValue() >= bestMove.GetValue()) {
				bestMove = allPlayerMoves[indexMove];
			}
		}
	}
	// If we found a move that can capture an opponent for the highest possible value, return that one as the chosen move.
	if (canCapture == true) {
		// Adding one to convert from array access to table display
		bestMove.SetReasonForMove("Capture opponent at (" + myFunctions.ToString(bestMove.GetEndPos().first + 1) + "," + myFunctions.ToString(bestMove.GetEndPos().second + 1) + ")");
		return bestMove;
	}

	// Iterate again through all possible move and find one that can be captured based on the start position and can advance and will not be captured at the destination.
	// That is the one we should be moving first.
	for (int indexMove = 0; indexMove < allPlayerMoves.size(); ++indexMove) {
		if (allPlayerMoves[indexMove].GetCanBeCaptured() == true && allPlayerMoves[indexMove].GetCanAdvance() == true && allPlayerMoves[indexMove].GetCanDestBeCaptured() == false) {
			string captor = "(" + myFunctions.ToString(allPlayerMoves[indexMove].GetCanCaptureSrc().first + 1) + "," + myFunctions.ToString(allPlayerMoves[indexMove].GetCanCaptureSrc().second + 1) + ")";
			allPlayerMoves[indexMove].SetReasonForMove("To avoid being captured by opponent at:" + captor);
			return allPlayerMoves[indexMove];
		}
	}
	// We already know there are no positions that can be captured and can move forward.
	// Iterate again through all possible move and find one that can be captured and can move backward. That is the one we should be moving next.
	for (int indexMove = 0; indexMove < allPlayerMoves.size(); ++indexMove) {
		if (allPlayerMoves[indexMove].GetCanBeCaptured() == true && allPlayerMoves[indexMove].GetCanMoveBackward() == true) {
			string captor = "(" + myFunctions.ToString(allPlayerMoves[indexMove].GetCanCaptureSrc().first + 1) + "," + myFunctions.ToString(allPlayerMoves[indexMove].GetCanCaptureSrc().second + 1) + ")";
			allPlayerMoves[indexMove].SetReasonForMove("To avoid being captured by opponent at : " + captor);
			return allPlayerMoves[indexMove];
		}
	}

	// At this stage we had no move that would allow us to capture an opponent and had no piece that could be captured by an opponent.
	// Iterate again through all possible moves and find one that can potentially produce the  highest possible value.
	int bestValue = 0;
	bool higherValue = false;
	for (int indexMove = 0; indexMove < allPlayerMoves.size(); ++indexMove) {
		if (allPlayerMoves[indexMove].GetValue() > bestValue && allPlayerMoves[indexMove].GetCanDestBeCaptured() == false) {
			// if start pos is a value pos and end pos is a value pos, move to end pos only if end pos is more valuable 
			higherValue = true;
			bestMove = allPlayerMoves[indexMove];
		}
	}
	if (higherValue == true) {
		bestMove.SetReasonForMove("Move to the location with highest value amongst current possible moves: (" + myFunctions.ToString(bestMove.GetEndPos().first + 1) + ", " + myFunctions.ToString(bestMove.GetEndPos().second + 1) + ")");
		return bestMove;
	}

	// At this stage all moves have the same value (0) associated with the move. Iterate through the possible moves and pick one that can advance block the opponent.
	bestMove;
	bool advanceAndBlock = false;
	for (int indexMove = 0; indexMove < allPlayerMoves.size(); ++indexMove) {
		// test if it can block an opponent by advancing (and not moving backward) and if advancing to that destination does not mean it will be captured.
		if (allPlayerMoves[indexMove].GetCanBlockAdvance() == true && allPlayerMoves[indexMove].GetCanAdvance() == true && allPlayerMoves[indexMove].GetCanDestBeCaptured() == false) {
			advanceAndBlock = true;
			bestMove = allPlayerMoves[indexMove];
		}
	}
	if (advanceAndBlock == true) {
		string blockedOponent = "(" + myFunctions.ToString(bestMove.GetBlockedOponent().first + 1) + "," + myFunctions.ToString(bestMove.GetBlockedOponent().second + 1) + ")";
		bestMove.SetReasonForMove("To advance and block the opponent at: " + blockedOponent);
		return bestMove;
	}

	// If we cannot advance and block at the same time find the one that can only advance while not being captured.
	bestMove;
	bool canAdvance = false;
	for (int indexMove = 0; indexMove < allPlayerMoves.size(); ++indexMove) {
		if (allPlayerMoves[indexMove].GetCanAdvance() == true && allPlayerMoves[indexMove].GetCanDestBeCaptured() == false) {
			canAdvance = true;
			bestMove = allPlayerMoves[indexMove];
		}
	}
	if (canAdvance == true) {
		bestMove.SetReasonForMove("To advance without the risk of being captured at the destination in the next move.");
		return bestMove;
	}

	// Last attempt, find one that can move backwards without being captured at the destination as all previous better options have been exhausted already.
	bestMove;
	bool canMoveBackward = false;
	for (int indexMove = 0; indexMove < allPlayerMoves.size(); ++indexMove) {
		if (allPlayerMoves[indexMove].GetCanMoveBackward() == true && allPlayerMoves[indexMove].GetCanDestBeCaptured() == false) {
			canMoveBackward = true;
			bestMove = allPlayerMoves[indexMove];
		}
	}
	if (canMoveBackward == true) {
		bestMove.SetReasonForMove("Move backward to a position where it cannot be captured in the next move. This is the only option left.");
		return bestMove;
	}
	// Returning an empty move. This will be tested on the caller's end.
	return bestMove;
}

/* *********************************************************************
Function Name: GetMoveDirection
Purpose: 
	To calculate the direction of the move based on the start and end position. It is used for displaying the direction of the move.
Parameters:
	all parameters passed by value
	pair<int,int> startPos	- pair of integers describing the start position 
	pair<int,int> endPos	- pair of integers describing the destination position 
Return Value: 
	string - string value describing the direction of the move (southwest, southeast, northwest, northeast).
Local Variables:
	int startPos1	- row value of start position
	int startPos2	- column value of start position
	int endPos1		- row value of destination position
	int endPos2		- column value of destination position
Algorithm:
	Given the start and end position decide the direction of the move.
Assistance Received: none
********************************************************************* */
string Computer::GetMoveDirection(pair<int,int> startPos, pair<int,int> endPos) {
	int startPos1, startPos2, endPos1, endPos2;
	startPos1 = startPos.first;
	startPos2 = startPos.second;
	endPos1 = endPos.first;
	endPos2 = endPos.second;
	if (endPos1 == startPos1 + 1 && endPos2 == startPos2 + 1) {
		return "southeast";
	}
	else if (endPos1 == startPos1 + 1 && endPos2 == startPos2 - 1) {
		return "southwest";
	}
	else if (endPos1 == startPos1 - 1 && endPos2 == startPos2 - 1) {
		return "northwest";
	}
	else if (endPos1 == startPos1 - 1 && endPos2 == startPos2 + 1) {
		return "northeast";
	}
	else {
		// This is an invalid code. It will be tested when function is called.
		return "NA";
	}
}