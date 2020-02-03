
#include <iostream>
#include "Solver.h"
#include <unordered_set>

using namespace std;

int main()
{
	//needs something to check if file even exists

	string sudokuPuzzleFileName = "testFile2.txt";
	
	Solver test;
	test.addBoard(sudokuPuzzleFileName);
	test.displayBoard();
	test.basicSolve();
	test.basicSolve();
	test.basicSolve();
	test.basicSolve();
	test.displayBoard();


	//hash_set<int> something;
	//something.insert(5);





}
