#include "HelpFunc.h"
#include <iostream>
void sudokuCreateMap(Sudoku& s) {
	const unsigned char topleft = 201, horizont = 196, vertical = 179, lineright = 195, lineleft = 180, hordown = 194, topright = 187, corners = 197,
		botleft = 200, botright = 188, horup = 193, ddpoleleft = 185, ddvertical = 186, ddhorizont = 205, sdcorner = 216, sdcorner2 = 215,
		ddcorner = 206, ddpoleright = 204, ddhorup = 202, ddhordown = 203, sdhordown = 209, sdhorup = 207, sdpoleright = 199, sdpoleleft = 182; // A good amount of ACII to make it look nice

																																				//Down from here we just form nice looking boxes around the numbers, 
	std::cout << topleft;
	//Top of the box
	for (int i = 0; i < 8; i++) {
		std::cout << ddhorizont << ddhorizont << ddhorizont << ((i % 3 == 2) ? ddhordown : sdhordown);
	}
	std::cout << ddhorizont << ddhorizont << ddhorizont << topright << std::endl;
	//Creates the 8 coloums from there
	for (int j = 0; j < 8; j++) {
		//The numbers
		for (int i = 0; i < 9; i++) {
			std::cout << ((i % 3 == 0) ? ddvertical : vertical) << " " << s[j][i] << " ";
		}
		std::cout << ddvertical << std::endl;
		//The middle part between numbers
		std::cout << ((j % 3 == 2) ? ddpoleright : sdpoleright);
		for (int i = 0; i < 8; i++) {
			if (j % 3 == 2) {
				std::cout << ddhorizont << ddhorizont << ddhorizont << ((i % 3 == 2) ? ddcorner : sdcorner);
			}
			else {
				std::cout << horizont << horizont << horizont << ((i % 3 == 2) ? sdcorner2 : corners);
			}
		}
		if (j % 3 == 2) {
			std::cout << ddhorizont << ddhorizont << ddhorizont << ddpoleleft << std::endl;
		}
		else {
			std::cout << horizont << horizont << horizont << sdpoleleft << std::endl;
		}

	}
	//Prints the last line of numbers
	for (int i = 0; i < 9; i++) {
		std::cout << ((i % 3 == 0) ? ddvertical : vertical) << " " << s[8][i] << " ";
	}
	std::cout << ddvertical << std::endl;
	std::cout << botleft;
	//Prints the bottom part
	for (int i = 0; i < 8; i++) {
		std::cout << ddhorizont << ddhorizont << ddhorizont << ((i % 3 == 2) ? ddhorup : sdhorup);
	}
	std::cout << ddhorizont << ddhorizont << ddhorizont << botright << std::endl;
}
void sudokuSetToZero(Sudoku& s) {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			s[i][j] = 0;
		}
	}
}
bool sudokoIsLegal(Sudoku& s) {

	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			//Checks that there is no more than accurence of a number in the i/(y) coloums
			for (int k = 0; k < MAX; k++) {
				if (j != k && s[i][j] != 0 && s[i][k] != 0) {
					if (s[i][j] == s[i][k]) {
						return false;
					}
				}
			}
			//Checks that there is no more than accurence of a number in the j/(x) rows
			for (int k = 0; k < MAX; k++) {
				if (i != k && s[i][j] != 0 && s[k][j] != 0) {
					if (s[i][j] == s[k][j]) {
						return false;
					}
				}
			}
			for (int k = i - (i % 3); k < i + 3 - (i % 3); k++) {
				for (int l = j - (j % 3); l < j + 3 - (j % 3); l++) {
					if (s[i][j] == s[k][l] && (i != k || j != l) && s[i][j] != 0 && s[k][l] != 0) {
						return false;
					}
				}
			}
		}
	}
	return true;
}
bool sudokuIsSame(Sudoku& f, Sudoku& t) {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			if (t[i][j] != f[i][j]) {
				return false;
			}
		}
	}
	return true;
}
//returns whether true if there is no unplaced numers
bool sudokuIsFinished(Sudoku& s) {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			if (s[i][j] == 0) {
				return false;
			}
		}
	}
	return true;
}
void sudokuCopy(const Sudoku& f, Sudoku& t) {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			t[i][j] = f[i][j];
		}
	}
}