#include<iostream>
/*
	Tomas Himberg Berger
	Solves sudokus with us of backtracking
	also once with more than 1 solution
	it's slower than "human methods" but it can handle one with more than 1 solution
	also sudoku impossible with "human methods"

	It can probably be made quicker, but I did this in a few hours, so won't bother
*/

const int MAX = 9;// I know I know a "global variable" they should be used in a 
				  //multi-person project and generally avoided
				  //But this is MY project, and this made my life easier 

class Stack {
private:
	int top; //Amout of items in stack
	int capasity;//Max items a stack can have
	int* arr; //And array of sudokus (functions a bit like a 3d array)

public:
	//Inizialize the values 
	Stack(int size) {
		arr = new int[MAX*MAX*size];
		capasity = size;
		top = 0;
	}
	//Set all values 
	Stack(int size, int used, int* a) { 
		arr = a;
		capasity = size;
		top = used;
	}
	//Destructor for the pointers used
	~Stack() { delete[] arr; }
	//Returns size of the stack
	int sizeOfStack() { return top; }
	bool push(int s[][MAX]);//Push to stack
	bool pop(int emptyS[][MAX]);//pop from stack
	//Returns true if the stack is empty
	bool isEmpty() { if (top <= 0) { return true; } return false; }
	//The gets is only needed when I make a copy of the stack
	int* getArr() {return arr;}//Returns my array of sudokus
	int getCap() { return capasity; }//returns the capasity of the stack
};

//Functions
bool sudokoIsLegal(int s[][MAX]); //Returns true if valid sudoku
void sudokuSolve(int s[][MAX]); //Solves the sudoku
bool sudokuIsFinished(int s[][MAX]);//retunrs true if no empty spots
void createMap(int s[][MAX]);//Make the sudoku to consol
void sudokuStackSolve(Stack &stk, Stack &sol);//Solve the sudokus in stack
void sudokuSetToZero(int s[][MAX]);//Inisilize everytinhg to 0
bool sudokuIsSame(int f[][MAX], int t[][MAX]);//return true if inputs are the same


int main() {
	///SOME TEST DATA
	///Write your own if you want it to solve that
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
	int solveThisMP[MAX][MAX]{ //2 Solutions
	{ 5,3,0,0,7,0,0,0,0 },
	{ 6,0,0,1,0,5,0,0,0 },
	{ 0,9,8,0,0,0,0,6,0 },
	{ 8,0,0,0,0,0,0,0,3 },
	{ 4,0,0,8,0,3,0,0,1 },
	{ 7,0,0,0,2,0,0,0,6 },
	{ 0,6,0,0,0,0,2,8,0 },
	{ 0,0,0,4,1,9,0,0,5 },
	{ 0,0,0,0,8,0,0,7,9 },
	};
	sudokuSolve(solveThisMP);
	std::cout << "Finished...\n Input any key to continue:\n";
	char t;
	std::cin >> t;
}
//Returns whether the sudoku is legal/valid
bool sudokoIsLegal(int s[][MAX]) {

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
//returns whether true if there is no unplaced numers
bool sudokuIsFinished(int s[][MAX]) {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			if (s[i][j] == 0) {
				return false;
			}
		}
	}
	return true;
}
//creates the fancy CMD sudoku thingi
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
//Recursivly goes into the sudoko for each valid move
//If the move in the end makes an unvalid sudoku
//It backtracks to last valid move
void sudokuStackSolve(Stack &stk, Stack &sol) {
	int s[MAX][MAX];
	sudokuSetToZero(s);
	if (!stk.pop(s)) {
		std::cout << "The stack is empty!\n"
			<< "This should in theory never happend, "
			<< "so you have discovered a bug";
		return;
	}
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			if (s[i][j] == 0) { //First non-placed place
				for (int k = 1; k < MAX+1; k++) {
					s[i][j] = k;
					bool isLegal = sudokoIsLegal(s);
					if (isLegal && sudokuIsFinished(s)) {
						//The sudoku is comple and we print it out
						//sol.push(s);
						
						if (sol.sizeOfStack() == 0) {
							sol.push(s);
						}
						else {
							//copy the data in the arr pointer in the Stack to *c
							int* c = new int[MAX*MAX*sol.getCap()];
							memcpy(c, sol.getArr(), MAX*MAX*sol.getCap() * sizeof(int));
							Stack tempStack(sol.sizeOfStack(), sol.sizeOfStack(), c);
							do {
								int temp[MAX][MAX];
								sudokuSetToZero(temp);
								tempStack.pop(temp);
								if (sudokuIsSame(temp, s)) {
									return;
								}
							} while (!tempStack.isEmpty());
							sol.push(s);
						}

						return;
						
					}
				
					if (isLegal) {
						//The placement is legal, and we add it to the stack
						if (stk.push(s)) { 
							//reurise with the first found correct one
							sudokuStackSolve(stk, sol);
						}
						else {
							std::cout << "The stack is full!\n" 
								<< "This should in theory never happend, "
								<< "so you have discovered a bug";
							return;
						}
					}
				}
			}
		}
	}
}
//Calls all the functions nessecery to solve the sudoku and prints them
void sudokuSolve(int s[][MAX]) {
	Stack stack(MAX*MAX+1); //It uses a DPS/FIFO/Stack 
							//so space comlexity is number of nodes and we have 9*9 nodes
							//adds 1 just in case
	stack.push(s);

	Stack solutions(10);
	std::cout << "Working ...\n";
	sudokuStackSolve(stack, solutions);
	int nrSolutions = solutions.sizeOfStack();
	if (nrSolutions == 1) {
		int solvedSudoku[MAX][MAX];
		sudokuSetToZero(solvedSudoku);
		std::cout << "Found 1 Solution:\n";
		solutions.pop(solvedSudoku);
		createMap(solvedSudoku);
	}
	else if (nrSolutions == 0){
		std::cout << "Found no solution/s\n";
	}
	else if(nrSolutions > 1) {
		std::cout << "Found More than one solution\n";
		int solvedSudoku[MAX][MAX];
		sudokuSetToZero(solvedSudoku);
		for (int i = 0; i <  nrSolutions; i++) {
			solutions.pop(solvedSudoku);
			std::cout << "Solution nr" << i + 1 << ":\n";
			createMap(solvedSudoku);
		}
	}
}
//Inizilize the sudoku with a 9 by 9
void sudokuSetToZero(int s[][MAX]) {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			s[i][j] = 0;
		}
	}
}
//See if the two sudokus are the same
bool sudokuIsSame(int f[][MAX], int t[][MAX]) {
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			if (t[i][j] != f[i][j]) {
				return false;
			}
		}
	}
	return true;
}
///Stack Class Functions
//Push a sudoku into the stack
bool Stack::push(int s[][MAX]) {
	if (top + 1 > capasity) {
		return false;
	}
	top++;
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			arr[top + MAX * (i + MAX * j)] = s[i][j];
		}
	}
	return true;

}
//Pull/pop/take a sudoku from the stack
//It's a FIFO list so it's the last one that got places in
bool Stack::pop(int s[][MAX]) {
	if (top <= 0) {
		return false;
	}
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			s[i][j] = arr[top + MAX * (i + MAX * j)];
		}
	}
	top--;
	return true;
}
