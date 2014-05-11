/* @JUDGE_ID: 16232QS 1157 C++ */

#include <iostream>
using namespace std;

static const int MAX_X = 10000;

int divisors[MAX_X + 1];

int main()
{
	int m, n, k;

	cin >> m >> n >> k;

	divisors[1] = 1;
	for (int i = 2; i <= MAX_X; i++) 
	{
		divisors[i]++;
		for (int j = i * i; j <= MAX_X; j += i)
		{
			divisors[j]++;
		}
	}

	int l = 0;
	for (int i = k + 1; i <= MAX_X; i++) {
		if (divisors[i - k] == m && divisors[i] == n) {
			l = i;
			break;
		}
	}

	cout << l << endl;

	return 0;
}
