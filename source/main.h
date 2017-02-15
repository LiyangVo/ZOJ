#pragma once

#include <iostream>
#include <vector>

using namespace std;

struct PrimeItem {
	PrimeItem(int number, bool isUsed) : number(number), isUsed(isUsed) {}

	int number;
	bool isUsed;
};

vector<PrimeItem> primeList1;
vector<PrimeItem> primeList2;

vector<vector<int>> subLists1;
vector<vector<int>> subLists2;

void dividePrime(int number, vector<PrimeItem> * primeList) {
	int prime = 2;
	while (number != 1) {
		if (number % prime == 0) {
			number /= prime;
			primeList->push_back(PrimeItem(prime, false));
		}
		else {
			prime++;
		}
	}
}

void exhaustive(vector<PrimeItem> * primeList, vector<vector<int>> * subLists, int curNum, int curIndex) {
	// start
	if (curIndex > subLists->size()) {
		vector<int> vec;
		subLists->push_back(vec);
	}

	vector<int> * subList = &(subLists->at(curIndex));

	// loop
	bool isCasted = false;

	for (int i = 0; i < primeList->size(); i++) {
		PrimeItem item = primeList->at(i);
		if (!item.isUsed) {
			item.isUsed = true;
			exhaustive(primeList, subLists, curNum * item.number, isCasted ? (curIndex++) : curIndex);

			isCasted = true;
			item.isUsed = false;
		}
	}

	if (curNum != 1) {
		subList->push_back(curNum);

		exhaustive(primeList, subLists, 1, isCasted ? (curIndex++) : curIndex);
	}
}

void start() {

	int a, b;
	while (cin >> a >> b) {
		primeList1.clear();
		primeList2.clear();
		subLists1.clear();
		subLists2.clear();

		dividePrime(a, &primeList1);
		exhaustive(&primeList1, &subLists1, 1, 1);

		dividePrime(a, &primeList2);
		exhaustive(&primeList2, &subLists2, 1, 1);

		cout << a;
	}
}

int main() {
	start();

	return 0;
}
