#include "SudokuBacktrackingMultiThread.h"
#include "HelpFunc.h"
#include <chrono>
#include <mutex>
#include <ratio>
#include <set>
#include <string> // for memcpy
#include <thread> //for threads'
#include <iostream>

const  int NUM_THREADS = std::thread::hardware_concurrency();
std::mutex stack_lock;
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
		
		stack_lock.lock();
		while (stk.empty()) {
			completed = true;
			stack_lock.unlock();
			if(all_complete){
				return;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds{100});
			stack_lock.lock();
		}
		s = stk.top();
		stk.pop();
		completed = false;
		stack_lock.unlock();
		
		for (int i = 0; i < MAX; i++) {
			for (int j = 0; j < MAX; j++) {
				if (s[i][j] == 0) { //First non-placed place
					for (int k = 1; k < MAX + 1; k++) {
						s[i][j] = k;
						if(sudokoIsLegal(s)){
							{
								std::lock_guard<std::mutex> guard(stack_lock);
								stk.push(s);
							}
							if(sudokuIsFinished(s)){
								{
									std::lock_guard<std::mutex> guard(stack_lock);	
									sol.push(s);
								}
							}
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
	Stack stack; 
	stack.push(s);

	Stack solutions;

	sudokuStackSolveMT(stack, solutions);
	std::cout << "We got " << solutions.size() << " Solutions (Not garanteed unique)\n";
	std::set<Sudoku> unique_sol;
	while (!solutions.empty()) {
		unique_sol.emplace(solutions.top());
		solutions.pop();
	}
	int nrSolutions = unique_sol.size();
	Sudoku solvedSudoku;
	std::cout << "There are/is " << nrSolutions << " Unique Solutions\n";
	if (nrSolutions != 0) {
		s = *unique_sol.begin();
	}
	return nrSolutions;
}


