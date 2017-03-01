/***********************
Enigma Problem (1009) from ZOJ
By yangli.network@gmail.com @20170227
************************/

#include <iostream>

using namespace std;

const int MAX_LETER = 26;
const int MAX_CHARACTER = 1000;

int leterCount;
int rotorIndexs[3];
char rotors[3][MAX_LETER];

int cryptoCount;
char cryptograph[MAX_CHARACTER];

void decrypt() {
	int index = 0;

	while (index < MAX_CHARACTER && cryptograph[index] != 0) {
		char character = cryptograph[index++];

		for (int i = 2; i >= 0; i--) {
			char * rotor = rotors[i];
			int rotorIndex = rotorIndexs[i];

			for (int j = 0; j < leterCount; j++) {
				char plain = j + 'A';

				int cryptIndex = (j - rotorIndex + leterCount) % leterCount;
				char crypt = (rotor[cryptIndex] - ('A' + cryptIndex) + j + leterCount) % leterCount + 'A';

				if (crypt == character) {
					character = plain;
					break;
				}
			}
		}

		rotorIndexs[0]++;
		for (int i = 0; i < 3; i++) {
			if (rotorIndexs[i] == leterCount) {
				rotorIndexs[i] = 0;
				if (i < 2) {
					rotorIndexs[i + 1]++;
				}
			}
		}

		character = character - 'A' + 'a';
		cout << character;
	}

	cout << endl;
}

int main() {
	int index = 0;
	
	while (cin >> leterCount && leterCount) {
		cin >> rotors[0] >> rotors[1] >> rotors[2];

		// decrypto;
		if (++index > 1) {
			cout << endl;
		}
		cout << "Enigma " << index << ":" << endl;

		cin >> cryptoCount;
		for (int i = 0; i < cryptoCount; i++) {
			cin >> cryptograph;

			rotorIndexs[0] = rotorIndexs[1] = rotorIndexs[2] = 0;
			decrypt();
		}
	}

	return 0;
}