//test
#include "Solver.h"

#include <iostream>
#include <fstream>
#include <unordered_set>

using namespace std;

void Solver::solve()
{
	do
	{
		updateAllPossibleNumbers();

	} while (setNumberIfItOnlyHasOnePossibleNumber());
}

int Solver::isThereOnlyOnePossibleNumber(int row, int col)
{
	bool counter = false;
	int value;

	for (int i = 0; i < 9; i++)
	{
		if (allPossibleNumbers[row][col][i])
		{
			if (counter) return 0;

			counter = true;

			value = i + 1;
		}
	}

	return value;
}

bool Solver::setNumberIfItOnlyHasOnePossibleNumber()
{
	bool wasThereAChangeInAnyNumbers = false;

	int x;

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (board[row][col] == 0)
			{
				board[row][col] = isThereOnlyOnePossibleNumber(row, col);
				
				if (board[row][col] != 0)
				{
					wasThereAChangeInAnyNumbers = true;
				}
			}
		}
	}

	return wasThereAChangeInAnyNumbers;
}

void Solver::checkAllPossibleNumbersInGivenSpot(int row, int col)
{
	cout << "All possible values in row: " << row << ", col: " << col << " are ";

	for (int i = 0; i < 9; i++)
	{
		if (allPossibleNumbers[row][col][i])
		{
			cout << i + 1 << " ";
		}
	}

	cout << endl;
}

bool Solver::doesThisNumberExistInBox(int row, int col, int num)
{
	if (row < 3)
	{
		if (col < 3)
		{
			for (int row = 0; row < 3; row++)
			{
				for (int col = 0; col < 3; col++)
				{
					if (board[row][col] == num)
					{
						return true;
					}
				}
			}
		}
		else if (col < 6)
		{
			for (int row = 0; row < 3; row++)
			{
				for (int col = 3; col < 6; col++)
				{
					if (board[row][col] == num)
					{
						return true;
					}
				}
			}
		}
		else
		{
			for (int row = 0; row < 3; row++)
			{
				for (int col = 6; col < 9; col++)
				{
					if (board[row][col] == num)
					{
						return true;
					}
				}
			}
		}
	}
	else if (row < 6)
	{
		if (col < 3)
		{
			for (int row = 3; row < 6; row++)
			{
				for (int col = 0; col < 3; col++)
				{
					if (board[row][col] == num)
					{
						return true;
					}
				}
			}
		}
		else if (col < 6)
		{
			for (int row = 3; row < 6; row++)
			{
				for (int col = 3; col < 6; col++)
				{
					if (board[row][col] == num)
					{
						return true;
					}
				}
			}
		}
		else
		{
			for (int row = 3; row < 6; row++)
			{
				for (int col = 6; col < 9; col++)
				{
					if (board[row][col] == num)
					{
						return true;
					}
				}
			}
		}
	}
	else
	{
		if (col < 3)
		{
			for (int row = 6; row < 9; row++)
			{
				for (int col = 0; col < 3; col++)
				{
					if (board[row][col] == num)
					{
						return true;
					}
				}
			}
		}
		else if (col < 6)
		{
			for (int row = 6; row < 9; row++)
			{
				for (int col = 3; col < 6; col++)
				{
					if (board[row][col] == num)
					{
						return true;
					}
				}
			}
		}
		else
		{
			for (int row = 6; row < 9; row++)
			{
				for (int col = 6; col < 9; col++)
				{
					if (board[row][col] == num)
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool Solver::doesThisNumberExistInColumn(int col, int num)
{
	for (int row = 0; row < 9; row++)
	{
		if (board[row][col] == num)
		{
			return true;
		}
	}

	return false;
}

bool Solver::doesThisNumberExistInRow(int row, int num)
{
	for (int col = 0; col < 9; col++)
	{
		if (board[row][col] == num)
		{
			return true;
		}
	}

	return false;
}

void Solver::updateAllPossibleNumbers()
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (board[row][col] == 0)
			{
				for (int i = 1; i <= 9; i++)
				{
					if (doesThisNumberExistInRow(row, i) || doesThisNumberExistInColumn(col, i) || doesThisNumberExistInBox(row, col, i))
					{
						allPossibleNumbers[row][col][i - 1] = false;
						//cout << "Row: " << row << " Col: " << col << " value " << i - 1 << " set to false." << endl;
					}
				}
			}
		}
	}
}

void Solver::setAllPossibleNumbersToTrue()
{

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			for (int boolValue = 0; boolValue < 9; boolValue++)
			{
				allPossibleNumbers[row][col][boolValue] = 1;
			}
		}
	}
}

//displays the puzzle with current values from "board"
void Solver::displayBoard()
{
	cout << "Displaying Board..." << endl;

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			cout << board[row][col];

			if (col == 2 || col == 5)
			{
				//used to divide between every 3 columns
				cout << "|";
			}
			else
			{
				cout << " ";
			}
		}

		cout << endl;

		if (row == 2 || row == 5)
		{
			//used to divide between every 3 rows
			cout << "-----+-----+-----" << endl;
		}
	}

	cout << endl;

}

//adds sudoku text file to the "board" array
void Solver::addBoard(string file)
{
	cout << "Adding to board" << endl;

	//"open" streams through the text file for values
	ifstream open(file);

	//"x" stores values from open and inserts into "board" array
	int x;

	//initializes the "board" array with values from the text file
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
	cout << "Constructor has been accessed accessed" << endl;
	setAllPossibleNumbersToTrue();


}





/*

#include "Solver.h"

#include <iostream>
#include <fstream>
#include <unordered_set>

using namespace std;

bool Solver::isItInvalidWithCertainty()
{
	unordered_set<int> hashTable;

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (board[row][col] != 0)
			{

			}
		}
	}

	return false;
}

bool Solver::isItSolved()
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (board[row][col] == 0) return false;
		}
	}
	return true;
}

void Solver::basicSolve()
{
	do
	{
		anyChanges = false;
		basicSolveHelper();
	} while (anyChanges);
}

void Solver::basicSolveHelper()
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
							board[row][col] = i;
							cout << i << endl;
							cout << hashTable.size() << endl;
							anyChanges = true;
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
			cout << board[i][j];
			if (j == 2 || j == 5)
			{
				cout << "|";;
			}
			else
			{
				cout << " ";
			}
		}
		//cout << endl;
		if (i == 2 || i == 5)
		{
			cout << endl;
			cout << "-----+-----+-----" << endl;
		}
		else
		{
			cout << endl;
		}
		

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
*/