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
	int s[MAX][MAX];
	sudokuSetToZero(s);
	if (!stk.pop(s)) {
		///DEBUG MESSAGE
		/*
		std::cout << "The stack is empty!\n"
			<< "This should in theory never happend, "
			<< "so you have discovered a bug";
		*/
		return;
	}
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
						if (stk.push(s)) { 
							//reurise with the first found correct one
							sudokuStackSolve(stk, sol);
						}
						else {
							///DEBUG
							/*
							std::cout << "The stack is full!\n" 
								<< "This should in theory never happend, "
								<< "so you have discovered a bug";
							*/
							return;
						}
					}
				}
			}
		}
	}
}
//Calls all the functions nessecery to solve the sudoku and return number of possible solutions
int solveSudokuBacktrack(int s[][MAX]) {
	Stack stack(MAX*MAX+1); //It uses a DPS/FIFO/Stack 
							//so space comlexity is number of nodes and we have 9*9 nodes
							//adds 1 just in case
	stack.push(s);

	Stack solutions(10);

	sudokuStackSolve(stack, solutions);
	int nrSolutions = solutions.sizeOfStack();
	int solvedSudoku[MAX][MAX];
	if (nrSolutions != 0) {
		solutions.pop(solvedSudoku);
		sudokuCopy(solvedSudoku, s);
	}
	std::cout << "There are " << solutions.sizeOfStack() << " Solutions\n";
	solutions.pop(s);
	sudokuCreateMap(s);
	solutions.pop(s);
	sudokuCreateMap(s);
	return nrSolutions;
}


