
#include <iostream>
#include "Solver.h"

using namespace std;

int main()
{
	string sudokuPuzzleFileName = "testFile1.txt";
	
	Solver test;
	test.addBoard(sudokuPuzzleFileName);
	test.displayBoard();







}
