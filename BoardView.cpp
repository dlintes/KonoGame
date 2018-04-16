#include "stdafx.h"
#include "BoardView.h"

using namespace std;

/* *********************************************************************
Function Name: BoardView
Purpose: 
	Default constructor for class BoardView
Parameters:
	None
Return Value: 
	None
Local Variables:
	int m_savedHumanScore		- keeps human score loaded from the status file
	int m_savedComputerScore	- computer score loaded from the status file
	int m_savedRoundNr			- round number loaded from the status file
	int m_savedBoardSize		- board size loaded from the status file
	string m_savedHumanColor	- human color loaded from the status file
	string m_savedComputerColor - computer color loaded from the status file
	string m_statusFile			- name of the status file - hard coded to a default value
	string m_nextPlayer			- name of the next player
	bool m_isValidData;			- bool value to store true if loaded data is valid and false if loaded dat is not valid.
	string** m_savedBoard;		- pointer to pointer of string array. Used to load the position of the players pieces on the board.
								  Can be accessed as a double array
Algorithm:
Assistance Received: none
********************************************************************* */
BoardView::BoardView()
{
	m_statusFile = "SaveStatus.txt";
	m_savedHumanScore = 0;
	m_savedComputerScore = 0;
	m_savedRoundNr = 0;
	m_savedBoardSize = 0;
	m_savedHumanColor = "W";
	m_savedComputerColor = "B";
	m_isValidData = true;
	m_nextPlayer = "";
}

/* *********************************************************************
Function Name: BoardView
Purpose:
	Overloaded constructor for class BoardView. Used for the case we want to load status from a different file and not from the default one.
Parameters:
	all parameters passed by value
	string statusFile
Return Value:
	None
Local Variables:
int m_savedHumanScore		- keeps human score loaded from the status file
int m_savedComputerScore	- computer score loaded from the status file
int m_savedRoundNr			- round number loaded from the status file
int m_savedBoardSize		- board size loaded from the status file
string m_savedHumanColor	- human color loaded from the status file
string m_savedComputerColor - computer color loaded from the status file
string m_statusFile			- name of the status file - passed from the input parameter this time.
string m_nextPlayer			- name of the next player
bool m_isValidData;			- bool value to store true if loaded data is valid and false if loaded dat is not valid.
string** m_savedBoard;		- pointer to pointer of string array. Used to load the position of the players pieces on the board.
							  Can be accessed as a double array
Algorithm:
Assistance Received: none
********************************************************************* */

BoardView::BoardView(string statusFile)
{
	m_statusFile = statusFile;
	m_savedHumanScore = 0;
	m_savedComputerScore = 0;
	m_savedRoundNr = 0;
	m_savedBoardSize = 0;
	m_savedHumanColor = "W";
	m_savedComputerColor = "B";
	m_isValidData = true;
	m_nextPlayer = "";
}

