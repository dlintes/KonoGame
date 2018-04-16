#include "stdafx.h"
#include "Tournament.h"

using namespace std;

/* *********************************************************************
Function Name: Tournament
Purpose: Constructor for Tournament class
Parameters:
	None
Return Value: 
	None
Local Variables: 
	Initializes the class private variables:
	m_round  - round number
	m_computerPoints - total points in the tournament for the computer
	m_humanPoints - total points in the tournament for the computer
	m_prevRoundWinner - winner of the previous round
Assistance Received: none
********************************************************************* */
Tournament::Tournament()
{
	m_round = 1;
	m_computerPoints = 0;
	m_humanPoints = 0;
	m_prevRoundWinner = "";
};

/* *********************************************************************
Function Name: SetRound
Purpose:
Sets  m_round to the round number
Parameters:
all parameters passed by value
int round			- round number
Return Value:
none
Assistance Received: none
********************************************************************* */
void Tournament::SetRound(int round)
{
	m_round = round;
};

/* *********************************************************************
Function Name: GetRound
Purpose:
Returns the round number
Parameters:
none
Return Value:
int m_round			 - round number
Assistance Received: none
********************************************************************* */
int const Tournament::GetRound()
{
	return m_round;
};

/* *********************************************************************
Function Name: SetComputerPoints
Purpose:
Sets m_computerPoints to the total points in the tournament for the computer
Parameters:
all parameters passed by value
int points			- total points in the tournament for the computer
Return Value:
none
Assistance Received: none
********************************************************************* */
bool Tournament::SetComputerPoints(int points)
{
	m_computerPoints = points;
	return true;
};

/* *********************************************************************
Function Name: SetHumanPoints
Purpose:
Sets m_humanPoints to the total points in the tournament for the human
Parameters:
all parameters passed by value
int points			- total points in the tournament for the human
Return Value:
none
Assistance Received: none
********************************************************************* */
bool Tournament::SetHumanPoints(int points)
{
	m_humanPoints = points;
	return true;
};

/* *********************************************************************
Function Name: GetComputerPoints
Purpose:
Returns the total points in the tournament for the computer
Parameters:
none
Return Value:
int	m_computerPoints		- total points in the tournament for the computer
Assistance Received: none
********************************************************************* */
int const Tournament::GetComputerPoints()
{
	return m_computerPoints;
};

/* *********************************************************************
Function Name: GetPrevRoundWinner
Purpose:
Returns winner of the previous round
Parameters:
none
Return Value:
string m_prevRoundWinner - winner of the previous round
Assistance Received: none
********************************************************************* */
string const Tournament::GetPrevRoundWinner()
{
	return m_prevRoundWinner;
};

/* *********************************************************************
Function Name: SetPreviousRunWinner
Purpose:
Sets m_prevRoundWinner to the winner of previous round
Parameters:
all parameters passed by value
string winner			- total points in the tournament for the human
Return Value:
none
Assistance Received: none
********************************************************************* */
bool Tournament::SetPreviousRoundWinner(string winner)
{
	m_prevRoundWinner = winner;
	return true;
};

/* *********************************************************************
Function Name: GetHumanPoints
Purpose:
Returns the total points in the tournament for the human
Parameters:
none
Return Value:
int	m_humanPoints		- total points in the tournament for the human
Assistance Received: none
********************************************************************* */
int const Tournament::GetHumanPoints()
{
	return m_humanPoints;
};