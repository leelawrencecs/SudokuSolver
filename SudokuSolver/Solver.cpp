
#include "Solver.h"
#include <iostream>
#include <fstream>
#include <unordered_set>

using namespace std;

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

void Solver::updateAllPossibleValues()
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
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

Solver::Solver()
{
	hasThereBeenAChangeInAnything = true;
	setAllPossibleValuesToTrue();
}















/*
void Solver::solveThePuzzleLoop()
{
	do
	{
		hasThereBeenAChangeInAnything = false;
		updateAllPossibleNumbers();
		setNumberIfItOnlyHasOnePossibleNumber();
		//rowIsolator();
		//colIsolator();
		boxIsolator();
		//killAllPossibleValuesFromNonZero();



	} while (hasThereBeenAChangeInAnything);

}

void Solver::boxIsolator()
{
	int counter;
	int theRow;
	int theCol;

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (board[row][col] == 0)
			{
				counter = getNumberOfPossibleValues(row, col);

				if (row < 3) theRow = 0;
				else if (row < 6) theRow = 3;
				else { theRow = 6; }

				if (col < 3) theCol = 0;
				else if (col < 6) theCol = 3;
				else { theCol = 6; }

				for (int i = theRow; i < theRow + 3; i++)
				{
					for (int j = theCol; j < theCol + 3; j++)
					{
						if (doTheseHaveTheSamePossibleValues(row, col, i, j) == true)
						{
							counter--;
						}
					}
				}

				if (counter == 0)
				{

					for (int i = theRow; i < theRow + 3; i++)
					{
						for (int j = theCol; j < theCol + 3; j++)
						{


							if (doTheseHaveTheSamePossibleValues(row, col, i, j) == false)
							{
								for (int k = 0; k < 9; k++)
								{
									if (allPossibleNumbers[row][col][k] == true)
									{
										if (allPossibleNumbers[i][j][k] == true)
										{
											hasThereBeenAChangeInAnything = true;
											//printOutAllPossibleNumbers(i, j);
										}

										allPossibleNumbers[i][j][k] == false;
									}
								}
							}
						}
					}
				}


			}
		}
	}

}

void Solver::howManyTotalPossibleValuesInWholePuzzle()
{
	int counter = 0;

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			for (int i = 0; i < 9; i++)
			{
				if (allPossibleNumbers[row][col][i] == true)
				{
					counter++;
				}
			}
		}
	}

	cout << "Total Possible Numbers: " << counter << endl;
}

void Solver::rowIsolator()
{
	int counter;

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (board[row][col] == 0)
			{
				counter = getNumberOfPossibleValues(row, col);

				for (int i = col; i < 9; i++)
				{
					if (doTheseHaveTheSamePossibleValues(row, col, row, i))
					{
						counter--;
					}
				}
				if (counter == 0)
				{
					for (int j = 0; j < 9; j++)
					{
						if (doTheseHaveTheSamePossibleValues(row, col, row, j) == false)
						{
							for (int k = 0; k < 9; k++)
							{
								if (allPossibleNumbers[row][col][k] == true)
								{
									if (allPossibleNumbers[row][j][k] == true)
									{
										hasThereBeenAChangeInAnything = true;
									}

									allPossibleNumbers[row][j][k] = false;
								}
							}
						}
					}
				}
			}

		}
	}


}

void Solver::colIsolator()
{
	int counter;

	for (int col = 0; col < 9; col++)
	{
		for (int row = 0; row < 9; row++)
		{
			if (board[row][col] == 0)
			{
				counter = getNumberOfPossibleValues(row, col);

				for (int i = row; i < 9; i++)
				{
					if (doTheseHaveTheSamePossibleValues(row, col, i, col))
					{
						counter--;
					}
				}
				if (counter == 0)
				{
					for (int j = 0; j < 9; j++)
					{
						if (doTheseHaveTheSamePossibleValues(row, col, j, col) == false)
						{
							for (int k = 0; k < 9; k++)
							{
								if (allPossibleNumbers[row][col][k] == true)
								{
									if (allPossibleNumbers[j][col][k] == true)
									{
										hasThereBeenAChangeInAnything = true;
									}

									allPossibleNumbers[j][col][k] = false;
								}
							}
						}
					}
				}
			}

		}
	}


}

bool Solver::doTheseHaveTheSamePossibleValues(int row, int col, int row2, int col2)
{
	for (int i = 0; i < 9; i++)
	{
		if (allPossibleNumbers[row][col][i] != allPossibleNumbers[row2][col2][i])
		{
			return false;
		}
	}

	return true;
}

int Solver::getNumberOfPossibleValues(int row, int col)
{
	int counter = 0;

	for (int i = 0; i < 9; i++)
	{
		if (allPossibleNumbers[row][col][i] == true)
		{
			counter++;
		}
	}

	return counter;
}

void Solver::killAllPossibleValuesFromNonZero()
{
	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (board[row][col] != 0)
			{
				for (int i = 0; i < 9; i++)
				{
					allPossibleNumbers[row][col][i] = false;
				}
			}
		}
	}

}

void Solver::killAllPossibleValues(int row, int col)
{
	for (int i = 0; i < 9; i++)
	{
		allPossibleNumbers[row][col][i] = false;
	}
}

//the following function will display all possible values for a certain box and is used for testing purposes only
void Solver::printOutAllPossibleNumbers(int row, int col)
{

	cout << "All possible numbers for row " << row << " column " << col << " are: ";

	for (int i = 0; i < 9; i++)
	{
		if (allPossibleNumbers[row][col][i] == 1)
		{
			cout << i + 1 << " ";
		}
	}
	cout << endl;
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

	for (int i = 0; i < 9; i++)
	{
		allPossibleNumbers[row][col][i] = false;
	}

	hasThereBeenAChangeInAnything = true;
	killAllPossibleValuesFromNonZero();
	return value;
}

void Solver::setNumberIfItOnlyHasOnePossibleNumber()
{

	for (int row = 0; row < 9; row++)
	{
		for (int col = 0; col < 9; col++)
		{
			if (board[row][col] == 0)
			{
				board[row][col] = isThereOnlyOnePossibleNumber(row, col);
				

			}
		}
	}
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
						if (allPossibleNumbers[row][col][i - 1] == true)
						{
							hasThereBeenAChangeInAnything = true;
						}

						allPossibleNumbers[row][col][i - 1] = false;
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
	cout << "Displaying the board..." << endl;

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

	cout << "Displaying the board successful" << endl;

}

//adds sudoku text file to the "board" array
void Solver::addBoard(string file)
{
	cout << "Adding to the board..." << endl;;

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

	setAllPossibleNumbersToTrue();

	cout << "Adding to the board successful" << endl;;
}

Solver::Solver()
{
	//hasThereBeenAChangeInAnything = true;
}
*/


/*

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


*/


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