/* *********************************************************************
Function Name: RetrieveSavedGameInfo
Purpose: 
	Read status of the game from a file and initializes the BoardView object that represents current status of the game.
Parameters:
	all parameters passed by value
	string fileName - name of the file containing the saved status
Return Value: 
	BoardView - an instanc eof the BoardView class representing the status of the game.
Local Variables:
	ifstream infile(fileName)	- file handler
	string fileLine				- string variable to store the content of a line in the file
	string str					- temporary string variable 
	bool foundComputer			- bool value helping in parsing the section of the file containing computer info
	bool foundHuman				- bool value helping in parsing the section of the file containing human info
	bool foundBoard				- bool value helping in parsing the section of the file containing board info
	bool setBoardSize			- bool value confirming board size have been set or not.
	vector<vector<string>> boardVector - vector of vector of strings representing the board's rows and columns as a strings. To be parsed later. 
	vector<string> lineVector			- vector of strings representing board's rows as strings. To be parsed later.
Algorithm:
	- read each line
	- identify each section and load the info for each section
	- parse the info from the board section and load it into a double array of strings.
	- set the next player
	-load the info regarding the score and color for each player.
	- return an isntance of BoardView class containing this info.
Assistance Received: none
********************************************************************* */
void BoardView::RetrieveSavedGameInfo(string fileName)
{
	ifstream infile(fileName);
	string fileLine,str;
	bool foundComputer, foundHuman, foundBoard, setBoardSize;
	vector<vector<string>> boardVector;
	vector<string> lineVector;
	foundComputer = false;
	foundHuman = false;
	foundBoard = false;
	setBoardSize = false;
	while (getline(infile, fileLine)) {
		string fileLineUpper = fileLine;
		transform(fileLineUpper.begin(), fileLineUpper.end(), fileLineUpper.begin(), ::toupper);
		if (fileLineUpper.find("ROUND:") != string::npos) {
			foundBoard = false;
			istringstream iss(fileLine);
			iss >> str >> m_savedRoundNr;
			cout << "Round number: " << m_savedRoundNr << endl;
			continue;
		}
		if (fileLineUpper.find("COMPUTER:") != string::npos) {
			foundHuman = false;
			foundComputer = true;
			foundBoard = false;
			continue;
		}
		if (fileLineUpper.find("HUMAN:") != string::npos) {
			foundHuman = true;
			foundComputer = false;
			foundBoard = false;
			continue;
		}
		if (fileLineUpper.find("BOARD:") != string::npos) {
			foundHuman = false;
			foundComputer = false;
			foundBoard = true;
			continue;
		}

		if (fileLineUpper.find("NEXT PLAYER:") != string::npos) {
			foundBoard = false;
			string nextPlayer;
			istringstream iss(fileLine);
			iss >> str >> str >> nextPlayer;
			cout << "Next player: " << nextPlayer << endl;
			transform(nextPlayer.begin(), nextPlayer.end(), nextPlayer.begin(), ::tolower);
			m_nextPlayer = nextPlayer;
			continue;
		}

		// We are processing the lines between Human: and the next section.
		// this includes score: and color:
		if (foundHuman == true) {
			if (fileLineUpper.find("SCORE:") != string::npos) {
				istringstream iss(fileLine);
				iss >> str >> m_savedHumanScore;
				cout << "Human score: " << m_savedHumanScore << endl;
			}
			if (fileLineUpper.find("COLOR:") != string::npos) {
				istringstream iss(fileLine);
				string retColor;
				iss >> str >> retColor;
				transform(retColor.begin(), retColor.end(), retColor.begin(), ::toupper);
				if (retColor != "WHITE" && retColor != "BLACK") {
					m_isValidData = false;
					m_savedHumanColor = "UNKNOWN";
				}
				else {
					if (retColor == "WHITE") {
						m_savedHumanColor = "W";
					}
					else {
						m_savedHumanColor = "B";
					}
				}
				cout << "Human color: " << retColor << endl;
			}
		}
		// We are processing the lines between Computer: and the next section.
		// this includes score: and color:
		if (foundComputer == true) {
			if (fileLineUpper.find("SCORE:") != string::npos) {
				istringstream iss(fileLine);
				iss >> str >> m_savedComputerScore;
				cout << "Computer score: " << m_savedComputerScore << endl;
			}
			if (fileLineUpper.find("COLOR:") != string::npos) {
				istringstream iss(fileLine);
				string retComputerColor;
				iss >> str >> retComputerColor;
				transform(retComputerColor.begin(), retComputerColor.end(), retComputerColor.begin(), ::toupper);
				if (retComputerColor != "WHITE" && retComputerColor != "BLACK") {
					m_isValidData = false;
					m_savedComputerColor = "UNKNOWN";
				}
				else {
					if (retComputerColor == "WHITE") {
						m_savedComputerColor = "W";
					}
					else {
						m_savedComputerColor = "B";
					}
				}
				cout << "Computer color: " << retComputerColor << endl;

			}
		}

		// Next section of code will retrieve the information between Board: and NextPlayer: lines.
		//It will load it into an array of strings that will be used to initialize the game later.
		if (foundBoard == true) {
			// initialize the line vector so we can append all the info for one line again
			lineVector.clear();			
			istringstream iss(fileLine);
			while (iss >> str) {
				lineVector.push_back(str);
			}
			if (setBoardSize == false) {
				m_savedBoardSize = lineVector.size();
				setBoardSize = true;
			}			
			boardVector.push_back(lineVector);
		}
	}
	infile.close();

	// Once the file is processed we would have all the board layout info in boardVector
	cout << "Board size: " << m_savedBoardSize << endl; 
	m_savedBoard = new string *[m_savedBoardSize];
	for (int i = 0; i < m_savedBoardSize; i++) {
		m_savedBoard[i] = new string[m_savedBoardSize];
	}
	for (int i = 0; i < boardVector.size(); ++i) {
		for (int j = 0; j < boardVector[i].size(); ++j) {
			m_savedBoard[i][j] = boardVector[i][j];
		}
	}
}

