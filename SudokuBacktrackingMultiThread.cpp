#include "SudokuBacktrackingMultiThread.h"
#include "HelpFunc.h"
#include <string> // for memcpy
#include <thread> //for threads'
#define NUM_THREADS MAX //for now only 9 threads supported
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
static void sudokuStackSolve(Stack &stk, Stack &sol) {
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
				for (int k = 1; k < MAX + 1; k++) {
					s[i][j] = k;
					bool isLegal = sudokoIsLegal(s);
					if (isLegal && sudokuIsFinished(s)) {
						//The sudoku is comple and we print it out
						//sol.push(s);

						if (sol.sizeOfStack() == 0) {
							sol.push(s);
						}
						else {
							//copy the data in the arr pointer in the Stack to *c
							int* c = new int[MAX*MAX*sol.getCap()];
							memcpy(c, sol.getArr(), MAX*MAX*sol.getCap() * sizeof(int));
							Stack tempStack(sol.sizeOfStack(), sol.sizeOfStack(), c);
							do {
								int temp[MAX][MAX];
								sudokuSetToZero(temp);
								tempStack.pop(temp);
								if (sudokuIsSame(temp, s)) {
									return;
								}
							} while (!tempStack.isEmpty());
							sol.push(s);
						}

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

void sudokuStackSolveMT(Stack &stk, Stack &sol) {
	std::thread threads[NUM_THREADS];
	int og[MAX][MAX];
	stk.pop(og);
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			if (og[i][j] == 0) {
				int s[MAX][MAX];
				sudokuCopy(og, s);
				for (int k = 0; k < NUM_THREADS; k++) {
					s[i][j] = k;
					stk.push(s);
				}
			}
		}
	}

	for (int i = 0; i < NUM_THREADS; i++) {
		threads[i] = std::thread(&sudokuStackSolve, std::ref(stk), std::ref(sol));
	}
	for (int i = 0; i < NUM_THREADS; i++) {
		threads[i].join();
	}
}
//Calls all the functions nessecery to solve the sudoku and return number of possible solutions
int solveSudokuBacktrackMT(int s[][MAX]) {
	Stack stack(MAX*MAX + 1); //It uses a DPS/FIFO/Stack 
							//so space comlexity is number of nodes and we have 9*9 nodes
							//adds 1 just in case
	stack.push(s);

	Stack solutions(10);

	sudokuStackSolveMT(stack, solutions);
	int nrSolutions = solutions.sizeOfStack();
	int solvedSudoku[MAX][MAX];
	if (nrSolutions != 0) {
		solutions.pop(solvedSudoku);
		sudokuCopy(solvedSudoku, s);
	}
	return nrSolutions;
}


