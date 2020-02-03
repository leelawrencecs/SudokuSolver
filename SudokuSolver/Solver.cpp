#include "Solver.h"

#include <iostream>
#include <fstream>
#include <unordered_set>

using namespace std;

void Solver::basicSolve()
{
	unordered_set<int> hashTable;

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (board[row][col] == 0)
			{
				
				for (int i = 1; i <= 9; i++)
				{
					if (doesRowHaveNumber(row, i)) hashTable.insert(i);
					else if (doesColumnHaveNumber(col, i)) hashTable.insert(i);
					else if (doesBoxHaveNumber(row, col, i)) hashTable.insert(i);
				}

				if (hashTable.size() == 8)
				{
					for (int i = 1; i <= 9; i++)
					{
						if (hashTable.count(i) == 0)
						{
							cout << "made it here" << endl;
							cout << i << endl;
							board[row][col] = i;
							break;
						}
					}
				}
				hashTable.clear();
			}
		}
	}
}

//i represents row, j represents col
int Solver::emptySlotsInBox(int i, int j)
{
	int emptySlotsNum = 0;

	if (i < 3)
	{
		if (j < 3)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					if (board[i][j] == 0) emptySlotsNum++;
				}
			}
		}
		else if (j < 6)
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 3; j < 6; j++)
				{
					if (board[i][j] == 0) emptySlotsNum++;
				}
			}
		}
		else
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 6; j < 9; j++)
				{
					if (board[i][j] == 0) emptySlotsNum++;
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
					if (board[i][j] == 0) emptySlotsNum++;
				}
			}
		}
		else if (j < 6)
		{
			for (int i = 3; i < 6; i++)
			{
				for (int j = 3; j < 6; j++)
				{
					if (board[i][j] == 0) emptySlotsNum++;
				}
			}
		}
		else
		{
			for (int i = 3; i < 6; i++)
			{
				for (int j = 6; j < 9; j++)
				{
					if (board[i][j] == 0) emptySlotsNum++;
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
					if (board[i][j] == 0) emptySlotsNum++;
				}
			}
		}
		else if (j < 6)
		{
			for (int i = 6; i < 9; i++)
			{
				for (int j = 3; j < 6; j++)
				{
					if (board[i][j] == 0) emptySlotsNum++;
				}
			}
		}
		else
		{
			for (int i = 6; i < 9; i++)
			{
				for (int j = 6; j < 9; j++)
				{
					if (board[i][j] == 0) emptySlotsNum++;
				}
			}
		}
	}

	return emptySlotsNum;
}

int Solver::emptySlotsInRow(int row)
{
	int emptySlotsNum = 0;

	for (int col = 0; col < 9; col++)
	{
		if (board[row][col] == 0)
		{
			emptySlotsNum++;
		}
	}

	return emptySlotsNum;
}

int Solver::emptySlotsInColumn(int col)
{
	int emptySlotsNum = 0;

	for (int row = 0; row < 9; row++)
	{
		if (board[row][col] == 0)
		{
			emptySlotsNum++;
		}
	}

	return emptySlotsNum;
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
	cout << endl;
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
	//cout << "constructor" << endl;
}