/* *********************************************************************
Function Name: SaveStatus
Purpose: Saves the status of the game into a file
Parameters:
	all parameters passed by value
	Board board				- to access info stored in board instance
	Tournament tournament	- to access info stored in tournament instance
	Round round				- to access info stored in round instance
	Human human				- to access info stored in human instance
	Computer computer		- to access info stored in computer instance
Return Value: 
	None
Local Variables:
	string strColor;
	string** boardSnapshot - double array of strings for storing board layout.
	int boardSize  - board size
	ofstream outfile - file handler
Algorithm:
	- open output file for writing
	- save the needed info to restart the game later in a standard format.
Assistance Received: none
********************************************************************* */
void BoardView::SaveStatus(Board board, Tournament tournament, Round round, Human human, Computer computer)
{
	// open a file in write mode.
	string strColor;
	string** boardSnapshot = board.GetBoard();
    int boardSize = board.GetBoardSize();
	ofstream outfile;
	// First truncate the file if it exists.
	outfile.open("SaveStatus.txt", ios::trunc);
	outfile << "Round: " << tournament.GetRound() << endl;
	outfile << endl;
	outfile << "Computer: " << endl;
	outfile << "   Score: " << tournament.GetComputerPoints() << endl;
	outfile << "   Color: " << ConvertColor(computer.GetColour()) << endl << endl;
	outfile << "Human: " << endl;
	outfile << "   Score: " << tournament.GetHumanPoints() << endl;
	outfile << "   Color: " << ConvertColor(human.GetColour()) << endl << endl;
	outfile << "Board: " << endl;
    // Output the table view 
	for (int j = 0; j < boardSize; j++) {
		outfile << "   ";
		for (int i = 0; i < boardSize; i++) {
			outfile << boardSnapshot[j][i];
			outfile << " ";
		}
		outfile << endl;
	}
	outfile << endl;
	outfile << "Next player: " << round.GetNextPlayer();
	outfile.close();
}

/* *********************************************************************
Function Name: ConvertColor
Purpose: Converts the char representing the color to the actual word
Parameters:
	all parameters passed by value
	char color - player's color
Return Value:
	string - actual word describing the color
Local Variables:
	None
Algorithm:
Assistance Received: none
********************************************************************* */
string BoardView::ConvertColor(char color) {
	if (color == 'B') {
		return "Black";
	}
	return "White";
}

/* *********************************************************************
Function Name: PrintBoard
Purpose: 
	Prints the layout of the board with the current location of player's pieces to standard output
Parameters:
	all parameters passed by value
	string** board	- array describing the board layout
	int boardSize	- size of the board
Return Value:
	None
Local Variables:
	int i - integer used to iterate through the array
	int j - integer used to iterate through the array
Algorithm:
	Loop through the array's rows and columns and print the output
Assistance Received: none
********************************************************************* */
void BoardView::PrintBoard(string** board, int boardSize)
{
	std::cout << "N" << endl;
	for (int j = 0; j < boardSize; j++) {
		std::cout << j + 1 << " ";
		for (int i = 0; i < boardSize; i++) {
			std::cout << board[j][i];
			std::cout << " ";
		}
		std::cout << endl;
	}
	std::cout << "S " << endl;
	std::cout << "W ";
	for (int i = 0; i < boardSize; i++) {
		std::cout << i + 1 << " ";
	}
	std::cout << "E " << endl;
}

/* *********************************************************************
Function Name: PrintBoard
Purpose:
	Prints the layout of the board with the value associated with each location
Parameters:
	string** board	- array describing the board layout and values associated with each square on the board (passed by reference)
	int boardSize	- size of the board (passed by value)
Return Value:
	None
Local Variables:
	int i - integer used to iterate through the array
	int j - integer used to iterate through the array
Algorithm:
	Loop through the array's rows and columns and print the output
Assistance Received: none
********************************************************************* */
void BoardView::PrintBoard(int** boardValues, int boardSize)
{
	for (int j = 0; j < boardSize; j++) {
		for (int i = 0; i < boardSize; i++) {
			std::cout << boardValues[j][i];
			std::cout << " ";
		}
		std::cout << endl;
	}
}

