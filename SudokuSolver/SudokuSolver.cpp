
#include <iostream>
#include "Solver.h"
#include <unordered_set>

using namespace std;

int main()
{

	string sudokuPuzzleFileName = "testFile7.txt";
	
	Solver test;
	test.addBoard(sudokuPuzzleFileName);
	test.displayBoard();
	test.solverLoop();
	test.displayBoard();
	test.displayAllPossibleValuesFromCertainRow(6);
	test.displayAllPossibleValuesFromCertainRow(7);
	test.displayAllPossibleValuesFromCertainRow(8);
	//test.displayAllPossibleValuesFromAllValues();
	test.getNumberOfSolvedValues();
	test.totalNumbmerOfPossibleValues();
	test.endAllBeAllOne();

	



}
