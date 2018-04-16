#include "stdafx.h"
#include "Round.h"

using namespace std;


/* *********************************************************************
Function Name: Round
Purpose: Constructor for Round class
Parameters: None
Return Value: None
Local Variables: Initializes the class private variables:
	m_winnerBonus - bonus granted to the winner
	m_winner - round winner
	m_nextPlayer - who's turn is to move
	m_exitGamePlayer - name of the player who exit the game.
	m_computerPoints - total points for computer for the round
	m_humanPoints - total points for the human for the round
Assistance Received: none
********************************************************************* */
Round::Round()
{
	m_winnerBonus = 0;
	m_winner = "";
	m_nextPlayer = "";
	m_exitGamePlayer = "";
	m_computerPoints = 0;
	m_humanPoints = 0;
}

/* *********************************************************************
Function Name : SetWinner
Purpose : to store the name of the winner for the round. Used for later reporting at the end of the game
Parameters :
	all parameters passed by value
	string containing the name of the winner
Return Value : 
	None
Local Variables :
	None - it stores [passed parameter into the class' private variabel
Algorithm :
Assistance Received : none
* ******************************************************************** */
bool Round::SetWinner(string winner)
{
	m_winner = winner;
	return true;
}

/* *********************************************************************
Function Name: GetWinner
Purpose:
Returns who the winner is
Parameters:
none
Return Value:
string m_winner			- round winner
Assistance Received: none
********************************************************************* */
string const Round::GetWinner()
{
	return m_winner;
}

/* *********************************************************************
Function Name: GetComputerPoints
Purpose:
Returns the total points for computer for the round
Parameters:
none
Return Value:
int m_computerPoints	- total points for computer for the round
Assistance Received: none
********************************************************************* */
int const Round::GetComputerPoints()
{
	return m_computerPoints;
}

/* *********************************************************************
Function Name: GetHumanPoints
Purpose:
Returns the total points for the human for the round
Parameters:
none
Return Value:
int m_humanPoints	- total points for the human for the round
Assistance Received: none
********************************************************************* */
int const Round::GetHumanPoints()
{
	return m_humanPoints;
}

/* *********************************************************************
Function Name: GetWinerBonus
Purpose:
Returns who the bonus granted to the winner
Parameters:
none
Return Value:
int	m_winnerBonus	- bonus granted to the winner
Assistance Received: none
********************************************************************* */
int const Round::GetWinerBonus()
{
	return m_winnerBonus;
}

/* *********************************************************************
Function Name: SetWinnerBonus
Purpose:
Sets m_winnerBonus to equal int winnerBonus
Parameters:
all parameters passed by value
int winnerBonus	- holds value of winner bonus
Return Value:
none
Assistance Received: none
********************************************************************* */
bool Round::SetWinnerBonus(int winnerBonus)
{
	m_winnerBonus = winnerBonus;
	return true;
}

/* *********************************************************************
Function Name: SetNextPlayer
Purpose:
Sets m_nextPlayer to equal string nextPlayer
Parameters:
all parameters passed by value
string nextPlayer	- holds value of who the next player is
Return Value:
none
Assistance Received: none
********************************************************************* */
bool Round::SetNextPlayer(string nextPlayer)
{
	m_nextPlayer = nextPlayer;
	if (nextPlayer != "human" && nextPlayer != "computer") {
		return false;
	}
	return true;	
}

/* *********************************************************************
Function Name: GetNextPlayer
Purpose:
Returns who the next player is
Parameters:
none
Return Value:
string	m_nextPlayer	 - who's turn is to move
Assistance Received: none
********************************************************************* */
string Round::GetNextPlayer()
{
	return m_nextPlayer;
}

/* *********************************************************************
Function Name: SetExitGamePlayer
Purpose:
Sets m_exitGamePlayer to equal string player (i.e the player who exits the game)
Parameters:
all parameters passed by value
string player	- holds value of who the player is
Return Value:
none
Assistance Received: none
********************************************************************* */
bool Round::SetExitGamePlayer(string player)
{
	m_exitGamePlayer = player;
	return true;
}

/* *********************************************************************
Function Name: GetExitGamePlayer
Purpose:
Returns name of the player who exit the game.
Parameters:
none
Return Value:
string m_exitGamePlayer		- name of the player who exit the game.
Assistance Received: none
********************************************************************* */
string const Round::GetExitGamePlayer()
{
	return m_exitGamePlayer;
}

/* *********************************************************************
Function Name: CalculatePoints
Purpose: To calculate the points at the end of the game for a player.
Parameters:
	all parameters passed by value
	board - object of type Board - contains info related to layout of the pieces.
	human - object of type human - contains info related to human player 
	computer - object of type human - contains info related to Computer player 
Return Value:
	No return value. Calculated values are stored in the class' private variables.
Local Variables:
	int awardPoints - variable to store points awarded to the winner.
	pair<int, int> pairHumanPoints - pair of integers that contain total points for the human player and the number of pieces of the player at the end of the game.
	pair<int, int> pairComputerPoints = pair of integers that contain total points for the computer and the number of pieces of the player at the end of the game.
	int humanPoints - total points for the human
	int humanPieces - total pieces for the human
	int computerPoints - total points for the computer;
	int computerPieces - total pieces for the human;
	int totalPlayerPieces - nnumber of pieces at the start of the game for a player. Depends on the board size.
	int totalHumanPoints - integer that cumulates the total points for human
	int totalComputerPoints = - integer that cumulates the total points for computer;
Algorithm:
	Calculate the value for each piece of the player and the number of pieces remaining on the table.
	Compare the 2 values and awards a bonus to the winner which is equal to the difference between the winner and the other player's points.
	Stores relevan information in private variables for ease of reporting.
Assistance Received: none
********************************************************************* */
void Round::CalculatePoints(Board board, Human human, Computer computer) {
	string winner;
	int awardPoints;
	pair<int, int> pairHumanPoints = human.CalculatePositionPoints(board);
	pair<int, int> pairComputerPoints = computer.CalculatePositionPoints(board);
	int humanPoints = pairHumanPoints.first;
	int humanPieces = pairHumanPoints.second;
	int computerPoints = pairComputerPoints.first;
	int computerPieces = pairComputerPoints.second;
	int totalPlayerPieces = board.GetBoardSize() + 2;
	// Assign to human 5 points for each computer piece that was captured
	int totalHumanPoints = humanPoints + (totalPlayerPieces - computerPieces) * 5;
	// Assign to computer 5 points for each human piece that was captured
	int totalComputerPoints = computerPoints + (totalPlayerPieces - humanPieces) * 5;
	// If human exit the game, subtract 5 points for the human
	if (m_exitGamePlayer == "human") {
		totalHumanPoints = totalHumanPoints - 5;
	}
	// If computer exit the game, subtract 5 points for the human
	if (m_exitGamePlayer == "computer") {
		totalComputerPoints = totalComputerPoints - 5;
	}
	// For the player having the most points, award the difference between the total points
	if (totalHumanPoints > totalComputerPoints) {
		m_winner = "human";
		m_winnerBonus = totalHumanPoints - totalComputerPoints;
		//totalHumanPoints = totalHumanPoints + m_winnerBonus;
	}
	else {
		m_winner = "computer";
		m_winnerBonus = totalComputerPoints - totalHumanPoints;
		//totalComputerPoints = totalComputerPoints + m_winnerBonus;
	}
	m_humanPoints = totalHumanPoints;
	m_computerPoints = totalComputerPoints;	
}