/* *********************************************************************
Function Name: GetHumanScore
Purpose:
	Returns the saved human score
Parameters:
	no parameters
Return Value:
	int m_savedHumanScore	- returns human score loaded from the status file
Assistance Received: none
********************************************************************* */
int const BoardView::GetHumanScore()
{
	return  m_savedHumanScore;
}

/* *********************************************************************
Function Name: GetComputerScore
Purpose:
	Returns the saved computer score
Parameters:
	no parameters
Return Value:
	int m_savedComputerScore	- returns computer score loaded from the status file
Assistance Received: none
********************************************************************* */
int const BoardView::GetComputerScore()
{
	return m_savedComputerScore;
}

/* *********************************************************************
Function Name: GetRound
Purpose:
	Returns the saved round number
Parameters:
	no parameters
Return Value:
	int m_savedRoundNr	- saved round number loaded from the status file
Assistance Received: none
********************************************************************* */
int const BoardView::GetRound()
{
	return m_savedRoundNr;
}

/* *********************************************************************
Function Name: GetBoardSize
Purpose:
	Returns the saved board size
Parameters:
	no parameters
Return Value:
	int m_savedBoardSize	- saved board size loaded from the status file
Assistance Received: none
********************************************************************* */
int const BoardView::GetBoardSize()
{
	return m_savedBoardSize;
}

/* *********************************************************************
Function Name: GetHumanColor
Purpose:
Returns the saved human color
Parameters:
no parameters
Return Value:
string m_savedHumanColor - saved human color loaded from the status file
Assistance Received: none
********************************************************************* */
string const BoardView::GetHumanColor()
{
	return m_savedHumanColor;
}

/* *********************************************************************
Function Name: GetComputerColor
Purpose:
	Returns the saved human color
Parameters:
	no parameters
Return Value:
	string m_savedComputerColor - saved computer color loaded from the status file
Assistance Received: none
********************************************************************* */
string const BoardView::GetComputerColor()
{
	return m_savedComputerColor;
}

/* *********************************************************************
Function Name: GetNextPlayer
Purpose:
	Returns the name of the next player
Parameters:
	no parameters
Return Value:
	string m_nextPlayer - name of the next player
Assistance Received: none
********************************************************************* */
string const BoardView::GetNextPlayer()
{
	return m_nextPlayer;
}

/* *********************************************************************
Function Name: GetBoard
Purpose:
Returns the saved board
Parameters:
no parameters
Return Value:
string m_savedBoard - the last saved board
Assistance Received: none
********************************************************************* */
string ** const BoardView::GetBoard()
{
	return m_savedBoard;
}

/* *********************************************************************
Function Name: ValidInfo
Purpose:
	Validates data loaded from status file.
Parameters:
	None
Return Value:
	bool - true if data passes validation rules, false otherwise.
Local Variables:
	m_isValidData			- private data member
	m_savedHumanColor		- private data member storing human player's color
	m_savedComputerColor	- private data member storing computer player's color
Algorithm:
	Verifies certain conditions based on data retrieved from status file 
Assistance Received: none
********************************************************************* */
pair<bool,string> BoardView::ValidInfo()
{
	if (m_isValidData == false) {
		return make_pair(false, "There were errors while retrieving saved data.");
	}
	if (m_savedHumanColor == m_savedComputerColor){
		return make_pair(false,"Computer color and human color cannot be the same.");
	}
	if (m_savedHumanColor != "B" && m_savedHumanColor != "W" && m_savedComputerColor != "B" && m_savedComputerColor != "W") {
		return make_pair(false, "Computer color and human color cann only be W or B. Retrieved: " + m_savedHumanColor + " and " + m_savedComputerColor);
	}
	return make_pair(true,"");
}

