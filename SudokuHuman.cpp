#include<iostream>
#include <random> //To be used to make sudokus

//A sudoku solver that solves sudokus as humans aka using strategies

const int MAX = 9;// I know I know a "global variable" they should be used in a 
				  //multi-person project and generally avoided
				  //But this is MY project, and this made my life easier
std::random_device rd;  //Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

//Functions
void createMap(int s[][MAX]);
bool solveSudoku(int s[][MAX]);
void copyMAXArr(int f[][MAX], int t[][MAX]);
bool isSameArr(int f[][MAX], int t[][MAX]);
bool isFinished(int s[][MAX]);
void pointingPairSimple(bool a[][MAX][MAX], int s[][MAX]);
void nakedPair(bool a[][MAX][MAX], int s[][MAX]);
void boxReduction(bool a[][MAX][MAX], int s[][MAX]);
void copyCanditates(bool f[][MAX][MAX], bool t[][MAX][MAX]);
bool isSameCan(bool f[][MAX][MAX], bool t[][MAX][MAX]);
bool isLegalSudoku(int s[][MAX]);
void createSudoku(int newS[][MAX]);
bool oneSolution(int s[][MAX]);
void setToZero(int s[][MAX]);
//TODO Find out why  pointingPairSimple fucks with my code

int	main() {
	int solveThis[MAX][MAX]{//Just normal strategy to solve so it becomes solved
	{ 0,0,5,0,0,7,0,6,0 },
	{ 3,2,0,6,5,0,0,4,0 },
	{ 0,0,0,0,0,2,5,0,9 },
	{ 0,0,6,0,0,0,0,2,0 },
	{ 0,0,3,5,2,6,7,0,0 },
	{ 0,4,0,0,0,0,6,0,0 },
	{ 9,0,1,2,0,0,0,0,0 },
	{ 0,3,0,0,6,8,0,7,5 },
	{ 0,5,0,4,0,0,3,0,0 }
	};
	int solveThis2[MAX][MAX]{ //Needing pointing pair to be solved
	{ 0,0,0,0,6,7,4,9,0 },
	{ 0,9,0,0,0,0,2,0,6 },
	{ 0,0,0,5,0,0,0,8,0 },
	{ 0,0,5,0,0,8,0,0,0 },
	{ 7,0,0,0,9,0,0,0,8 },
	{ 0,0,0,4,0,0,3,0,0 },
	{ 0,6,0,0,0,4,0,0,0 },
	{ 5,0,4,0,0,0,0,6,0 },
	{ 0,8,3,1,5,0,0,0,0 }
	};
	int solveThis3[MAX][MAX]{ //Unsolvable Sudoku 
	{ 1,7,3,8,0,0,9,5,0 },	
	{ 8,0,0,7,5,0,0,0,0 },	
	{ 0,0,0,0,0,0,0,4,0 },	
	{ 0,0,0,5,3,0,0,0,0 },
	{ 2,0,0,0,9,0,3,0,0 },
	{ 5,0,6,0,8,0,0,0,0 },
	{ 0,0,7,0,0,4,0,0,5 },
	{ 0,6,0,0,2,0,0,0,9 },
	{ 3,5,0,0,0,0,4,6,0 }
	};
	int solveThisNP[MAX][MAX]{ //Alot of naked pairs
	{ 0,8,0,0,9,0,0,3,0 },
	{ 0,3,0,0,0,0,0,6,9 },
	{ 9,0,2,0,6,3,1,5,8 },
	{ 0,2,0,8,0,4,5,9,0 },
	{ 8,5,1,9,0,7,0,4,6 },
	{ 3,9,4,6,0,5,8,7,0 },
	{ 5,6,3,0,4,0,9,8,7 },
	{ 2,0,0,0,0,0,0,1,5 },
	{ 0,1,0,0,5,0,0,2,0 },
	};
	solveSudoku(solveThis2);
	if (isLegalSudoku(solveThis2)) {
		createMap(solveThis2);
	}
	else {
		std::cout << "Unable to solve the sudoku\n";
	}
	std::cout << "GENERATED SUDOKU\n";
	int createS[MAX][MAX] = {false};
	createSudoku(createS);
	createMap(createS);
	solveSudoku(createS);
	createMap(createS);
	char c;
	std::cin >> c;

	return 0;
}
//0-2 and 0-2, 3-5 and 3-5, 6-8 and 6-8
bool solveSudoku(int s[][MAX]) {
	int copyarr[MAX][MAX];
	int pp[MAX][MAX];

	bool avl[MAX][MAX][MAX] = { false }; //Fist is a 2d array of the sudoku the last is a 1d array of what numbers is possible
	//Makses so that number already in has only 1 possible placement
	//and the 0's/empty has every thing possible
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			if (s[i][j] != 0) {
				avl[i][j][s[i][j] - 1] = true;
				
			}
			else {
				for (int k = 0; k < MAX; k++) {
					avl[i][j][k] = true;
				}
			}
		}
	}
	bool avlCopy[MAX][MAX][MAX];

	int runs = 0;
	int oldS[MAX][MAX];
	bool progress = true;
	do {
		copyCanditates(avl, avlCopy);
		for (int i = 0; i < MAX; i++) {
			for (int j = 0; j < MAX; j++) {
				//If the sudoku  space is empty
				if (s[i][j] == 0) {
					//checks horizontal and vertical
					for (int k = 0; k < MAX; k++) {
						if (k != j) {
							if (s[i][k] != 0) {
								avl[i][j][s[i][k] - 1] = false;
							}
						}
						if (k != i) {
							if (s[k][j] != 0) {
								avl[i][j][s[k][j] - 1] = false;
							}
						}
					}
					

					//checks the 3x3 
					for (int k = i - (i % 3); k < i + 3 - (i % 3); k++) {
						for (int l = j - (j % 3); l < j + 3 - (j % 3); l++) {
							if ((i != k || l != j) && s[k][l] != 0) {
								avl[i][j][s[k][l] - 1] = false;
							}
						}
					}
					//checks 3x3 for n, and if it's the only one with n as a possiblilty then it is n
					for (int q = 0; q < MAX; q++) {
						if (avl[i][j][q]) {
							bool exist = false;
							for (int k = i - (i % 3); k < i + 3 - (i % 3); k++) {
								for (int l = j - (j % 3); l < j + 3 - (j % 3); l++) {
									if ((i != k || l != j) && avl[i][j][q] == avl[k][l][q]) {
										exist = true;
									}

								}
							}
							if (exist == false) {
								for (int w = 0; w < MAX; w++) {
									avl[i][j][w] = false;
								}
								avl[i][j][q] = true;
								break;
							}
						}
					}
				}
			}
		}

		for (int i = 0; i < MAX; i++) {
			for (int j = 0; j < MAX; j++) {
				int nrTrue = 0;
				int insert = 0;
				for (int k = 0; k < MAX; k++) {
					if (avl[i][j][k]) {
						nrTrue++;
						insert = k + 1;
					}
				}
				if (nrTrue == 1) {
					s[i][j] = insert;

				}

			}
		}
		boxReduction(avl, s);
		nakedPair(avl, s);
		
	
		if (isSameCan(avl, avlCopy)) {
			progress = false;
		}
		runs++;
	} while (!isFinished(s) && progress);

	if (!progress || !isFinished(s) || !isLegalSudoku(s)) {
		return false;
	}
	return true;
}
void createMap(int s[][MAX]) {
	char topleft = 201, horizont = 196, vertical = 179, lineright = 195, lineleft = 180, hordown = 194, topright = 187, corners = 197,
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

void copyMAXArr(int f[][MAX], int t[][MAX]) {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			t[i][j] = f[i][j];
		}
	}
}
bool isSameArr(int f[][MAX], int t[][MAX]) {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			if (t[i][j] != f[i][j]) {
				return false;
			}
		}
	}
	return true;
}

