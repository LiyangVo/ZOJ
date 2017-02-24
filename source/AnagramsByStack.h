/***********************
Crashing Anagrams by Stack (1004) from ZOJ
By yangli.network@gmail.com @20170224
************************/

#include <iostream>

using namespace std;

const int MAX_STACK = 100;

class Stack {
public:
	Stack() {}
	~Stack() {}

	void push(char ch) {
		if (stackIndex < MAX_STACK) {
			stack[stackIndex++] = ch;
		}
	}
	int pop() {
		if (stackIndex > 0) {
			return stack[--stackIndex];
		}

		return 0;
	}
	int getSize() {
		return stackIndex;
	}
	char getTop() {
		if (stackIndex > 0) {
			return stack[stackIndex - 1];
		}
		
		return 0;
	}
	void clear() {
		stackIndex = 0;
	}

private:
	char stack[MAX_STACK];
	int stackIndex = 0;
};

// start
Stack stack;
char sourceWord[MAX_STACK];
char targetWord[MAX_STACK];
char operation[MAX_STACK * 2];
int operationIndex;

void anagram(int sourceIndex, int targetIndex) {
	if (targetWord[targetIndex] == 0) {
		for (int i = 0; i < operationIndex; i++) {
			cout << operation[i] << ' ';
		}
		cout << endl;
		return;
	}

	if (sourceWord[sourceIndex] != 0) {
		stack.push(sourceWord[sourceIndex]);
		operation[operationIndex++] = 'i';
		anagram(++sourceIndex, targetIndex);

		sourceIndex--;
		operationIndex--;
		stack.pop();
	}

	if (targetWord[targetIndex] == stack.getTop()) {
		stack.pop();
		operation[operationIndex++] = 'o';

		anagram(sourceIndex, ++targetIndex);
	}
}

int main() {
	while (true) {
		memset(sourceWord, 0, MAX_STACK);
		memset(targetWord, 0, MAX_STACK);
		stack.clear();
		operationIndex = 0;

		cin >> sourceWord >> targetWord;

		cout << '[' << endl;
		anagram(0, 0);
		cout << '[' << endl;
	}
}