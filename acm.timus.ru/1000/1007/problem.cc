/* @JUDGE_ID: 16232QS 1007 C++ */

#include <iostream>
#include <string>

using namespace std;

void analyze(string& aWord, int aLength)
{
	int sum = 0;
	int len = aWord.length();

	for (int i = 0, v = len; v > 0; i++, v--) {
		if (aWord[i] == '1') {
			sum += v;
		}
	}

	int modLimit = aLength + 1;
	int mod = sum % modLimit;

	if (len == aLength && mod == 0) return;

	if (len == aLength) {
		aWord[len - mod] = '0';
		return;
	}

	if (len < aLength) {
		if (mod == 0) {
			aWord = string("0") + aWord;
		} else if (mod == 1) {
			aWord = string("1") + aWord;
		} else {
			int numberOfOnes = 0;
			for (int i = 0; i < len; i++) {
				if (aWord[i] == '1') numberOfOnes++;

				if (numberOfOnes % modLimit == modLimit - mod) {
					aWord.insert(aWord.begin() + i + 1, '0');
					return;
				} else if ((numberOfOnes + len - i) % modLimit == modLimit - mod) {
					aWord.insert(aWord.begin() + i + 1, '1');
					return;
				}
			}
		}
		return;
	} else {
		int numberOfOnes = 0;
		for (int i = 0; i < len; i++) {
			int removeValue = numberOfOnes + (len - i) * (aWord[i] - '0');
			if (removeValue % (aLength + 1) == mod) {
				aWord.erase(aWord.begin() + i);
				return;
			}
			if (aWord[i] == '1') numberOfOnes++;
		}
	}
}

int main()
{
	int wordLength;
	string dataWord;

	cin >> wordLength;
	cin >> dataWord;

	do {
		analyze(dataWord, wordLength);
		cout << dataWord << endl;
		cin >> dataWord;
	} while (cin);
	
	return 0;
}
