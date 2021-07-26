#include "SudokuBacktrackingMultiThread.h"
#include "HelpFunc.h"
#include <chrono>
#include <ratio>
#include <string> // for memcpy
#include <thread> //for threads'
#include <iostream>
#define NUM_THREADS 12 //for now only 9 threads supported
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
void sudokuStackSolveMT_rec(Stack &stk, Stack &sol, std::atomic_bool& completed, std::atomic_bool& all_complete) {
	Sudoku s;
	while (!all_complete) {
		while (stk.empty()) {
			completed = true;
			if(all_complete){
				return;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds{100});

		}
		s = stk.top();
		stk.pop();
		completed = false;
		for (int i = 0; i < MAX; i++) {
			for (int j = 0; j < MAX; j++) {
				if (s[i][j] == 0) { //First non-placed place
					for (int k = 1; k < MAX + 1; k++) {
						s[i][j] = k;
						bool isLegal = sudokoIsLegal(s);
						if (isLegal && sudokuIsFinished(s)) {
							//The sudoku is comple and we print it out
							std::cout << "We done solved it";
							sol.push(s);
							completed = true;
							return;
						}
						else if (isLegal) {
							//The placement is legal, and we add it to the stack
							stk.push(s);
						}
					}
				}
			}
		}
	}
}

void sudokuStackSolveMT(Stack &stk, Stack &sol) {
	std::thread threads[NUM_THREADS];
	std::atomic_bool completed[NUM_THREADS];
	std::atomic_bool all_completed = false;
	for (int i = 0; i < NUM_THREADS; i++) {
		completed[i] = false; 
		threads[i] = std::thread(sudokuStackSolveMT_rec, std::ref(stk), std::ref(sol), std::ref(completed[i]), std::ref(all_completed));
	}
	while (!all_completed) {
		int nr_completed = 0;
		for (int i = 0; i < NUM_THREADS; i++) {
			if(completed[i]){
				nr_completed++;
			}
			//std:: cout << "Completed" << nr_completed << "/" << "9\n";
			if(nr_completed == NUM_THREADS){
				all_completed = true;
			}
		}
	}
	for (int i = 0; i < NUM_THREADS; i++) {
		threads[i].join();
	}
}
//Calls all the functions nessecery to solve the sudoku and return number of possible solutions
int solveSudokuBacktrackMT(Sudoku& s) {
	Stack stack; //It uses a DPS/FIFO/Stack 
							//so space comlexity is number of nodes and we have 9*9 nodes
							//adds 1 just in case
	stack.push(s);

	Stack solutions;

	sudokuStackSolveMT(stack, solutions);
	int nrSolutions = solutions.size();
	Sudoku solvedSudoku;
	std::cout << "There are " << nrSolutions << " Solutions\n";
	if (nrSolutions != 0) {
		s = solutions.top();
	}
	return nrSolutions;
}


