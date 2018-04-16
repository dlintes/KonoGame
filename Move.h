#pragma once

#pragma once
//
//		Move.h - Kono Move class header.
//		Liana Lintes - 02/08/2018
//

#include <string>
//#include "Util.h"

using namespace std;

class Move {

public:

	Move();

	bool SetValue(int value);
	int const GetValue();

	bool SetStartPos(pair<int,int> pos);
	pair<int,int> const GetStartPos();

	bool SetEndPos(pair<int,int> pos);
	pair<int,int> const GetEndPos() ;

	bool SetCanCaptureSrc(pair<int, int> pos);
	pair<int, int> const GetCanCaptureSrc();

	bool SetCanCaptureDst(pair<int, int> pos);
	pair<int, int> const GetCanCaptureDst();

	bool SetDirection(string direction);
	string const GetDirection(); 

	bool SetReasonForMove(string reason);
	string const GetReasonForMove();

	bool SetCanBeCaptured(bool var);
	bool const GetCanBeCaptured();

	bool SetCanDestBeCaptured(bool var);
	bool const GetCanDestBeCaptured();

	bool SetCanCapture(bool var);
	bool const GetCanCapture();

	bool SetCanBlockAdvance(bool var);
	bool const GetCanBlockAdvance();

	bool SetCanAdvance(bool var);
	bool const GetCanAdvance();

	bool SetCanMoveBackward(bool var);
	bool const GetCanMoveBackward();

	bool SetBlockedOponent(pair<int,int> pos);
	pair<int,int> const GetBlockedOponent();

private:

	int m_value;
	pair<int, int> m_startPos, m_endPos, m_canCaptureSrc, m_canCaptureDst, m_blockedOponent;
	string m_direction, m_reasonForMove;
	bool  m_canBeCaptured, m_canDestBeCaptured, m_canCapture, m_canBlock, m_canAdvance, m_canMoveBackward;
};