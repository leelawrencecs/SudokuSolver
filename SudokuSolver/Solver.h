#pragma once

#include <iostream>

using namespace std;

class Solver
{
private:
	int board[9][9];


public:
	Solver();
	void addBoard(string file);
	void displayBoard();


};

