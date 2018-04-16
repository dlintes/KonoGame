#pragma once
//
//		Position.h - Kono Position class header.
//		Liana Lintes - 02/09/2018
//

#include <string>
#include "Human.h"
#include "Computer.h"
#include "Round.h"

#define NE "NE"
#define SE "SE"
#define NW "NW"
#define SW "SW"

using namespace std;

class Util {

public:
	// Nothing to initialize in the constructor. So no body created in cpp file
	Util() {};
	string CharToString(char input);
	string ToString(int input);
	bool ValidatePosition(pair<int, int> pos, int boardSize);
	bool ValidatePosition(int pos1, int pos2, int boardSize);
	bool ValidateDirectionValue(string direction);

private:
	
};