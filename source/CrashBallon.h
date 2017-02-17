/***********************
Crashing Ballon Problem (1003) from ZOJ
By yangli.network@gmail.com @20170215
************************/

#include <iostream>
#include <vector>

using namespace std;

/////////////////////////////////////////////////////////////
/*
solution 1: a better way of solution 1
*/

const int MAX_NUMBER = 100;
int _usedBallons[MAX_NUMBER + 1];

int tryFactor(int number, int factor) {
	if (factor > MAX_NUMBER || factor > number) {
		return 0;
	}
	else if (_usedBallons[factor] || number % factor != 0) {
		return tryFactor(number, factor + 1);
	}
	else {
		return factor;
	}
}

bool isFactorable(int number, int factor) {
	if (number == 1) {
		return true;
	}
	else if (factor > MAX_NUMBER || factor > number) {
		return false;
	} 

	factor = tryFactor(number, factor);
	if (factor == 0) {
		return false;
	}

	if (isFactorable(number / factor, factor + 1)) {
		return true;
	}

	return isFactorable(number, factor + 1);
}

bool isResultRight(int numA, int numB, int factor) {
	if (numA == 1) {
		return isFactorable(numB, 1);
	}
	else if (factor > MAX_NUMBER || factor > numA) {
		return false;
	}

	factor = tryFactor(numA, factor);
	if (factor == 0) {
		return false;
	}

	_usedBallons[factor] = true;
	if (isResultRight(numA / factor, numB, factor + 1)) {
		return true;
	}
	
	_usedBallons[factor] = false;
	return isResultRight(numA, numB, factor + 1);
}

void startSolution() {
	int maxNum, minNum;
	while (cin >> maxNum >> minNum) {
		if (maxNum < minNum) {
			swap(maxNum, minNum);
		}

		// reset ballon
		for (int i = 0; i < MAX_NUMBER + 1; i++) {
			_usedBallons[i] = false;
		}

		// not have the change to challange
		if (!isFactorable(minNum, 1)) {
			cout << maxNum << endl;
		}
		else {
			cout << (isResultRight(maxNum, minNum, 1) ? maxNum : minNum) << endl;
		}
	}
}

/////////////////////////////////////////////////////////////
/* 
solution 2: 
1. try to devide given numbers by number from 100 to 2
this solution can pass the test, but I do not think it is right.
Ex: The anwer is 86 * 43 * 48, but the solution test 96 * 43 * 43 which can not pass the test.
*/

int check_low(int m, int w)
{
	for (int i = w; i >= 2; --i)
	{
		if (m%i == 0)
		{
			if ((m /= i) == 1)
			{
				return 1;
			}
		}
	}
	return m == 1;
}

int check_high(int n, int m, int w)
{
	if (1 == n && 1 == m){ return 1; }
	if (0 == w){ return 0; }
	return ((0 == n%w) && check_high(n / w, m, w - 1))
		|| ((0 == m%w) && check_high(n, m / w, w - 1)) || (check_high(n, m, w - 1));
}

int solve(int n, int m)
{
	return (check_low(m, 100) && !check_high(n, m, 100)) ? m : n;
}

void startSolution2() {
	int n, m;
	while (cin >> n >> m)
	{
		if (n < m){
			n ^= m; m ^= n; n ^= m;
		}
		cout << solve(n, m) << endl;
	}
}

///////////////////////////////////////
/*old one:
This is not good and all, and not right.
I can not find the bug.
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

		if (a <= 100) {
			vector<int> vec;
			vec.push_back(a);
			subLists1.push_back(vec);
		}
		if (b <= 100) {
			vector<int> vec;
			vec.push_back(b);
			subLists2.push_back(vec);
		}

		// not challage
		if (subLists2.size() == 0) {
			cout << a << endl;
		}
		// challage
		else if (subLists1.size() == 0) {
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
	startSolution();

	return 0;
}
