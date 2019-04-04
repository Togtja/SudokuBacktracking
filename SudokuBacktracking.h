#pragma once
#include"Stack.h"
int solveSudokuBacktrack(int s[][MAX]); //Solves the sudoku
bool sudokuIsFinished(int s[][MAX]);//retunrs true if no empty spots
void sudokuStackSolve(Stack &stk, Stack &sol);//Solve the sudokus in stack
