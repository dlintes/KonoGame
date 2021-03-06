/*
************************************************************
* Name:  Liana Lintes
* Project : Project1 - C++ project            *
* Class : CMPS 366 01 Sp18 - Organization of Programming Languages                       *
* Date : 02/27/2018                           *
************************************************************
*/

// kono.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Human.h"
#include "Tournament.h"
#include "Round.h"
#include "Computer.h"
#include "BoardView.h"
#include "Util.h"
#include <ctime>
#include <string>
#include <utility>
#include <sstream>
#include <fstream>
#include <errno.h>
#include <algorithm>
#include <cstdio>

using namespace std;

tuple<BoardView, Board, Human, Computer, Tournament, Round> StartGame(BoardView boardview, Human human, Computer computer, Tournament tournament, Round round, pair<char, string> resumeGame);

/* *********************************************************************
Function Name: main
Purpose:
	Instantiate required objects and drives the game by alternately allowing each player to move.

Parameters:
	None
Return Value:
	integer - success
Local Variables:
	BoardView boardview		- instance of the BoardView class. Responsible with I/O operations
	Human human				- instance of Human class.
	Computer computer		- instance of Computer class
	Tournament tournament	- instance of Tournament class
	Round round				- instance of Round class
	char color				- color of the players
	string strInput			- takes standard input for various situations
	string strColor			- string to store color for super pieces
	pair <int, int> startPos, endPos - pair of integers describeing start and destination positions
	bool playRound			- bool value used to loop while playing the current round.
	string statusFile		- stores the default value of the file containing the saved status of the game.
	tuple<Board, Human, Computer, Round, Tournament, bool> humanMoveTuple
	tuple<Board, Human, Computer, Round, Tournament, bool> computerMoveTuple
	tuple<Board, Human, Computer, Round, Tournament, bool> helpManrMoveTuple
							- the above threee tuples are used to get back the objects listed in the tuple.
							- they were introduced as we tried to avoid passing objects by reference into functions that have to change these objects.
	Util util				- instance of Util class that contains utility functions that are common to other functions.

Algorithm:
	Check if the game will be resumed.
		- if yes -> load the status
		- if not -> get starting info (starting player, color of each player, size of the board)
	Initialize the needed objects
	Enter into a loop where menu is displayed and input is asked for chosen options
	Chose apropriate action for each chosen option.

Assistance Received: none
********************************************************************* */