void copyCanditates(bool f[][MAX][MAX ], bool t[][MAX][MAX]) {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			for (int q = 0; q < MAX; q++) {
				t[i][j][q] = f[i][j][q];
			}
		}
	}
}
bool isSameCan(bool f[][MAX][MAX], bool t[][MAX][MAX]) {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			for (int q = 0; q < MAX; q++) {
				if (t[i][j][q] != f[i][j][q]) {
					return false;
				}
			}

		}
	}
	return true;
}

bool isFinished(int s[][MAX]) {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			if (s[i][j] == 0) {
				return false;
			}
		}
	}
	return true;
}

int possibleCantidates(bool a[][MAX][MAX], int i, int j) {
	int possible = 0;
	for (int q = 0; q < MAX; q++) {
		if (a[i][j][q]) {
			possible++;
		}
	}
	return possible;
}

bool isLegalSudoku(int s[][MAX]) {
	
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

void pointingPairSimple(bool a[][MAX][MAX], int s[][MAX]) {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			
			if (possibleCantidates(a, i, j) < 2) { continue; }
			for (int q = 0; q < MAX; q++) {
				//int possible;
				if (a[i][j][q]) {
					//possible = 1;
					bool colum = false; //0 means neither, 1 means colum, 2 means row, and 3 means both;
					bool row = false;
					for (int k = i - (i % 3); k < i + 3 - (i % 3); k++) {
						for (int l = j - (j % 3); l < j + 3 - (j % 3); l++) {
							int subPossible = 0;
							for (int w = 0; w < MAX; w++) {
								
								if (a[k][l][w]) {
									subPossible++;
								}
							}
							if ((i != k || j != l) && a[i][j][q] == a[k][l][q] && subPossible > 1) {
								if (i == k) {
									row = true;
								}
								if (j == l) {
									colum = true;
								}
								if (i != k && j != l) {
									row = true;
									colum = true;
									
								}
							}
						}
						
					}

					if (colum && !row) {
						for (int i_1 = 0; i_1 < MAX; i_1++) {
							if (i_1 < i - (i % 3) || i_1 >= i + 3 - (i % 3)) {
								a[i_1][j][q] = false;
							}
						}
					}

					if (row && !colum) {
						for (int j_1 = 0; j_1 < MAX; j_1++) {
							if (j_1 < j - (j % 3) || j_1 >= j + 3 - (j % 3)) {
								a[i][j_1][q] = false;
							}
						}
					}
				}

			}

		}
	}
}
void nakedPair(bool a[][MAX][MAX], int s[][MAX]) {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			if (s[i][j] != 0) { continue; }
			if (possibleCantidates(a,i,j) != 2) { continue; }
			bool row = true;
			bool colom = true;
			bool x3 = true;
			//For it's rows and colums
			//rows - trying to find exacly same in q values (AKA naked pairs)
			for (int k = 0; k < MAX; k++) {
				row = true;
				for (int q = 0; q < MAX; q++) {
					if (j == k) { row = false; break; }
					if (a[i][j][q] != a[i][k][q]) {
						row = false;
					}
				}

				if (row) {
					for (int w = 0; w < MAX; w++) {
						for (int q = 0; q < MAX; q++) {
							if (w != k && w != j && a[i][j][q] == a[i][w][q]) {
								
								a[i][w][q] = false;
							}
						}
					}
					break;
				}
			}
			//coloms - trying to find exacly same in q values (AKA naked pairs)
			for (int k = 0; k < MAX; k++) {
				colom = true;
				for (int q = 0; q < MAX; q++) {
					if (i == k) { colom = false; break; }
					if (a[i][j][q] != a[k][j][q]) {
						colom = false;
					}
				}

				if (colom) {
					for (int w = 0; w < MAX; w++) {
						for (int q = 0; q < MAX; q++) {
							if (w != k && w != i && a[i][j][q] == a[w][j][q]) {
								
								a[w][j][q] = false;
							}
						}
					}
					break;
				}
			}
			//3x3 - trying to find exacly same in q values (AKA naked pairs)
			
			for (int k = i - (i % 3); k < i + 3 - (i % 3); k++) {
				for (int l = j - (j % 3); l < j + 3 - (j % 3); l++) {
					x3 = true;
					for (int q = 0; q < MAX; q++) {
						if (i == k && j == l) { x3 = false; break; }
						if (a[i][j][q] != a[k][l][q]) {
							x3 = false;
						}
					}

					if (x3) {
						
						for (int w = i - (i % 3); w < i + 3 - (i % 3); w++) {
							for (int x = j - (j % 3); x < j + 3 - (j % 3); x++) {
								for (int q = 0; q < MAX; q++) {
									if (((w != k || x != l) && (w != i || x != j)) 
										&& a[i][j][q] == a[w][x][q]) {
										a[w][x][q] = false;
									}
								}
							}
						}
						break;
					}

				}
			}
		}

	}
}
void boxReduction(bool a[][MAX][MAX], int s[][MAX]) {
	//Find two n in a row/colom inside a 3x3
	//colom inside 3x3
	bool colomBox = false;
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			if (s[i][j] != 0) { continue; }
			for (int k = i - (i % 3); k < i + 3 - (i % 3); k++) {
				if (i == k) { continue; }
				for (int q = 0; q < MAX; q++) {
					if (a[i][j][q] != a[k][j][q]) { continue; }
					if (i != k && a[i][j][q] != 0) {
						colomBox = true;
						//check outside the box
						for (int w = 0; w < MAX; w++) {
							if ((w < i - (i % 3) || w >= i + 3 - (i % 3))
								&& a[w][j][q] == a[i][j][q]) {
								colomBox = false;
								break;
							}
						}
					}
					if (colomBox) {
						for (int x = i - (i % 3); x < i + 3 - (i % 3); x++) {
							for (int y = j - (j % 3); y < j + 3 - (j % 3); y++) {
								if (j != y && a[i][j][q] == a[x][y][q]) {
									a[x][y][q] = false;
								}
							}
						}
						colomBox = false;
					}
				}
			}
			//row inside 3x3
			bool rowBox = false;
			for (int k = j - (j % 3); k < j + 3 - (j % 3); k++) {
				if (j == k) { continue; }
				for (int q = 0; q < MAX; q++) {
					if (a[i][j][q] != a[i][k][q]) { continue; }
					if (j != k && a[i][j][q] != 0 ) {
						rowBox = true;
						//check outside the box
						for (int w = 0; w < MAX; w++) {
							if ((w < j - (j % 3) || w >= j + 3 - (j % 3))
								&& a[i][w][q] == a[i][j][q]) {
								rowBox = false;
								break;
							}
						}
					}
					if (rowBox) {
						for (int x = i - (i % 3); x < i + 3 - (i % 3); x++) {
							for (int y = j - (j % 3); y < j + 3 - (j % 3); y++) {
								if (i != x  && a[i][j][q] == a[x][y][q]) {
									a[x][y][q] = false;
								}
							}
						}
						rowBox = false;
					}
				}
			}
		}

	}
}

/*void createSudoku(int newS[][MAX]) {

	std::uniform_int_distribution<> num(1, 9); //Random number from 1 to 9
	std::uniform_int_distribution<> willPlace(1, 5); //
	int minNeeded = 17;
	int maxNeeded = MAX * MAX - minNeeded;
	int placed = 0;
	//Makes a legal sudoku

	do {
		setToZero(newS);
		for (placed = 0; placed < maxNeeded;) {
			for (int i = 0; i < MAX; i++) {
				for (int j = 0; j < MAX; j++) {
					if (willPlace(gen) == 1) {
						newS[i][j] = num(gen);
						placed++;
					}
				}
			}
			if (oneSolution(newS)) { break; }
		}

	} while (!oneSolution(newS));

}*/

bool oneSolution(int s[][MAX]) {
	int temp[MAX][MAX];
	copyMAXArr(s, temp);
	if (solveSudoku(temp) && isFinished(temp) ) {
		return true;
	}
	false;
}
void setToZero(int s[][MAX]) {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			s[i][j] = 0;
		}
	}
}