/* *********************************************************************
Function Name: roundMenu
Purpose:
	Displays menu customized for player type
Parameters:
	all parameters passed by value
	string - next player name
Return Value:
	string - chosen option from the menu
Local Variables:
	string option	- stores menu selection
	bool inputOk	- bool variables to allow input validation
Algorithm:
	Displayes an extra option if the player is human compared to the computer player
Assistance Received: none
********************************************************************* */
string BoardView::roundMenu(string nextPlayer)
{
	string option;
	bool inputOk = false;
	while (inputOk == false) {
		cout << endl << "Menu options: " << endl;
		cout << "Save the game [S/s]" << endl;
		cout << "Make a move [M/m]" << endl;
		// This option is displayed only if it is the human player's turn 
		if (nextPlayer == "human") {
			cout << "Ask for help [H/h]" << endl;
		}
		cout << "Quit [Q/q]" << endl;
		cout << "Chose option : ";
		getline(cin, option);
		for_each(option.begin(), option.end(), [](char& in) { in = ::toupper(in); });
		if (option != "S" && option != "M" && option != "H" && option != "Q") {
			continue;
		}
		break;
	}
	return option;
}

/* *********************************************************************
Function Name: PlayAnotherRound
Purpose:
	To display end of round stats and ask the players if they want to continue with another round	
Parameters:
	all parameters passed by value
	Human human				- instance of human class
	Computer computer		- instance of computer class
	Tournament tournament	- instance of tournament class
	Round round				- instance of round class
Return Value:
	bool - true if player wants to pay another round, false othehrwise
Local Variables:
	string strInput - stores player's response from standard input
Algorithm:
Assistance Received: none
********************************************************************* */
bool BoardView::PlayAnotherRound(Human human, Computer computer, Tournament tournament, Round round) {

	// Print end of round stats
	cout << "End of round statistics: " << endl;
	cout << "Human score: " << round.GetHumanPoints() << endl;
	cout << "Computer score: " << round.GetComputerPoints() << endl;
	cout << "The winner is: " << round.GetWinner() << endl << endl;
	cout << "Winner bonus: " << round.GetWinerBonus() << endl;
	cout << " - winner's bonus will be added to winner's total tournament points. " << endl;

	// Ask for another round
	char ask = ' ';
	while (ask != 'Y' &&  ask != 'N') {
		std::cout << "Do you want to play another round [Y - Yes/N - No]: ";
		cin >> ask;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		ask = toupper(ask);
	}
	if (ask != 'Y' ) {
		int humanTotal = tournament.GetHumanPoints();
		int computerTotal = tournament.GetComputerPoints();
		cout << "Tournament results: " << endl;
		cout << " Total tournament points human:    " << humanTotal << endl;
		cout << " Total tournament points computer: " << computerTotal << endl;
		if (humanTotal > computerTotal) {
			cout << "Tournament winner: human!" << endl;
		}
		else if (computerTotal > humanTotal) {
			cout << "Tournament winner: computer" << endl;
		}
		else {
			cout << " Tournament winner: tie" << endl;
		}
		return false;
	}
	return true;
}

/* *********************************************************************
Function Name: ComputerMoves
Purpose:
	To pick the best move for computer and execute it
Parameters:
	all parameters passed by value
	Board board				- instance of board class
	Human human				- instance of human class
	Computer computer		- instance of computer class
	Tournament tournament	- instance of tournament class
	Round round				- instance of round class
Return Value:
	tuple<Board, Human, Computer, Round, Tournament, bool> - tuple containing classes that have been passed by value and modified inside the function.
															 last variable of the tuple is a bool value indicating if we reached end of game 
																- true for end of game reached false otherwise

Local Variables:
	bool endOfGame					- true for end of game reached false otherwise
	pair<int, int> startPos, endPos - pairs of integers describing start and destination position
	string computerStringColor		- computer player's color
	string humanStringColor			- human player's color
Algorithm:
	- calculate the best possible move amongst all the pieces on the table
	- execute it and update relevant info
Assistance Received: none
********************************************************************* */
tuple<Board, Human, Computer, Round, Tournament, bool> BoardView::ComputerMoves(Board board, Human human, Computer computer, Round round, Tournament tournament) {
	// computer returns its move as a pair of pairs. First element in the pair is a pair that
	// identifies start position. Second element is a pair that identifies end position.
	// Togeher they define a move.

	bool endOfGame = false;
	pair<int, int> startPos, endPos;
	string computerStringColor = board.CharToString(computer.GetColour());
	string humanStringColor = board.CharToString(human.GetColour());
	Move computerMove = computer.CalculateMove(board, computer.GetColour(), human.GetColour());
	startPos = computerMove.GetStartPos();
	endPos = computerMove.GetEndPos();

	// Board class is executing the move based on the computer's request.
	board.MovePiece(startPos, endPos, computerStringColor, humanStringColor);
	std::cout << endl << "The computer moved the piece at (" << startPos.first + 1 << "," << startPos.second + 1 << ") " << computer.GetMoveDirection(startPos, endPos) << "." << endl;
	std::cout << computerMove.GetReasonForMove() << endl << endl;
	round.SetNextPlayer("human");
	if (computer.EndOfGame(board) == true) {
		round.CalculatePoints(board, human, computer);
		// The point difference between the 2 players is awarded to the winner and added to the tournament total.
		if (round.GetWinner() == "human") {
			tournament.SetHumanPoints(tournament.GetHumanPoints() + round.GetWinerBonus());
		} else {
			tournament.SetComputerPoints(tournament.GetComputerPoints() + round.GetWinerBonus());
		}
		/*
		tournament.SetComputerPoints(tournament.GetComputerPoints() + round.GetComputerPoints());
		tournament.SetHumanPoints(tournament.GetHumanPoints() + round.GetHumanPoints());
		*/
		std::cout << "All pieces reached opponent's places. Computer finished the game." << endl;
		endOfGame = true;
	}
	return std::make_tuple(board, human, computer, round, tournament, endOfGame);
}

