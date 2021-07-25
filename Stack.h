#pragma once
#include "GlobalVar.h"
#include <set>
class Stack {
private:
	int capasity;//Max items a stack can have
	
	std::mutex myMutex;
	std::set<std::array<std::array<int, MAX>, MAX>> arr;

public:
	//Inizialize the values 
	Stack(int size) {
		capasity = size;
	}
	//Set all values 
	Stack(int size, int used, int* a) {
		//arr = a;
		capasity = size;
	}
	//Destructor for the pointers used
	~Stack() { }
	//Returns size of the stack
	int sizeOfStack() { return arr.size(); }
	bool push(int s[MAX][MAX]);//Push to stack
	bool pop(int emptyS[MAX][MAX]);//pop from stack
	//Returns true if the stack is empty
	bool isEmpty() { return arr.empty(); }
	//The gets is only needed when I make a copy of the stack
	//int* getArr() { return arr; }//Returns my array of sudokus
	int getCap() { return capasity; }//returns the capasity of the stack
};