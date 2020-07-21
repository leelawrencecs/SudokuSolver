
#include "Solver.h"
#include <iostream>
#include <fstream>
#include <unordered_set>

using namespace std;

//loops algorithms for solving puzzle
void Solver::solverLoop()
{
	do
	{
		hasThereBeenAChangeInAnything = false;
		updateAllPossibleValues();
		insertValue();
		rowIsolator();
		colIsolator();
		boxIsolator();

	} while (hasThereBeenAChangeInAnything);
}

//prints out number of solved values. used for testing purposes only
void Solver::getNumberOfSolvedValues()
{
	int counter = 0;

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (board[row][col] != 0)
			{
				counter++;
			}
		}
	}

	cout << "There are " << counter << " solved values" << endl;
}

//checks if the possible values for two boxes are the same
bool Solver::doTheseHaveSamePossibleValues(int row, int col, int row2, int col2)
{
	for (int possibleValues = 0; possibleValues < 9; possibleValues++)
	{
		if (allPossibleValues[row][col][possibleValues] != allPossibleValues[row2][col2][possibleValues])
		{
			return false;
		}
	}

	return true;
}

//returns the amount of possible values that a box can have
int Solver::getNumberOfPossibleValues(int row, int col)
{
	int counter = 0;

	for (int possibleValues = 0; possibleValues < 9; possibleValues++)
	{
		if (allPossibleValues[row][col][possibleValues] == true)
		{
			counter++;
		}
	}

	return counter;
}

//isolates possible values in particular 3x3 box where we know that the possible numbers are guaranteed in a group of size N with N possible numbers
void Solver::boxIsolator()
{
	int counter;
	int rowBox, colBox;

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			counter = getNumberOfPossibleValues(row, col);

			if (row < 3) rowBox = 0;
			else if (row < 6) rowBox = 3;
			else rowBox = 6;

			if (col < 3) colBox = 0;
			else if (col < 6) colBox = 3;
			else colBox = 6;

			for (int i = rowBox; i < rowBox + 3; i++)
			{
				for (int j = colBox; j < colBox + 3; j++)
				{
					if (doTheseHaveSamePossibleValues(row, col, i, j))
					{
						counter--;
					}


				}
			}

			if (counter == 0)
			{
				for (int i = rowBox; i < rowBox + 3; i++)
				{
					for (int j = colBox; j < colBox + 3; j++)
					{
						if (doTheseHaveSamePossibleValues(row, col, i, j) == false)
						{
							for (int possibleValues = 0; possibleValues < 9; possibleValues++)
							{
								if (allPossibleValues[row][col][possibleValues] == true)
								{
									if (allPossibleValues[i][j][possibleValues] == true)
									{
										hasThereBeenAChangeInAnything = true;
									}

									allPossibleValues[i][j][possibleValues] = false;
								}
							}



						}


					}
				}
			}




		}
	}

}

//isolates possible values in particular column where we know that the possible numbers are guaranteed in a group of size N with N possible numbers
void Solver::colIsolator()
{
	int counter;

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			counter = getNumberOfPossibleValues(row, col);

			for (int row2 = 0; row2 < 9; row2++)
			{
				if (doTheseHaveSamePossibleValues(row, col, row2, col))
				{
					counter--;
				}
			}

			if (counter == 0)
			{
				for (int row2 = 0; row2 < 9; row2++)
				{
					if (doTheseHaveSamePossibleValues(row, col, row2, col) == false)
					{
						for (int possibleValues = 0; possibleValues < 9; possibleValues++)
						{
							if (allPossibleValues[row][col][possibleValues] == true)
							{
								if (allPossibleValues[row2][col][possibleValues] == true)
								{
									hasThereBeenAChangeInAnything = true;
								}

								allPossibleValues[row2][col][possibleValues] = false;
							}
						}



					}
				}
			}


		}
	}
}

