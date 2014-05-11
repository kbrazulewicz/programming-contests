/* @JUDGE_ID: 16232QS 1515 C++ */

#include <iostream>
#include <string>
using namespace std;


int main()
{
	int n, d;
	int maxSum = 0;
	int i;

	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> d;

		if (d > maxSum + 1) {
			break;
		}
		maxSum += d;
	}

	cout << maxSum + 1 << endl;

	return 0;
}
