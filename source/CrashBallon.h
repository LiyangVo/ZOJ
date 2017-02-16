/***********************
Crashing Ballon Problem (1003) from ZOJ
By yangli.network@gmail.com @20170215
************************/

#include <iostream>
#include <vector>

using namespace std;


///////////////////////////////////////
/* 
1. devide both number to primes
2. list all valiable result by premuting and combining primes
3. compare result
*/

struct PrimeItem {
	PrimeItem(int number, int count) : number(number), count(count) {}

	int number;
	int count;
};

bool isNumInVector(vector<int> * list, int number) {
	for (unsigned i = 0; i < list->size(); i++) {
		if (list->at(i) == number) {
			return true;
		}
	}

	return false;
}

bool isAllItemUsed(vector<PrimeItem> * list) {
	for (unsigned i = 0; i < list->size(); i++) {
		if (list->at(i).count > 0) {
			return false;
		}
	}

	return true;
}

void dividePrime(int number, vector<PrimeItem> * primeList) {
	int prime = 2;
	bool isNew = true;

	while (number != 1) {
		if (number % prime == 0) {
			number /= prime;

			if (isNew) {
				primeList->push_back(PrimeItem(prime, 1));
				isNew = false;
			}
			else {
				primeList->at(primeList->size() - 1).count++;
			}
		}
		else {
			prime++;
			isNew = true;
		}
	}
}

void exhaustive(vector<PrimeItem> * primeList, vector< vector<int> > * subLists, int curNum, int curIndex) {
	// start
	if (curIndex == -1) {
		curIndex = int(subLists->size());

		vector<int> vec;
		subLists->push_back(vec);
	}

	// end
	if (curNum > 100) {
		return;
	}

	vector<int> * subList = &(subLists->at(curIndex));
	if (isAllItemUsed(primeList) && !isNumInVector(subList, curNum)) {
		subList->push_back(curNum);
		
		return;
	}

	// loop
	bool isCasted = false;

	if (curNum > 1 && !isNumInVector(subList, curNum)) {
		subList->push_back(curNum);
		exhaustive(primeList, subLists, 1, curIndex);

		isCasted = true;
	}

	for (unsigned i = 0; i < primeList->size(); i++) {
		PrimeItem * item = &primeList->at(i);
		if (item->count > 0) {
			if (curNum * item->number <= 100) {
				item->count--;
				exhaustive(primeList, subLists, curNum * item->number, isCasted ? -1 : curIndex);

				item->count++;
				isCasted = true;
			}
		}
	}
}

void resetSubLists(vector< vector<int> > * subLists, int totalNum) {
	unsigned index = 0;

	while (index < subLists->size()) {
		vector<int> * subList = &(subLists->at(index));

		int total = 1;
		for (unsigned i = 0; i < subList->size(); i++) {
			total *= subList->at(i);
		}

		if (total == totalNum) {
			index++;
		}
		else {
			subLists->erase(subLists->begin() + index);
		}
	}
}

bool isListHasSame(vector<int> * subList1, vector<int> * subList2) {
	for (unsigned i = 0; i < subList1->size(); i++) {
		for (unsigned j = 0; j < subList2->size(); j++) {
			if (subList1->at(i) == subList2->at(j)) {
				return true;
			}
		}
	}

	return false;
}

void start() {
	int a, b;
	while (cin >> a >> b) {
		if (a < b) {
			int c = a;
			a = b;
			b = c;
		}

		vector<PrimeItem> primeList1;
		vector<PrimeItem> primeList2;

		vector< vector<int> > subLists1;
		vector< vector<int> > subLists2;

		dividePrime(a, &primeList1);
		exhaustive(&primeList1, &subLists1, 1, -1);
		resetSubLists(&subLists1, a);

		dividePrime(b, &primeList2);
		exhaustive(&primeList2, &subLists2, 1, -1);
		resetSubLists(&subLists2, b);

		if (subLists2.size() == 0) {
			cout << a << endl;
		}
		else if(subLists1.size() == 0) {
			cout << b << endl;
		}
		else {
			bool isLegal = false;

			for (unsigned i = 0; i < subLists1.size() && !isLegal; i++) {
				for (unsigned j = 0; j < subLists2.size() && !isLegal; j++) {
					if (!isListHasSame(&subLists1.at(i), &subLists2.at(j))) {
						isLegal = true;
					}
				}
			}

			if (isLegal) {
				cout << a << endl;
			}
			else {
				cout << b << endl;
			}
		}
	}
}

/////////////////////////////////////////////////////////////
// main

int main() {
	start();

	return 0;
}
