/***********************
Jugs Problem (1004) from ZOJ
By yangli.network@gmail.com @20170227
************************/

#include <iostream>

using namespace std;

/******************/
// search all result using dfs 
const int MAX_JUG = 1000;
const int MAX_OPERATION_COUNT = 10000;

bool results[MAX_JUG][MAX_JUG];
int operations[MAX_OPERATION_COUNT];
int jugA, jugB;
int target = 0;
bool isFindTraget;

void bfs(int a, int b, int operationIndex) {
	if (isFindTraget) {
		return;
	}
	else if (b == target || a == target) {
		for (int i = 0; i < operationIndex; i++) {
			int operation = operations[i];
			switch (operation)
			{
			case 1: cout << "fill A" << endl; break;
			case 2: cout << "fill B" << endl; break;
			case 3: cout << "empty A" << endl; break;
			case 4: cout << "empty B" << endl; break;
			case 5: cout << "pour A B" << endl; break;
			case 6: cout << "pour B A" << endl; break;
			default: break;
			}
		}
		cout << "success" << endl;
		isFindTraget = true;
		return;
	}

	if (results[a][b]) {
		return;
	}

	results[a][b] = true;

	// fill A
	if (a < jugA) {
		operations[operationIndex] = 1;
		bfs(jugA, b, operationIndex + 1);
	}
	// fill B
	if (b < jugB) {
		operations[operationIndex] = 2;
		bfs(a, jugB, operationIndex + 1);
	}
	// empty A 
	if (a > 0) {
		operations[operationIndex] = 3;
		bfs(0, b, operationIndex + 1);
	}
	// empty B
	if (b > 0) {
		operations[operationIndex] = 4;
		bfs(a, 0, operationIndex + 1);
	}
	// pour a to b 
	if (a > 0 && b < jugB) {
		operations[operationIndex] = 5;
		if (jugB - b >= a) {
			bfs(0, b + a, operationIndex + 1);
		}
		else {
			bfs(a - (jugB - b), jugB, operationIndex + 1);
		}
	}
	// pour b to a 
	if (b > 0 && a < jugA) {
		operations[operationIndex] = 6;
		if (jugA - a >= b) {
			bfs(a + b, 0, operationIndex + 1);
		}
		else {
			bfs(jugA, b - (jugA - a), operationIndex + 1);
		}
	}

	// !!!!!!!!!
	results[a][b] = false;
}

int main() {
	while (cin >> jugA >> jugB >> target) {
		// clear
		for (int i = 0; i < jugA; i++) {
			for (int j = 0; j < jugB; j++) {
				results[i][j] = false;
			}
		}

		isFindTraget = false;
		bfs(0, 0, 0);
	}

	return 0;
}