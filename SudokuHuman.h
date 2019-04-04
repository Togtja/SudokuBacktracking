#pragma once
#include "GlobalVar.h"
//A sudoku solver that solves sudokus as humans aka using strategies

bool solveSudokuHuman(int s[][MAX]);

static void pointingPairSimple(bool a[][MAX][MAX], int s[][MAX]);
static void nakedPair(bool a[][MAX][MAX], int s[][MAX]);
static void boxReduction(bool a[][MAX][MAX], int s[][MAX]);

static void copyCanditates(bool f[][MAX][MAX], bool t[][MAX][MAX]);
static bool isSameCan(bool f[][MAX][MAX], bool t[][MAX][MAX]);

//static void createSudoku(int newS[][MAX]);

static bool oneSolution(int s[][MAX]);