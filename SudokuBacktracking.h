#pragma once
#include "GlobalVar.h"
int solveSudokuBacktrack(Sudoku& s); //Solves the sudoku
bool sudokuIsFinished(Sudoku& s);//retunrs true if no empty spots
void sudokuStackSolve(Stack &stk, Stack &sol);//Solve the sudokus in stack