/*
 Includes code related to human moves. This include I/O for asking what piece to move, as well as a sewuence of calls for methods
 // available in other classes.
*/
/* *********************************************************************
Function Name: HumanMoves
Purpose:
	To get info from standard input for human move and execute it.
Parameters:
	all parameters passed by value
	Board board				- instance of board class
	Human human				- instance of human class
	Computer computer		- instance of computer class
	Tournament tournament	- instance of tournament class
	Round round				- instance of round class
Return Value:
	tuple<Board, Human, Computer, Round, Tournament, bool>	- tuple containing classes that have been passed by value and modified inside the function.
															  last variable of the tuple is a bool value indicating if we reached end of game
															   - true for end of game reached false otherwise
Local Variables:
bool endOfGame					- true for end of game reached false otherwise
pair<int, int> startPos, endPos - pairs of integers describing start and destination position
string direction				- direction of the move.
pair<bool, string> retValid;	- true if input is valid false otherwise
Algorithm:
	- ask player to input chosen move
	- validate the input
	- execute it
Assistance Received: none
********************************************************************* */
tuple<Board, Human, Computer, Round, Tournament, bool> BoardView::HumanMoves(Board board, Human human, Computer computer, Round round, Tournament tournament) {
	std::cout << "Please enter your move in the format row col direction" << endl;
	std::cout << "For example 1 1 SE will move from (1,1) to (2,2)." << endl;
	// Get startPos and endPos as a series of 4 numbers (x1, x2, y1,y2) that identify 
	// source position X(x1,x2) and destination position Y(y1,y2)
	int startPos1, startPos2;
	string direction;
	pair<int, int> startPos;
	pair<int, int> endPos;
	pair<bool, string> retValid;
	Util myFunctions;
	bool endOfGame = false;
	while (true) {
		bool except = true;
		while (except == true) {
			try {
				cin >> startPos1 >> startPos2 >> direction;
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				except = false;
			}
			catch (...) {
				cout << " There were errors on data entered." << endl;
			}
		}
		// Convert direction to uppercase
		transform(direction.begin(), direction.end(), direction.begin(), ::toupper);
		// Validate start position, end position and direction
		if (myFunctions.ValidatePosition(startPos1 - 1, startPos2 - 1, board.GetBoardSize()) != true) {
			cout << "Start position is not a valid position. Please re-enter." << endl;
			continue;
		}
		if (myFunctions.ValidateDirectionValue(direction) != true) {
			cout << "Direction is not valid. Accepted values for direction are: SE/SW/NE/NW." << endl;
			cout << "Input is not case sensitive. Please re-enter." << endl;
			continue;
		}

		// Human calculates position from 1 while data is stored from 0.
		// Given the start position and the direction, this function will return the end position of the move.
		startPos = make_pair(startPos1 - 1, startPos2 - 1);
		endPos = human.ConvertInputToPosition(startPos1 - 1, startPos2 - 1, direction);
		retValid = human.ValidateInput(board, startPos, endPos, human.GetColour(), computer.GetColour());
		if (retValid.first == true) {
			break;
		}
		cout << retValid.second << " " << "Please try again!" << endl;
	}
	string humanStringColor = board.CharToString(human.GetColour());
	string computerStringColor = board.CharToString(computer.GetColour());
	// MovePiece method returns the value of the move which includes also the bonus for an eventual capture.
	board.MovePiece(startPos, endPos, humanStringColor, computerStringColor);
	round.SetNextPlayer("computer");
	if (human.EndOfGame(board) == true) {
		round.CalculatePoints(board, human, computer);
		// The point difference between the 2 players is awarded to the winner and added to the tournament total.
		if (round.GetWinner() == "human") {
			tournament.SetHumanPoints(tournament.GetHumanPoints() + round.GetWinerBonus());
		} else {
			tournament.SetComputerPoints(tournament.GetComputerPoints() + round.GetWinerBonus());
		}
		/*
		tournament.SetComputerPoints(tournament.GetComputerPoints() + round.GetComputerPoints());
		tournament.SetHumanPoints(tournament.GetHumanPoints() + round.GetHumanPoints());
		*/
		endOfGame = true;
	}
	return std::make_tuple(board, human, computer, round, tournament, endOfGame);
}

