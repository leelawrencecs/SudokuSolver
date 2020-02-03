#include "Solver.h"

#include <iostream>
#include <fstream>

using namespace std;

void Solver::basicSolve()
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (board[row][col] == 0)
			{

			}
		}
	}
}

bool Solver::doesColumnHaveNumber(int col, int num)
{
	for (int row = 0; row < 9; row++)
	{
		if (board[row][col] == num) return true;
	}

	return false;
}

bool Solver::doesRowHaveNumber(int row, int num)
{
	for (int col = 0; col < 9; col++)
	{
		if (board[row][col] == num) return true;
	}

	return false;
}

//the following parameters are in this order: row, col, number
bool Solver::doesBoxHaveNumber(int i, int j, int num)
{
	//the following code is ugly and repetitive but it works efficiently. may change it later

	if (i < 3)
	{
		if (j < 3)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (board[i][j] == num) return true;
				}
			}
		}
		else if (j < 6)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 3; j < 6; j++)
				{
					if (board[i][j] == num) return true;
				}
			}
		}
		else
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 6; j < 9; j++)
				{
					if (board[i][j] == num) return true;
				}
			}
		}
	}
	else if (i < 6)
	{
		if (j < 3)
		{
			for (int i = 3; i < 6; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (board[i][j] == num) return true;
				}
			}
		}
		else if (j < 6)
		{
			for (int i = 3; i < 6; i++)
			{
				for (int j = 3; j < 6; j++)
				{
					if (board[i][j] == num) return true;
				}
			}
		}
		else
		{
			for (int i = 3; i < 6; i++)
			{
				for (int j = 6; j < 9; j++)
				{
					if (board[i][j] == num) return true;
				}
			}
		}
	}
	else
	{
		if (j < 3)
		{
			for (int i = 6; i < 9; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (board[i][j] == num) return true;
				}
			}
		}
		else if (j < 6)
		{
			for (int i = 6; i < 9; i++)
			{
				for (int j = 3; j < 6; j++)
				{
					if (board[i][j] == num) return true;
				}
			}
		}
		else
		{
			for (int i = 6; i < 9; i++)
			{
				for (int j = 6; j < 9; j++)
				{
					if (board[i][j] == num) return true;
				}
			}
		}
	}

	return false;
}

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
