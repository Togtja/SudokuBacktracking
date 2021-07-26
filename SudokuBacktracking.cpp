#include "SudokuBacktracking.h"
#include "HelpFunc.h"
#include <iostream>
#include <string> // for memcpy
/*
	Tomas Himberg Berger
	Solves sudokus with us of backtracking
	also sudokus with more than 1 solution
	it's slower than "human methods" but it can handle one with more than 1 solution
	also sudoku's impossible with "human methods"

	It can probably be made quicker, but I did this in a few hours, so won't bother
*/


//Recursivly goes into the sudoko for each valid move
//If the move in the end makes an unvalid sudoku
//It backtracks to last valid move
void sudokuStackSolve(Stack &stk, Stack &sol) {
	auto s = stk.top();
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			if (s[i][j] == 0) { //First non-placed place
				for (int k = 1; k < MAX+1; k++) {
					s[i][j] = k;
					bool isLegal = sudokoIsLegal(s);
					if (isLegal && sudokuIsFinished(s)) {
						//The sudoku is comple and we print it out
						//sol.push(s);
						sol.push(s);

						return;
						
					}
				
					if (isLegal) {
						//The placement is legal, and we add it to the stack
						stk.push(s);
						//reurise with the first found correct one
						sudokuStackSolve(stk, sol);
						
					}
				}
			}
		}
	}
}
//Calls all the functions nessecery to solve the sudoku and return number of possible solutions
int solveSudokuBacktrack(Sudoku& s) {
	Stack stack;
	stack.push(s);

	Stack solutions;

	sudokuStackSolve(stack, solutions);
	int nrSolutions = solutions.size();
	Sudoku solvedSudoku[MAX][MAX];
	if (nrSolutions != 0) {
		s = solutions.top();
		solutions.pop();
	}
	return nrSolutions;
}