/* *********************************************************************
Function Name: ResumeGame
Purpose:
	Asks the user if this is a new game or one to be resumed from a saved file.
Parameters:
	none
Return Value:
	pair<char, string> - pair of char and string. 
						char variable indicates the answer Y or N
						string variable will contain the name of the file containing saved status if the chosen option is to resume the game
Local Variables:
	char response	- stores the answer from standard input
	string fileName	- stores file name if game is resumed
Algorithm:
Assistance Received: none
********************************************************************* */
pair<char, string> BoardView::ResumeGame() {
	char response = ' ';
	string fileName;
	while (response != 'Y' && response != 'N') {
		cout << "Do you want to resume game from a file containing game status? [Y/N]: ";
		cin >> response;
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		response = toupper(response);
	}
	if (response == 'Y') {
		bool fileExists = false;
		while (fileExists == false) {
			cout << "Enter the name of the file containing saved status: ";
			cin >> fileName;
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			fileExists = FileExists(fileName);
			if (fileExists == false) {
				cout << "File " + fileName + " does not exists." << endl;
			}
		}
	}
	return make_pair(response, fileName);
}

/* *********************************************************************
Function Name: FileExists
Purpose:
	Verifies if provided file exists
Parameters:
	all parameters passed by value
	const string fileName
Return Value:
	bool - true if file exists false otherwise
Local Variables:
	bool fileExists			- true if file exists false otherwise
	std::ifstream infile	- file handler
Algorithm:
Assistance Received: none
********************************************************************* */
bool BoardView::FileExists(const string fileName)
{
	bool fileExists = false;
	std::ifstream infile(fileName);
	fileExists = infile.good();
	infile.close();
	return fileExists;
}

