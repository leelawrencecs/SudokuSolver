#pragma once

#include <iostream>

using namespace std;

class Solver
{
private:
	int board[9][9];
	bool allPossibleNumbers[9][9][9];
	
public:

	void similarMustValues();
	void solve();
	int isThereOnlyOnePossibleNumber(int row, int col);
	bool setNumberIfItOnlyHasOnePossibleNumber();
	void checkAllPossibleNumbersInGivenSpot(int row, int col);
	bool doesThisNumberExistInBox(int row, int col, int num);
	bool doesThisNumberExistInColumn(int col, int num);
	bool doesThisNumberExistInRow(int row, int num);
	void updateAllPossibleNumbers();
	void setAllPossibleNumbersToTrue();
	void displayBoard();
	void addBoard(string);
	Solver();
};








/*

#pragma once

#include <iostream>

using namespace std;

class Solver
{
private:
	int board[9][9];
	bool anyChanges;

public:
	Solver();
	bool isItInvalidWithCertainty();
	bool isItSolved();
	void basicSolve(); //checks all possible numbers a location can have. if it's only 1, then it will use that
	void basicSolveHelper();
	int emptySlotsInBox(int, int);
	int emptySlotsInRow(int);
	int emptySlotsInColumn(int);
	//bool canItBeThisNumber(int, int, int);
	bool doesBoxHaveNumber(int, int, int);
	bool doesRowHaveNumber(int, int);
	bool doesColumnHaveNumber(int, int);
	void addBoard(string);
	void displayBoard();

};

*/