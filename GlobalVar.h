#pragma once
#include <mutex>
#include <stack>
#include <array>
const int MAX = 9;
typedef std::array<std::array<int, MAX>, MAX> Sudoku;
typedef std::stack<Sudoku> Stack;
