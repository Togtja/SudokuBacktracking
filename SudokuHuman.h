#pragma once
#include "GlobalVar.h"
#include "HelpFunc.h"
//A sudoku solver that solves sudokus as humans aka using strategies

bool solveSudokuHuman(Sudoku& s);

static void pointingPairSimple(bool a[][MAX][MAX], Sudoku& s);
static void nakedPair(bool a[][MAX][MAX], Sudoku& s);
static void boxReduction(bool a[][MAX][MAX], Sudoku& s);

static void copyCanditates(bool f[][MAX][MAX], bool t[][MAX][MAX]);
static bool isSameCan(bool f[][MAX][MAX], bool t[][MAX][MAX]);

//static void createSudoku(int newS[][MAX]);

static bool oneSolution(Sudoku& s);