/***********************
Do the Untwist (1006) from ZOJ
By yangli.network@gmail.com @20170227
************************/

#include <iostream>

using namespace std;

const int MAX_CHAR_COUNT = 70;
const int MAX_CODE = 28;

char cipertext[MAX_CHAR_COUNT];
int plaincode[MAX_CHAR_COUNT];
int key;
int len;

char numberToChar(int number) {
	switch(number) {
		case 0:
			return '_';
		case 27:
			return '.';
		default:
			return number + 'a' - 1;
	}
}

int charToNumbaer(char ch) {
	switch (ch) {
		case '_':
			return 0;
		case '.':
			return 27;
		default:
			return ch - 'a' + 1;
	}
}

int main() {
	while (cin >> key && key) {
		cin >> cipertext;

		// lenght
		len = 0;
		while (cipertext[len]) {len++;}

		// untwist
		for (int i = 0; i < len; i++) {
			int plainIndex = (key * i) % len;

			plaincode[plainIndex] = (charToNumbaer(cipertext[i]) + i) % MAX_CODE;
		}

		// cout
		for (int i = 0; i < len; i++) {
			cout << numberToChar(plaincode[i]);
		}
		cout << endl;
	}

	return 0;
}