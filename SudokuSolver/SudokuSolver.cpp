
#include <iostream>
#include "Solver.h"
#include <unordered_set>

using namespace std;

int main()
{

	string sudokuPuzzleFileName = "testFile5.txt";
	
	Solver test;
	test.addBoard(sudokuPuzzleFileName);
	test.displayBoard();
	test.solverLoop();
	test.displayBoard();
	//test.displayAllPossibleValuesFromAllValues();
	//test.getNumberOfSolvedValues();
	
	



}