//isolates possible values in particular row where we know that the possible numbers are guaranteed in a group of size N with N possible numbers
void Solver::rowIsolator()
{
	int counter;

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			counter = getNumberOfPossibleValues(row, col);

			for (int col2 = 0; col2 < 9; col2++)
			{
				if (doTheseHaveSamePossibleValues(row, col, row, col2))
				{
					counter--;
				}
			}

			if (counter == 0)
			{
				for (int col2 = 0; col2 < 9; col2++)
				{
					if (doTheseHaveSamePossibleValues(row, col, row, col2) == false)
					{
						for (int possibleValues = 0; possibleValues < 9; possibleValues++)
						{
							if (allPossibleValues[row][col][possibleValues] == true)
							{
								if (allPossibleValues[row][col2][possibleValues] == true)
								{
									hasThereBeenAChangeInAnything = true;
								}

								allPossibleValues[row][col2][possibleValues] = false;
							}
						}



					}
				}
			}


		}
	}
}

//helper function for insertValue()
int Solver::insertIfThereIsOnlyOnePossibleValue(int row, int col)
{
	int valueSeen = 0;

	for (int possibleValues = 0; possibleValues < 9; possibleValues++)
	{
		if (allPossibleValues[row][col][possibleValues] == true)
		{
			if (valueSeen == 0) valueSeen = possibleValues + 1;
			else return 0;
		}
	}

	hasThereBeenAChangeInAnything = true;
	return valueSeen;
}

//inserts number onto the board if there is only one possible number that a box can have
void Solver::insertValue()
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (board[row][col] == 0)
			{
				board[row][col] = insertIfThereIsOnlyOnePossibleValue(row, col);
			}
		}
	}
}

//displays every possible value for every box in the puzzle. Used for testing purposes only
void Solver::displayAllPossibleValuesFromAllValues()
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			cout << "For row:" << row << " col:" << col << ", all possible values are: ";

			for (int possibleValues = 0; possibleValues < 9; possibleValues++)
			{
				if (allPossibleValues[row][col][possibleValues] == true)
				{
					cout << possibleValues + 1 << " ";
				}
			}

			cout << endl;
		}
	}
}

//checks to see if a certain number exists within the row
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

//checks to see if a certain number exists within the column
bool Solver::doesThisNumberExistInCol(int col, int num)
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

//checks to see if a certain number exists within the 3v3 box
bool Solver::doesThisNumberExistInBox(int row, int col, int num)
{
	int rowBox, colBox;

	if (row < 3) rowBox = 0;
	else if (row < 6) rowBox = 3;
	else rowBox = 6;

	if (col < 3) colBox = 0;
	else if (col < 6) colBox = 3;
	else colBox = 6;

	for (int i = rowBox; i < rowBox + 3; i++)
	{
		for (int j = colBox; j < colBox + 3; j++)
		{
			if (board[i][j] == num)
			{
				return true;
			}
		}
	}

	return false;
}

//makes sure that every possible value that a box can have is valid
void Solver::updateAllPossibleValues()
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			//makes sure that any box that has a value will not have any possible values
			if (board[row][col] != 0)
			{
				for (int possibleValues = 0; possibleValues < 9; possibleValues++)
				{
					if (allPossibleValues[row][col][possibleValues] == true)
					{
						hasThereBeenAChangeInAnything = true;
					}

					allPossibleValues[row][col][possibleValues] = false;
				}
			}
			else
			{
				for (int i = 0; i < 9; i++)
				{
					//make sure that for every possible value, there isn't another value in the same row, column, or 3x3 box
					if (doesThisNumberExistInRow(row, i + 1) || doesThisNumberExistInCol(col, i + 1) || doesThisNumberExistInBox(row, col, i + 1))
					{
						if (allPossibleValues[row][col][i] == true)
						{
							hasThereBeenAChangeInAnything = true;
						}

						allPossibleValues[row][col][i] = false;
					}
				}
			}
		}
	}
}

//sets every boxes possible value as a potential value
void Solver::setAllPossibleValuesToTrue()
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			for (int possibleValues = 0; possibleValues < 9; possibleValues++)
			{
				allPossibleValues[row][col][possibleValues] = true;
			}
		}
	}
}

//prints out the board onto the console
void Solver::displayBoard()
{

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

//adds text file of the puzzle into memory 
void Solver::addBoard(string file)
{
	ifstream open(file);

	int value;

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			open >> value;
			board[row][col] = value;
		}
	}

}

//initially sets up program to run the solver
Solver::Solver()
{
	hasThereBeenAChangeInAnything = true;
	setAllPossibleValuesToTrue();
}