int main()
{
	char color;
	string strInput;
	string strColor;
	pair <int, int> startPos, endPos;
	bool playRound = true;
	string statusFile = "SavedStatus.txt";
	
	// Initialize tournament outside of the loop. round will be initialized in the loop
	Tournament tournament;
	BoardView boardview;
	Util util;

	//Checking if to start a new game or resume the game from file.
	pair<char, string> resumeGame = boardview.ResumeGame();
	if (resumeGame.first == 'Y') {
		string resumeFile = resumeGame.second;
		std::ifstream file(resumeFile);
		cout << "Game will resume. Game status will be loaded from file: " + resumeFile << endl;
		boardview.RetrieveSavedGameInfo(resumeFile);
		pair<bool, string> isValid = boardview.ValidInfo();
		if (isValid.first == false) {
			cout << "Error: " << isValid.second << endl;
			cout << "Exit game!" << endl;
			return 0;
		}
		tournament.SetComputerPoints(boardview.GetComputerScore());
		tournament.SetHumanPoints(boardview.GetHumanScore());
		tournament.SetRound(boardview.GetRound());
	}
	

	while (playRound == true) {
		int size = 0;
		Player player;
		Human human;
		Computer computer;
		Round round;
		//Board board;

		tuple<BoardView, Board, Human, Computer, Tournament, Round> gameTuple = StartGame(boardview, human, computer, tournament, round, resumeGame);
		boardview = get<0>(gameTuple);
		Board board = get<1>(gameTuple);
		human = get<2>(gameTuple);
		computer = get<3>(gameTuple);
		tournament = get<4>(gameTuple);
		round = get<5>(gameTuple);

		// resetting resume game info as this is not needed in this loop. We are asked to reload the game from file only once when game is restarted.
		// once playing rounds in the loop this option is not needed anymore.
		resumeGame = make_pair('N', "");

		bool gameOn = true;
		while (gameOn) {
			string** boardSnapshot = board.GetBoard();
			int boardSize = board.GetBoardSize(); 
			boardview.PrintBoard(boardSnapshot, boardSize);
			if (round.GetNextPlayer() == "human") {
				std::cout << endl <<  "Human moves." << endl;
			}
			else {
				std::cout << endl << "Computer moves." << endl;
			}

			string menuOption = boardview.roundMenu(round.GetNextPlayer());
			if (menuOption == "S") {
				int roundNr = tournament.GetRound();
				std::cout << "The game was saved in file SaveStatus.txt" << endl;
				std::cout << "Next time the game is restarted it will continue from the current status" << endl;
				// Save tournament status in  the status file
				boardview.SaveStatus(board, tournament, round, human, computer);
				return 0;
			}
			else if (menuOption == "M") {
				if (round.GetNextPlayer() == "human") {
					tuple<Board, Human, Computer, Round, Tournament, bool> humanMoveTuple = boardview.HumanMoves(board, human, computer, round, tournament);
					board = get<0>(humanMoveTuple);
					human = get<1>(humanMoveTuple);
					computer = get<2>(humanMoveTuple);
					round = get<3>(humanMoveTuple);
					tournament = get<4>(humanMoveTuple);
					bool endGame = get<5>(humanMoveTuple);
					if (endGame == true) {
						break;
					}
				}
				else {
					tuple<Board, Human, Computer, Round, Tournament, bool> computerMoveTuple = boardview.ComputerMoves(board, human, computer, round, tournament);
					board = get<0>(computerMoveTuple);
					human = get<1>(computerMoveTuple);
					computer = get<2>(computerMoveTuple);
					round = get<3>(computerMoveTuple);
					tournament = get<4>(computerMoveTuple);
					bool endGame = get<5>(computerMoveTuple);
					if (endGame == true) {
						string** boardSnapshot = board.GetBoard();
						int boardSize = board.GetBoardSize();
						boardview.PrintBoard(boardSnapshot, boardSize);
						break;
					}
				}
			}
			else if (menuOption == "H") {
				//tuple<Board, Human, Computer, Round, Tournament, bool> helpManTuple = boardview.HelpMankind(board, human, computer, round, tournament);
				std::cout << "Human asked for help. Computer moves for human." << endl;
				// Calculate move method, calculates the move depending on board status. Second parameter is consider my color and third opponent's color.
				// This way can be used for both human and computer to calculate the strategy.
				Move suggestedMove = computer.CalculateMove(board, human.GetColour(), computer.GetColour());
				//Move suggestedMove = boardview.HelpMankind(board, human, computer, round, tournament);
				string dispSuggestedMove = "(" + util.ToString(suggestedMove.GetStartPos().first + 1) + "," + util.ToString(suggestedMove.GetStartPos().second + 1) + ") " + suggestedMove.GetDirection();
				cout << "Suggested move: " << dispSuggestedMove << endl;
				cout << "Reason for move: " << suggestedMove.GetReasonForMove() << endl;
				tuple<Board, Human, Computer, Round, Tournament, bool> humanMoveTuple = boardview.HumanMoves(board, human, computer, round, tournament);
				board = get<0>(humanMoveTuple);
				human = get<1>(humanMoveTuple);
				computer = get<2>(humanMoveTuple);
				round = get<3>(humanMoveTuple);
				tournament = get<4>(humanMoveTuple);
				bool endGame = get<5>(humanMoveTuple);
				if (endGame == true) {
					string** boardSnapshot = board.GetBoard();
					int boardSize = board.GetBoardSize();
					boardview.PrintBoard(boardSnapshot, boardSize);
					break;
				}
			}
			else if (menuOption == "Q") {
				std::cout << "Exit game !" << endl;
				round.SetExitGamePlayer(round.GetNextPlayer());
				round.CalculatePoints(board, human, computer);
				// The point difference between the 2 players is awarded to the winner and added to the tournament total.
				if (round.GetWinner() == "human") {
					tournament.SetHumanPoints(tournament.GetHumanPoints() + round.GetWinerBonus());
				} else {
					tournament.SetComputerPoints(tournament.GetComputerPoints() + round.GetWinerBonus());
				}
				break;
			}
		}
		if (boardview.PlayAnotherRound(human, computer, tournament, round) == false) {
			break;
		}
		// Set the previous round winner. To be used in the new round to decide who starts.
		tournament.SetPreviousRoundWinner(round.GetWinner());
		tournament.SetRound(tournament.GetRound() + 1);
		cout << "Tournament human score: " << tournament.GetHumanPoints() << endl;
		cout << "Tournament computer score: " << tournament.GetComputerPoints() << endl;
	}
	system("pause");
	return 0;
}


