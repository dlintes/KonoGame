#include "stdafx.h"
#include "Move.h"

using namespace std;

/* *********************************************************************
Function Name: Move
Purpose: Constructor for move class. This class holds info associated with a move of a piece from start position to end position
Parameters:
	None. Initializes class' private data members.
Return Value: 
	None
Local Variables:
	m_value - value associated with the move. Calculated as a sum of the end position's value plus 5 if the move can capture an opponent.
	m_startPos			- pair of integers describing (row,col) for starting position;
	m_endPos			- pair of integers describing (row,col) for destination position;
	m_canCaptureSrc		- pair of integers describing the position of the opponent that can capture the start position of this move.
	m_canCaptureDst		- pair of integers describing the position of the opponent that can capture the destination position of this move.
	m_blockedOponent	- pair of integers describing the position of the opponent that can be blocked by this move.
	m_reasonForMove		- string that contains the reason for picking that move, such as to avoid capture or to capture an opponent.
	m_direction			- string that describes direction of the move. Accepted values NE/NW/SE/SW.
	m_canBeCaptured		- bool value describing if the start position of the move can be captured by an opponent
	m_canDestBeCaptured - bool value describing if the destination position of the move can be captured by an opponent
	m_canCapture		- bool value describing if an opponent can be captured by this move.
	m_canBlock			- bool value describing if this move can block an opponent or not.
	m_canAdvance		- bool value describing if this move can advance without being captured
	m_canMoveBackward	- bool value describing if this move can move back without being captured
Algorithm:
Assistance Received: none
********************************************************************* */
Move::Move()
{
	m_value = 0;
	m_startPos = make_pair(0, 0);
	m_endPos = make_pair(0, 0);
	m_canCaptureSrc = make_pair(-1, -1);
	m_canCaptureDst = make_pair(-1, -1);
	m_blockedOponent = make_pair(-1, -1);
	m_reasonForMove = "";
	m_direction = "";
	m_canBeCaptured = false;
	m_canDestBeCaptured = false;
	m_canCapture = false;
	m_canBlock = false;
	m_canAdvance = false;
	m_canMoveBackward = false;
}

/* *********************************************************************
Function Name: SetValue
Purpose:
	Sets the value associated with the move to a variable to be put in a getter function later
Parameters:
	all parameters passed by value
	int value	- value to be set for the move
Return Value:
	bool - true or false
Assistance Received: none
********************************************************************* */
bool Move::SetValue(int value) {
	m_value = value;
	return true;
};

/* *********************************************************************
Function Name: GetValue
Purpose:
Returns the value associated with the move
Parameters:
none
Return Value:
int m_value - value associated with the move. Calculated as a sum of the end position's value plus 5 if the move can capture an oponent.
Assistance Received: none
********************************************************************* */
int const Move::GetValue() {
	return m_value;
};

/* *********************************************************************
Function Name: SetStartPos
Purpose:
	Sets the start position
Parameters:
	all parameters passed by value
	pair<int, int> pos	- location of start position of piece
Return Value:
	boole - true or false. No need for validation here as data was already validated before
Assistance Received: none
********************************************************************* */
bool Move::SetStartPos(pair<int, int> pos)
{
	m_startPos = pos;
	return true;
}

/* *********************************************************************
Function Name: GetStartPos
Purpose:
	Returns the start position
Parameters:
	none
Return Value:
	pair<int, int> m_startPos	- location of previously set start position of piece
Assistance Received: none
********************************************************************* */
pair<int, int> const Move::GetStartPos()
{
	return m_startPos;
}

/* *********************************************************************
Function Name: SetEndPos
Purpose:
	Sets the end pos
Parameters:
	all parameters passed by value
	pair<int, int> pos		- position on board desired to be end position
Return Value:
	bool - true or false. No need to validate as validation is done before calling it
Assistance Received: none
********************************************************************* */
bool Move::SetEndPos(pair<int, int> pos)
{
	m_endPos = pos;
	return true;
}

/* *********************************************************************
Function Name: GetEndPos
Purpose:
	Gets the end pos
Parameters:
	none
Return Value:
	pair<int, int> m_endPos		- position on board that was previously set as end position
Assistance Received: none
********************************************************************* */
pair<int, int> const Move::GetEndPos()
{
		return m_endPos;
}

/* *********************************************************************
Function Name: SetCanCaptureSrc
Purpose:
Sets the position in the paramater to be a pair of integers describing position where the oponent can capture the start pos of this move
Parameters:
	all parameters passed by value
	pair<int, int> pos		- position on board
Return Value:
	bool - true or false. 
	No need for validation. It is done before function being called.
Assistance Received: none
********************************************************************* */
bool Move::SetCanCaptureSrc(pair<int, int> pos)
{
	m_canCaptureSrc = pos;
	return true;
}

