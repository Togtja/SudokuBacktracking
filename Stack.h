#pragma once
#include "Limits.h"
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
	int* getArr() { return arr; }//Returns my array of sudokus
	int getCap() { return capasity; }//returns the capasity of the stack
};