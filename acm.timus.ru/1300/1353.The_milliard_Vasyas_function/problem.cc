/* @JUDGE_ID: 16232QS 1353 C++ */

#include <iostream>
#include <string>
using namespace std;

static const int MAX_SUM = 81;

int T[10][MAX_SUM + 1];
int S[MAX_SUM + 1];

void precalculate()
{
	for (int i = 0; i <= 9; T[1][i++] = 1);

	for (int numberOfDigits = 2; numberOfDigits <= 9; numberOfDigits++) {
		for (int expectedSum = 1; expectedSum <= MAX_SUM; expectedSum++) {
			for (int firstDigit = 1; firstDigit <= min(expectedSum, 9); firstDigit++) {
				for (int i = 1; i < numberOfDigits; i++) {
					T[numberOfDigits][expectedSum] += T[numberOfDigits - i][expectedSum - firstDigit];
				}
			}
		}
	}

	S[1] = 1;
	for (int expectedSum = 1; expectedSum <= MAX_SUM; expectedSum++) {
		for (int numberOfDigits = 1; numberOfDigits <= 9; numberOfDigits++) {
			S[expectedSum] += T[numberOfDigits][expectedSum];
		}
	}
}


int main()
{
	int s;

	precalculate();

	cin >> s;

	cout << S[s] << endl;

	return 0;
}