/* *********************************************************************
Function Name: StartGame
Purpose:
To chose the board size, each player's color and decide who will move first. It will also ask if the game should be started from a previous position
and initialize the board based on the saved status of the game.
Parameters:
all parameters passed by value
BoardView boardview		- instance of the BoardView class. Responsible with I/O operations
Human human				- instance of Human class.
Computer computer		- instance of Computer class
Tournament tournament	- instance of Tournament class
Round round				- instance of Round class
resumeGame				- pair<char, string> - pair of a char and a string
- the char can take values Y/N and indicets if the game can be resumed or not
- the string contains the name of the file where game status is saved. It will be used to load status if resume = 'Y'.
Return Value:
tuple<BoardView, Board, Human, Computer, Tournament, Round> -  a tuple containing BoardView, Board, Human, Computer, Tournament, Round objects
These objects are instantiated once and modified in the loop while the game is playing. Since we were advised to avoid passing parameters by
reference we are passing them by value, modify them in the function and return them back, thus keeping the changes.
Local Variables:
int size - chosen size of the board
pair<pair<char, bool>, pair<char, bool>> retPair - a pair of pairs of char and bool variables.
- the char in the inner pair  stores the color of the player
- the bool in the inner pair describes if the player will be first or not.
- the outer pair contains one pair for humen and one pair for computer. Each of these pairs describeing the color and who starts the game.
pair<char, bool> hPair - describes the color and if the human moves first or not.
pair<char, bool> cPair - describes the color and if the computer moves first or not.
Algorithm:
Player is asked if the game will be resumed or starting a new game.
If a new game starts, board size is entered, dices are rolled and it is decided who will be the player to start the game as well as color of each player.
If game is to be resumed from a status file
- ask the name of the file (a default file name can also be used).
- read the file and parse the info for players, tournament scores and board status.
- load the info into the board object.
Assistance Received: none
********************************************************************* */
tuple<BoardView, Board, Human, Computer, Tournament, Round>
StartGame(BoardView boardview, Human human, Computer computer, Tournament tournament, Round round, pair<char, string> resumeGame) {
	int size = 0;
	if (resumeGame.first != 'Y') {
		// When starting a new round ask for board size			
		while (true) {
			std::cout << "Enter board size [5/7/9]: ";
			cin >> size;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Entered value: " << size << endl;
			if (size != 5 && size != 7 && size != 9) {
				cout << "Entered value is not valid. Accepted values are 5, 7 or 9. Please try again." << endl;
				continue;
			}
			break;
		}
		if (tournament.GetRound() > 1) {
			if (tournament.GetPrevRoundWinner() == "human") {
				pair<char, char> colorPair = boardview.HumanChosesColor();
				human.SetColour(colorPair.first);
				computer.SetColour(colorPair.second);
			}
			else {
				computer.SetColour('B');
				human.SetColour('W');
			}
			// If this is not the first round, set the starting player based on the previous round results.
			if (tournament.GetPrevRoundWinner() == "human") {
				round.SetNextPlayer("human");
			}
			else {
				round.SetNextPlayer("computer");
			}
		}
		else {
			// If this is the starting round and game is not resumed from the file,
			// we are chosing the first player by rolling dices.
			bool loadDice;
			char ask = ' ';
			while (ask != 'Y' &&  ask != 'N') {
				cout << "Do you want to load the dice values from a file? [Y/N]: ";
				cin >> ask;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				ask = toupper(ask);
			}
			// ask is converted to appercase already. Testing only for the upper case.
			loadDice = false;
			if (ask == 'Y') {
				loadDice = true;
			}
			pair<pair<char, bool>, pair<char, bool>> retPair = boardview.ChosePlayer(human, computer, loadDice);
			pair<char, bool> hPair = retPair.first;
			pair<char, bool> cPair = retPair.second;

			if (hPair.second == true) {
				round.SetNextPlayer("human");
			}
			else {
				round.SetNextPlayer("computer");
			}
			human.SetColour(hPair.first);
			computer.SetColour(cPair.first);
			std::cout << "Computer color: " << computer.GetColour() << endl;
			std::cout << "Human color: " << human.GetColour() << endl;
		}
	}
	else {
		// Setting relevant board info based on the retrieved info from saved file.
		size = boardview.GetBoardSize();
		// Set next turn and color
		round.SetNextPlayer(boardview.GetNextPlayer());
		computer.SetColour(boardview.GetComputerColor()[0]);
		human.SetColour(boardview.GetHumanColor()[0]);
	}
	Board board(size);
	if (resumeGame.first == 'Y') {
		board.SetBoard(boardview.GetBoard());
	}
	return std::make_tuple(boardview, board, human, computer, tournament, round);
}