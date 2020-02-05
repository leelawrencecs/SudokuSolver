
#include <iostream>
#include "Solver.h"
#include <unordered_set>

using namespace std;

int main()
{
	//needs something to check if file even exists

	string sudokuPuzzleFileName = "testFile4.txt";
	
	Solver test;
	test.addBoard(sudokuPuzzleFileName);
	test.displayBoard();
	test.solve();
	test.displayBoard();
	



}
