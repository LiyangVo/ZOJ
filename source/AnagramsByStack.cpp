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
	int stackIndex;
};

// start
Stack stack;
char sourceWord[MAX_STACK];
char targetWord[MAX_STACK];
char operation[MAX_STACK * 2];

void anagram(int sourceIndex, int targetIndex, int operationIndex, int index = 0) {
	if (sourceIndex > MAX_STACK || targetIndex > MAX_STACK || operationIndex > MAX_STACK * 2) {
		return;
	}
	
	if (targetWord[targetIndex] == 0) {
		for (int i = 0; i < operationIndex; i++) {
			cout << operation[i] << ' ';
		}
		cout << endl;
		return;
	}

	if (index == 0) {
		if (sourceWord[sourceIndex] != 0) {
			stack.push(sourceWord[sourceIndex]);
			operation[operationIndex] = 'i';

			anagram(sourceIndex + 1, targetIndex, operationIndex + 1);

			stack.pop();
		}
		anagram(sourceIndex, targetIndex, operationIndex, index + 1);
	}
	else if (index == 1) {
		if (targetWord[targetIndex] == stack.getTop()) {
			stack.pop();
			operation[operationIndex] = 'o';

			anagram(sourceIndex, targetIndex + 1, operationIndex + 1);

			stack.push(targetWord[targetIndex]);
		}

		anagram(sourceIndex, targetIndex, operationIndex, index + 1);
	}
}

int main() {
	while (cin >> sourceWord >> targetWord) {
		stack.clear();

		cout << '[' << endl;
		anagram(0, 0, 0);
		cout << ']' << endl;
	}

	return 0;
}