#pragma once
#include "Stack.h"
int solveSudokuBacktrackMT(int s[][MAX]);
void sudokuStackSolve_rec(Stack &stk, Stack &sol);
void sudokuStackSolveMT(Stack &stk, Stack &sol);