/* *********************************************************************
Function Name: GetCanCaptureSrc
Purpose:
Returns the position in the paramater to be a pair of integers describing position where the oponent can capture the start pos of this move
Parameters:
none
Return Value:
pair<int, int> m_canCaptureSrc		- pair of integers describing the position of the oponent that can capture the start position of this move.
Assistance Received: none
********************************************************************* */
pair<int, int> const Move::GetCanCaptureSrc()
{
	return m_canCaptureSrc;
}

/* *********************************************************************
Function Name: SetCanCaptureDst
Purpose:
	Sets the position in the paramater to be the position of the oponent that can capture the destination position of this move.
Parameters:
	all parameters passed by value
	pair<int, int> pos		- position desired to be set as stated in purpose
Return Value:
	bool - true or false
	No need for validation. Done before function is called.
Assistance Received: none
********************************************************************* */
bool Move::SetCanCaptureDst(pair<int, int> pos)
{
	m_canCaptureDst = pos;
	return true;
}

/* *********************************************************************
Function Name: GetCanCaptureDst
Purpose:
	Returns the position in the paramater to be the position of the oponent that can capture the destination position of this move.
Parameters:
	none
Return Value:
	pair<int, int> m_canCaptureDst		- pair of integers describing the position of the oponent that can capture the destination position of this move.
Assistance Received: none
********************************************************************* */
pair<int, int> const Move::GetCanCaptureDst()
{
	return m_canCaptureDst;
}

/* *********************************************************************
Function Name: SetDirection
Purpose:
	Sets m_direction to be the parameter passed that describes direction of the move. Accepted values NE/NW/SE/SW.
Parameters:
	all parameters passed by value
	string direction	- string that describes direction of the move. Accepted values NE/NW/SE/SW.
Return Value:
	bool - true or false
Assistance Received: none
********************************************************************* */
bool Move::SetDirection(string direction)
{
	m_direction = direction;
	if (direction != "NE" && direction != "NW" && direction != "SE" && direction != "SW") {
		return false;
	}
	return true;
}

/* *********************************************************************
Function Name: GetDirection
Purpose:
Sets m_direction to be the parameter passed that describes direction of the move. Accepted values NE/NW/SE/SW.
Parameters:
none
Return Value:
string m_direction		- string that describes direction of the move. Accepted values NE/NW/SE/SW.
Assistance Received: none
********************************************************************* */
string const Move::GetDirection()
{
	return m_direction;
}

/* *********************************************************************
Function Name: SetReasonForMove
Purpose:
	Sets m_reasonForMove to be the parameter passed that describes reason for the move.
Parameters:
	all parameters passed by value
	string reason		-string that holds the reason for the move
Return Value:
	bool - false or true. 
	No need for validation as the reason is a string
Assistance Received: none
********************************************************************* */
bool Move::SetReasonForMove(string reason)
{
	m_reasonForMove = reason;
	return true;
}

/* *********************************************************************
Function Name: GetReasonForMove
Purpose:
	Returns m_reasonForMove
Parameters:
	none
Return Value:
	string m_reasonForMove		- string that contains the reason for picking that move, such as to avoid capture or to capture an oponent.
Assistance Received: none
********************************************************************* */
string const Move::GetReasonForMove()
{
	return m_reasonForMove;;
};

/* *********************************************************************
Function Name: SetCanBeCaptured
Purpose:
	Sets m_canBeCaptured to be passed var parameter
Parameters:
	all parameters passed by value
	bool var	-  describes if the start position of the move can be captured by an oponent
Return Value:
	bool - true or false
Assistance Received: none
********************************************************************* */
bool Move::SetCanBeCaptured(bool var)
{
	m_canBeCaptured = var;
	return true;
}

/* *********************************************************************
Function Name: GetCanBeCaptured
Purpose:
	Returns m_canBeCaptured
Parameters:
	none
Return Value:
	bool m_canBeCaptured		- bool value describing if the start position of the move can be captured by an oponent
Assistance Received: none
********************************************************************* */
bool const Move::GetCanBeCaptured()
{
	return m_canBeCaptured;
}

/* *********************************************************************
Function Name: SetCanDestBeCaptured
Purpose:
	Sets m_canDestBeCaptured to be passed var parameter
Parameters:
	all parameters passed by value
	bool var		-  describes if the destination position of the move can be captured by an oponent
Return Value:
	bool - true or false
Assistance Received: none
********************************************************************* */
bool Move::SetCanDestBeCaptured(bool var)
{
	m_canDestBeCaptured = var;
	return true;
}

