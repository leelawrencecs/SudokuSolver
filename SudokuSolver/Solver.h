#pragma once

#include <iostream>

using namespace std;






class Solver
{
private:
	int board[9][9];
	bool allPossibleValues[9][9][9];
	bool hasThereBeenAChangeInAnything;

public:
	Solver();
	void addBoard(string);
	void setAllPossibleValuesToTrue();
	void displayBoard();
	void solverLoop();
	void updateAllPossibleValues();
	bool doesThisNumberExistInRow(int row, int num);
	bool doesThisNumberExistInCol(int col, int num);
	bool doesThisNumberExistInBox(int row, int col, int num);
	void displayAllPossibleValuesFromAllValues();
	void insertValue();
	int insertIfThereIsOnlyOnePossibleValue(int row, int col);
	void rowIsolator();
	void colIsolator();
	void boxIsolator();
	int getNumberOfPossibleValues(int row, int col);
	bool doTheseHaveSamePossibleValues(int row, int col, int row2, int col2);
	void getNumberOfSolvedValues();


};






















































/*
class Solver
{
private:
	bool hasThereBeenAChangeInAnything;
	bool allPossibleNumbers[9][9][9];
	int board[9][9];
	int first;
	int second;

public:
	Solver();
	void addBoard(string);
	void displayBoard();
	void setAllPossibleNumbersToTrue();
	void solveThePuzzleLoop();
	void updateAllPossibleNumbers();
	bool doesThisNumberExistInRow(int row, int num);
	bool doesThisNumberExistInColumn(int col, int num);
	bool doesThisNumberExistInBox(int row, int col, int num);
	void setNumberIfItOnlyHasOnePossibleNumber();
	int isThereOnlyOnePossibleNumber(int row, int col);
	void printOutAllPossibleNumbers(int row, int col);
	void killAllPossibleValues(int row, int col);
	void rowIsolator();
	int getNumberOfPossibleValues(int row, int col);
	bool doTheseHaveTheSamePossibleValues(int row, int col, int row2, int col2);
	void howManyTotalPossibleValuesInWholePuzzle();
	void colIsolator();
	void boxIsolator();
	void killAllPossibleValuesFromNonZero();


};
*/


/*
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

*/






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