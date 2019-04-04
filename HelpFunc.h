#pragma once
#include "Limits.h"
void sudokuCreateMap(int s[][MAX]);
void sudokuSetToZero(int s[][MAX]);
bool sudokoIsLegal(int s[][MAX]);
bool sudokuIsSame(int f[][MAX], int t[][MAX]);
bool sudokuIsFinished(int s[][MAX]);
void sudokuCopy(const int f[][MAX], int t[][MAX]);