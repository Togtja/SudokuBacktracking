#pragma once
#include "GlobalVar.h"
void sudokuCreateMap(Sudoku& s);
void sudokuSetToZero(Sudoku& s);
bool sudokoIsLegal(Sudoku& s);
bool sudokuIsSame(Sudoku& f, Sudoku& t);
bool sudokuIsFinished(Sudoku& s);
void sudokuCopy(const Sudoku& f, Sudoku& t);