/* *********************************************************************
Function Name: ChosePlayer
Purpose:
	To chose the color and the name of the player to start
Parameters:
	all parameters passed by value
	Human human			- instance of human class
	Computer computer	- instance of human class
Return Value:
	pair<pair<char, bool>, pair<char, bool>> - pair of pairs of char and bool variables
	 - first pair contains human info, second one contains computer info
		- char component of each pair contains the chosen color for that player
		- bool component of each pair is true if the player starts the game false otherwise
Local Variables:
	int hDiceValue	- sum of rolled dices values for human
	int cDiceValue	- sum of rolled dices values for computer
	char color		- player's color
	string strInput - stores info from standard input
	bool loadDice	- by default is false which means the function to generate dice numbers randomly will be called.
					  if set to true it will load dice values from file.
					  This is not a dynamic feature. The program needs to be compiled.
Algorithm:
	- depending on the value of loadDice it will simulate dice rolling via random generated numbers or load data from a file
	- player having the highest dice values will pick the desired color and start.
	- computer always picks black color
	- human can pick any color and consequently assigns the computer the remaining color.
Assistance Received: none
********************************************************************* */
pair<pair<char, bool>, pair<char, bool>> BoardView::ChosePlayer(Human human, Computer computer, bool loadDice)
{
	int hDiceValue;
	int cDiceValue;
	char color;
	string strInput;
	// Can be manually changed to load the dices from a file instead of rolling them
	// If loadDice is true, we are loading dice values from a file.

	if (loadDice == false) {
		hDiceValue = 0;
		cDiceValue = 0;
		while (hDiceValue == cDiceValue) {
			hDiceValue = human.RollDice();
			cDiceValue = computer.RollDice();
			if (hDiceValue == cDiceValue) {
				continue;
			}
		}
	}
	else {
		string diceValuesFile;
		bool foundFile = false;
		while (foundFile == false) {
			std::cout << "Enter the name of the file containing dice values: " << endl;
			std::getline(cin, diceValuesFile);
			std::ifstream diceFileHandler(diceValuesFile);
			if (diceFileHandler.good() != true) {
				cout << "File " + diceValuesFile + " does not exist. Retry." << endl;
				continue;
			}
			diceFileHandler.close();
			break;
		}
		pair<int, int> dicePair = GetDiceFromFile(diceValuesFile);
		hDiceValue = dicePair.first;
		cDiceValue = dicePair.second;
	}
	pair<char, bool> hPair;
	pair<char, bool> cPair;
	cout << "Human dice value: " << hDiceValue << endl;
	cout << "Computer dice value: " << cDiceValue << endl;
	if (hDiceValue > cDiceValue) {
		cout << "Human won at rolling the dices!" << endl;
		// After human choses color it will return a pair containing his chosen color and the computer assigned color. 
		pair<char, char> colorPair = HumanChosesColor();
		hPair = make_pair(colorPair.first, true);
		cPair = make_pair(colorPair.second, false);
	}
	if (hDiceValue < cDiceValue) {
		cout << "Computer won at rolling the dices!" << endl;
		std::cout << "Computer chose black color. " << endl;
		hPair = make_pair('W', false);
		cPair = make_pair('B', true);
	}
	return std::make_pair(hPair, cPair);
}

/* *********************************************************************
Function Name: GetDiceFromFile
Purpose:
	To load the dice values from file instead of simulating rolling the dice.
Parameters:
	all parameters passed by value
	string fileName - file containing the dice values in a certain format.
Return Value:
	pair<int, int> - pair of integers containing the total dice value for human and computer 
Local Variables:
	ifstream file	- file handler
	string str		- temp string variable
	int myVal		- variable to get the dice value from file  
	int totalHuman  - stores total for human
	int totalComputer - stores total for computer
	int lineCounter	  - stores line counter when reading from file
Algorithm:
	reads dice values from a file 
Assistance Received: none
********************************************************************* */
pair<int, int> BoardView::GetDiceFromFile(string fileName) {

	std::ifstream file(fileName);
	if (!file) {
		return std::make_pair(0, 0);
	}

	std::string str;
	int myVal;
	int totalHuman = 0;
	int totalComputer = 0;
	int lineCounter = 0;
	while (std::getline(file, str))
	{
		std::istringstream iss(str);
		int lineTotal = 0;
		for (std::string str; iss >> str; ) {
			std::istringstream ss(str);
			ss >> myVal;
			lineTotal = lineTotal + myVal;
		}
		if (lineCounter % 2 == 0) {
			totalHuman = totalHuman + lineTotal;
		}
		else {
			totalComputer = totalComputer + lineTotal;
		}
		lineCounter = lineCounter + 1;
	}
	file.close();
	return std::make_pair(totalHuman, totalComputer);
}

/*
This function is called only when human choses color. Computer choses black color automatically.
Returns a pair of 2 elements
- first element: human color
- second element: computer color
*/
/* *********************************************************************
Function Name: HumanChosesColor
Purpose:
	Asks human to pick the color to play
Parameters:
	None
Return Value:
	pair<char, char> - pair of chars containing the human and computer color
Local Variables:
	char color		- converted standard input to string
	string strInput	- stores color from standard input 
Algorithm:
	- asks human to chose color
	- assigns remaining color to the computer
Assistance Received: none
********************************************************************* */
pair<char, char> BoardView::HumanChosesColor() {
	char color = ' ';
	string strInput;
	while (color != 'W' && color != 'B') {
		std::cout << "Human choses color (W - White/B - Black): ";
		std::getline(cin, strInput);
		color = toupper(strInput[0]);
	}
	if (color == 'B') {
		return make_pair('B', 'W');
	}
	return make_pair('W', 'B');
}