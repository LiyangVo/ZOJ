/***********************
Gnome Tetravex (1008) from ZOJ
By yangli.network@gmail.com @20170228
************************/

#include <iostream>

using namespace std;

struct Square {
	int top;
	int right;
	int down;
	int left;

	int count;

	void set(int t, int r, int d, int l, int c) {
		top = t;
		right = r;
		down = d;
		left = l;
		count = c;
	}
	bool compare(int t, int r, int d, int l) {
		return top == t && right == r && down == d && left == l;
	}
};

int line;
int squareCount;
int fillSquareCount;
Square squares[25];
int fillSquares[25];

bool search(int index) {
	if (index >= fillSquareCount) {
		return true;
	}

	for (int i = 0; i < squareCount; i++) {
		if (squares[i].count > 0 && (index < line || squares[ fillSquares[index - line] ].down == squares[i].top) && (index % line == 0 || squares[ fillSquares[index - 1] ].right == squares[i].left) ) {
			squares[i].count--;
			fillSquares[index] = i;

			if (search(index + 1)) {
				return true;
			}

			squares[i].count++;
		}
	}

	return false;
}

int main() {
	int gameIndex = 0;
	int t, r, d, l;

	while (cin >> line && line) {
		fillSquareCount = line * line;
		squareCount = 0;

		// input
		for (int i = 0; i < fillSquareCount; i++) {
			cin >> t >> r >> d >> l;

			int j = 0;
			for (; j < squareCount; j++) {
				if (squares[j].compare(t, r, d, l)) {
					squares[j].count++;
					break;
				}
			}

			if (j >= squareCount) {
				squares[squareCount++].set(t, r, d, l, 1);
			}
		}

		// cout
		++gameIndex;
		if (gameIndex > 1) {
			cout << endl;
		}

		cout << "Game " << gameIndex << ": ";
		cout << (search(0) ? "Possible" : "Impossible") << endl;
	}

	return 0;
}