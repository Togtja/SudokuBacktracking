#pragma once
#include "GlobalVar.h"
#include <atomic>
int solveSudokuBacktrackMT(Sudoku& s);
void sudokuStackSolveMT_rec(Stack &stk, Stack &sol, std::atomic_bool& completed, std::atomic_bool& all_complete);
void sudokuStackSolveMT(Stack &stk, Stack &sol);