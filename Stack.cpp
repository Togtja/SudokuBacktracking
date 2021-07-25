#include "Stack.h"
#include <array>
#include <algorithm>
#include <iterator>
#include <set>
#include <iostream>
///Stack Class Functions
//Push a sudoku into the stack
bool Stack::push(int s[MAX][MAX]) {
	std::lock_guard<std::mutex> guard(myMutex);
	if (arr.size() >= capasity) {
		return false;
	}
	std::array<std::array<int, MAX>, MAX> tmp;
	for (int i = 0; i < MAX; i++) {
		std::copy(std::begin(s[i]), std::end(s[i]), std::begin(tmp[i]));
	}
	arr.emplace(tmp);
	//arr.push_back(tmp);
	return true;

}
//Pull/pop/take a sudoku from the stack
//It's a FIFO list so it's the last one that got places in
bool Stack::pop(int s[][MAX]) {
	std::lock_guard<std::mutex> guard(myMutex);
	if (arr.empty()) {
		return false;
	}
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			s[i][j] = (*arr.rbegin())[i][j];
		}
	}
	arr.erase(std::prev(arr.end()));
	return true;
}