#pragma once

#include <iostream>

using namespace std;

class Solver
{
private:
	int board[9][9];


public:
	Solver();
	void basicSolve(); //checks all possible numbers a location can have. if it's only 1, then it will use that
	bool canItBeThisNumber(int, int, int);
	bool doesBoxHaveNumber(int, int, int); //working
	bool doesRowHaveNumber(int, int); //working
	bool doesColumnHaveNumber(int, int); //working
	void addBoard(string); //working
	void displayBoard(); //working


};

