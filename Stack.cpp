#include "Stack.h"
#include <mutex>
std::mutex myMutex;
///Stack Class Functions
//Push a sudoku into the stack
bool Stack::push(int s[][MAX]) {
	std::lock_guard<std::mutex> guard(myMutex);
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
	std::lock_guard<std::mutex> guard(myMutex);
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