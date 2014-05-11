/* @JUDGE_ID: 16232QS 1131 C++ */

#include <iostream>
using namespace std;

int main()
{
	int n, k;
	int computersInfected = 1;
	int timePassed = 0;
	cin >> n >> k;

	while (computersInfected < n) {
		if (computersInfected < k) {
			computersInfected *= 2;
			timePassed++;
		} else {
			int computersLeft = n - computersInfected;
			timePassed += (computersLeft + k - 1) / k;
			computersInfected = n;
		}
	}

	cout << timePassed << endl;
	return 0;
}
