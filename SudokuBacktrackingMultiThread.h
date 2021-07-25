#pragma once
#include "Stack.h"
#include <atomic>
int solveSudokuBacktrackMT(int s[][MAX]);
void sudokuStackSolveMT_rec(Stack &stk, Stack &sol, std::atomic_bool& completed, std::atomic_bool& all_complete);
void sudokuStackSolveMT(Stack &stk, Stack &sol);