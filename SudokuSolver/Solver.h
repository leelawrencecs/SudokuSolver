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
	void displayAllPossibleValuesFromCertainRow(int row);
	void insertValue();
	int insertIfThereIsOnlyOnePossibleValue(int row, int col);
	void rowIsolator();
	void colIsolator();
	void boxIsolator();
	int getNumberOfPossibleValues(int row, int col);
	bool doTheseHaveSamePossibleValues(int row, int col, int row2, int col2);
	void getNumberOfSolvedValues();
	void setIfOnlyPossibleValueForBox();
	void setIfOnlyPossibleValueForRow();
	void setIfOnlyPossibleValueForCol();
	void clearPossibleValuesIfHasValue();
	void totalNumbmerOfPossibleValues();
	void endAllBeAllOne();
	bool dontExistOnBox(int i, int j, int n);


};