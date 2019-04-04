#pragma once
#include "Stack.h"
int solveSudokuBacktrackMT(int s[][MAX]);
static void sudokuStackSolve(Stack &stk, Stack &sol);
void sudokuStackSolveMT(Stack &stk, Stack &sol);