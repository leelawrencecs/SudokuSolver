#include "Solver.h"

#include <iostream>
#include <fstream>

using namespace std;

void Solver::displayBoard()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

void Solver::addBoard(string file)
{
	ifstream open(file);
	int x;

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			open >> x;
			board[i][j] = x;
		}
	}

}

Solver::Solver()
{
	cout << "constructor" << endl;
}
