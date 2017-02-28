/***********************
Gnome Tetravex (1008) from ZOJ
By yangli.network@gmail.com @20170228
************************/

#include <iostream>

using namespace std;

const int MAX_N = 5;
const int SQUARE_NUMBER_COUNT = 4;
const int MAX_SQUARE_COUNT = MAX_N * MAX_N;
const int MAX_NUMBER_COUNT = MAX_SQUARE_COUNT * SQUARE_NUMBER_COUNT;

int n;
int squareCount;
int numberCount;
int squareOrders[MAX_SQUARE_COUNT];
int squareNumbers[MAX_NUMBER_COUNT];

void swapSquare(int index1, int index2) {
	int order = squareOrders[index1];

	squareOrders[index1] = squareOrders[index2];
	squareOrders[index2] = order;
}

int getOrderIndex(int order) {
	for (int i = 0; i < squareCount; i++) {
		if (squareOrders[i] == order) {
			return i;
		}
	}

	return -1;
}

bool isCompleted() {
	for (int i = 0; i < squareCount; i++) {
		int orderIndex = getOrderIndex(i);

		int row = i / n;
		int col = i % n;
		int rightOrder = (col < n - 1) ? (row * n + col + 1) : -1;
		int downOrder = (row < n - 1) ? ((row + 1) * n + col) : -1;

		if (rightOrder > 0) {
			int rightIndex = getOrderIndex(rightOrder);
			if (squareNumbers[orderIndex * MAX_SQUARE_COUNT + 1] != squareNumbers[rightIndex * MAX_SQUARE_COUNT + 3]) {
				return false;
			}
		}

		if (downOrder > 0) {
			int downIndex = getOrderIndex(downOrder);
			if (squareNumbers[orderIndex * MAX_SQUARE_COUNT + 2] != squareNumbers[downIndex * MAX_SQUARE_COUNT]) {
				return false;
			}
		}
	}

	return true;
}

bool search(int orderIndex) {
	if (isCompleted()) {
		return true;
	}

	if (orderIndex >= squareCount) {
		return false;
	}

	for (int i = orderIndex + 1; i < squareCount; i++) {
		swapSquare(orderIndex, i);

		if (search(orderIndex + 1)) {
			return true;
		}

		swapSquare(orderIndex, i);
	}

	if (search(orderIndex + 1)) {
		return true;
	}

	return false;
}

int main() {
	int gameIndex = 0;

	while (cin >> n && n) {
		squareCount = n * n;
		numberCount = squareCount * SQUARE_NUMBER_COUNT;

		for (int i = 0; i < numberCount; i++) {
			cin >> squareNumbers[i];
		}

		for (int i = 0; i < squareCount; i++) {
			squareOrders[i] = i;
		}

		// cout
		gameIndex++;
		if (gameIndex > 1) {
			cout << endl;
		}

		cout << "Game " << gameIndex << ": ";
		cout << (search(0) ? "Possible" : "Impossible") << endl;
	}

	return 0;
}