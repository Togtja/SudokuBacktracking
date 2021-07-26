#include <iostream>
#include "SudokuBacktracking.h"
#include "SudokuHuman.h"
#include "HelpFunc.h"
#include "SudokuBacktrackingMultiThread.h"

int main() {
	//The Sudokus
	int sudokuNr = 4;
	int toSolve;
	Sudoku theSudoku;
	sudokuSetToZero(theSudoku);
	const Sudoku solveThis1{{//Just normal strategy to solve so it becomes solved
	{ 0,0,5,0,0,7,0,6,0 },
	{ 3,2,0,6,5,0,0,4,0 },
	{ 0,0,0,0,0,2,5,0,9 },
	{ 0,0,6,0,0,0,0,2,0 },
	{ 0,0,3,5,2,6,7,0,0 },
	{ 0,4,0,0,0,0,6,0,0 },
	{ 9,0,1,2,0,0,0,0,0 },
	{ 0,3,0,0,6,8,0,7,5 },
	{ 0,5,0,4,0,0,3,0,0 }
	}};
	const Sudoku solveThis2{{ //Needing pointing pair to be solved
	{ 0,0,0,0,6,7,4,9,0 },
	{ 0,9,0,0,0,0,2,0,6 },
	{ 0,0,0,5,0,0,0,8,0 },
	{ 0,0,5,0,0,8,0,0,0 },
	{ 7,0,0,0,9,0,0,0,8 },
	{ 0,0,0,4,0,0,3,0,0 },
	{ 0,6,0,0,0,4,0,0,0 },
	{ 5,0,4,0,0,0,0,6,0 },
	{ 0,8,3,1,5,0,0,0,0 }
	}};
	const Sudoku solveThis3{{ //Unsolvable Sudoku 
	{ 1,7,3,8,0,0,9,5,0 },
	{ 8,0,0,7,5,0,0,0,0 },
	{ 0,0,0,0,0,0,0,4,0 },
	{ 0,0,0,5,3,0,0,0,0 },
	{ 2,0,0,0,9,0,3,0,0 },
	{ 5,0,6,0,8,0,0,0,0 },
	{ 0,0,7,0,0,4,0,0,5 },
	{ 0,6,0,0,2,0,0,0,9 },
	{ 3,5,0,0,0,0,4,6,0 }
	}};
	const Sudoku solveThis4{{ //Alot of naked pairs
	{ 0,8,0,0,9,0,0,3,0 },
	{ 0,3,0,0,0,0,0,6,9 },
	{ 9,0,2,0,6,3,1,5,8 },
	{ 0,2,0,8,0,4,5,9,0 },
	{ 8,5,1,9,0,7,0,4,6 },
	{ 3,9,4,6,0,5,8,7,0 },
	{ 5,6,3,0,4,0,9,8,7 },
	{ 2,0,0,0,0,0,0,1,5 },
	{ 0,1,0,0,5,0,0,2,0 },
	}};
	std::cout << "What sudoku do you want to solve? ( 1 - " << sudokuNr << " )\n";
	std::cin >> toSolve;
	switch (toSolve) {
	case 1:
		sudokuCopy(solveThis1,theSudoku);
		break;
	case 2:
		sudokuCopy(solveThis2, theSudoku);
		break;
	case 3:
		sudokuCopy(solveThis3, theSudoku);
		break;
	case 4:
		sudokuCopy(solveThis4, theSudoku);
		break;
	default:
		std::cout << "No such sudoku\n";
		return 0;
		break;
	}
	std::cout << "Using strategies or just backtracking?(y for strategies, anythign else backtracking)\n ";
	char strat;
	std::cin >> strat;
	if (tolower(strat) == 'y') {
		if (solveSudokuHuman(theSudoku)) {
			sudokuCreateMap(theSudoku);
		}
		else {
			std::cout << "Human solver couldn't find a solution\n"
				<< "There still might be one, try the backtracking, it will find if there is a solution and if so even how many\n";
		}
	}
	else {
		std::cout << "Working ...\n";
		int sol = solveSudokuBacktrackMT(theSudoku);
		if (sol == 0) {
			std::cout << "There are no found solutions\n";
		}
		else if (sol == 1) {
			std::cout << "Found One correct solutions\n";
			sudokuCreateMap(theSudoku);
		}
		else {
			std::cout << "Found several correct solutions\nDisplaying one of them\n";
			sudokuCreateMap(theSudoku);
		}
	}
	return 0;
}