/* *********************************************************************
Function Name: GetCanDestBeCaptured
Purpose:
Returns m_canBeCaptured
Parameters:
none
Return Value:
bool m_canDestBeCaptured - bool value describing if the destination position of the move can be captured by an oponent
Assistance Received: none
********************************************************************* */
bool const Move::GetCanDestBeCaptured()
{
	return m_canDestBeCaptured;
}

/* *********************************************************************
Function Name: SetCanCapture
Purpose:
	Sets m_canCapture to be passed var parameter
Parameters:
	bool var	-  describes if an oponent can be captured by this move.
Return Value:
	bool - true or false
Assistance Received: none
********************************************************************* */
bool Move::SetCanCapture(bool var)
{
	m_canCapture = var;
	return true;
}

/* *********************************************************************
Function Name: GetCanCapture
Purpose:
	Returns m_canCapture
Parameters:
	none
Return Value:
	bool m_canCapture		- bool value describing if an oponent can be captured by this move.
Assistance Received: none
********************************************************************* */
bool const Move::GetCanCapture()
{
	return m_canCapture;
}

/* *********************************************************************
Function Name: SetCanBlockAdvance
Purpose:
	Sets m_canBlock to be passed var parameter
Parameters:
	all parameters passed by value
	bool var - describes if this move can block an oponent or not.
Return Value:
	bool - true or false
	No need to validate as function is set in the program and the passed variable
	can only have these 2 values.
Assistance Received: none
********************************************************************* */
bool Move::SetCanBlockAdvance(bool var)
{
	m_canBlock = var;
	return true;
}

/* *********************************************************************
Function Name: GetCanBlockAdvance
Purpose:
	Getter - gets the value of m_canBlockAdvance
Returns m_canBlock
Parameters:
	none
Return Value:
	bool m_canBlock			- bool value describing if this move can block an oponent or not.
Assistance Received: none
********************************************************************* */
bool const Move::GetCanBlockAdvance()
{
	return m_canBlock;
}

/* *********************************************************************
Function Name: SetCanAdvance
Purpose:
	Sets m_canAdvance to be passed var parameter
Parameters:
	all parameters passed by value
	bool var		- describes if this move can advance without being captured
Return Value:
	bool - true or false
	No need to validate as this is only set in the program. 
Assistance Received: none
********************************************************************* */
bool Move::SetCanAdvance(bool var)
{
	m_canAdvance = var;
	return true;
}

/* *********************************************************************
Function Name: GetCanAdvance
Purpose:
Returns m_canAdvance
Parameters:
none
Return Value:
bool m_canAdvance		- bool value describing if this move can advance without being captured
Assistance Received: none
********************************************************************* */
bool const Move::GetCanAdvance()
{
	return m_canAdvance;
}

/* *********************************************************************
Function Name: SetCanMoveBackward
Purpose:
	Sets m_canMoveBackward to passed var parameter
Parameters:
	all parameters passed by value
	bool var		- describes if this move can move back without being captured
Return Value:
	bool - true or false
	No need to validate. Set in the program.
Assistance Received: none
********************************************************************* */
bool Move::SetCanMoveBackward(bool var)
{
	m_canMoveBackward = true;
	return true;
}

/* *********************************************************************
Function Name: GetCanMoveBackward
Purpose:
	Returns m_canMoveBackward
Parameters:
	none
Return Value:
	bool m_canMoveBackward		- bool value describing if this move can move back without being captured
Assistance Received: none
********************************************************************* */
bool const Move::GetCanMoveBackward()
{
	return m_canMoveBackward;
}

/* *********************************************************************
Function Name: SetBlockedOponent
Purpose:
	Sets m_blockedOponent to passed var parameter
Parameters:
	all parameters passed by value
	pair<int, int> pos	- pair of integers describing the position of the oponent that can be blocked by this move.
Return Value:
	bool - true or false
Assistance Received: none
********************************************************************* */
bool Move::SetBlockedOponent(pair<int, int> pos)
{
	m_blockedOponent = pos;
	return true;
}

/* *********************************************************************
Function Name: GetBlockedOponent
Purpose:
	Returns m_blockedOponent
Parameters:
	none
Return Value:
	pair<int,int> m_blockedOponent	- pair of integers describing the position of the oponent that can be blocked by this move.
Assistance Received: none
********************************************************************* */
pair<int,int> const Move::GetBlockedOponent()
{
	return m_blockedOponent;
}