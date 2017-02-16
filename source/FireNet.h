/***********************
Fire Net Problem (1002) from ZOJ
By yangli.network@gmail.com @20170215
************************/

#include <iostream>
using namespace std;

////////////////////////////////////////////////
/* 
fisrt solution: 
1. list all result
2. pick legal results
This function will get the right result, but with more calculating needing.
Call startFireNet to start!
*/ 

bool isFireNetLegal(const int * map, int index, int maxSize) {
	if (index < 0 || index >= maxSize * maxSize || map[index] != 0) {
		return false;
	}

	int curRow = index / maxSize;
	int curCol = index % maxSize;

	for (int row = curRow - 1; row >= 0; row--) {
		int curIndex = row * maxSize + curCol;

		if (map[curIndex] == 1) {
			break;
		}
		else if (map[curIndex] == 2) {
			return false;
		}
	}

	for (int col = curCol - 1; col >= 0; col--) {
		int curIndex = curRow * maxSize + col;

		if (map[curIndex] == 1) {
			break;
		}
		else if (map[curIndex] == 2) {
			return false;
		}
	}

	return true;
}

int FireNet(int range, const int * defaultMap) {
	// map
	int mapSize = range * range;
	int * map = new int[mapSize];

	// using Binary to list all result
	int totalCount = 1;
	for (int i = 0; i < mapSize; i++) {
		if (defaultMap[i] == 0) {
			totalCount *= 2;
		}
	}

	// calculate
	int maxCount = 0;

	for (int i = 0; i < totalCount; i++) {
		int count = 0;

		for (int j = 0; j < mapSize; j++) {
			map[j] = defaultMap[j];
		}

		int index = 0;
		for (int j = 0; j < mapSize; j++) {
			if (map[j] == 0 && ((i & (1 << index++)) > 0)) {
				if (isFireNetLegal(map, j, range)) {
					map[j] = 2;
					count++;
				}
				else {
					break;
				}

			}
		}

		if (count > maxCount) {
			maxCount = count;
		}
	}

	// clean
	delete[] map;

	return maxCount;
}

void startFireNet()
{
	int * map = new int[100];
	int maxSize = 0;

	while (cin >> maxSize && maxSize) {
		char ch;
		for (int i = 0; i < maxSize * maxSize; i++) {
			cin >> ch;

			map[i] = ch != '.';
		}

		int count = FireNet(maxSize, map);

		cout << count << endl;
	}

	delete[] map;
}

////////////////////////////////////////////////
/* 
sencond solution:
using backtraching methods
This function will calculating faster.
Call startFireNet2 to start!
*/

bool isFireNetLegal2(char ** map, int x, int y, int range){
	// search row
	for (int row = x - 1; row >= 0; row--) {
		if (map[row][y] == 'X') {
			break;
		}
		else if (map[row][y] == 'O') {
			return false;
		}
	}

	// search column
	for (int col = y - 1; col >= 0; col--) {
		if (map[x][col] == 'X') {
			break;
		}
		else if (map[x][col] == 'O') {
			return false;
		}
	}

	return true;
}

void FireNetSearch2(char ** map, int index, int count, int range, int & maxCount) {
	if (index >= range * range) {
		if (maxCount < count) {
			maxCount = count;
		}

		return;
	}

	int x = index / range;
	int y = index % range;

	if (map[x][y] == '.' && isFireNetLegal2(map, x, y, range)) {
		// next search
		map[x][y] = 'O';
		FireNetSearch2(map, index + 1, count + 1, range, maxCount);

		// KEY !!!! »ØËÝ£¡£¡£¡
		map[x][y] = '.';
		FireNetSearch2(map, index + 1, count, range, maxCount);
	}
	else {
		// next step
		FireNetSearch2(map, index + 1, count, range, maxCount);
	}
}

void startFireNet2() {
	int range;

	while (cin >> range && range) {
		char ** map = new char *[range];
		for (int i = 0; i < range; i++) {
			map[i] = new char[range];

			for (int j = 0; j < range; j++) {
				cin >> map[i][j];
			}
		}

		int maxCount = 0;
		FireNetSearch2(map, 0, 0, range, maxCount);

		for (int i = 0; i < range; i++) {
			delete[] map[i];
		}
		delete[] map;

		cout << maxCount << endl;
	}
}

/////////////////////////////////////////////////////////////
// main

int main() {
	//startFireNet();
	//startFireNet2();

	return 0;
}