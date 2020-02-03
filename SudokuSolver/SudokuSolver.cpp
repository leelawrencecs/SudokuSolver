
#include <iostream>
#include "Solver.h"

using namespace std;

int main()
{
	//needs something to check if file even exists
	string sudokuPuzzleFileName = "testFile1.txt";
	
	Solver test;
	test.addBoard(sudokuPuzzleFileName);
	test.displayBoard();
	







}
