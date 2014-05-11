/* @JUDGE_ID: 16232QS 1582 C++ */

#include <cmath>
#include <iostream>
using namespace std;

int main()
{
	double k1, k2, k3;

	cin >> k1 >> k2 >> k3;

	cout << (int)(1000 * k1 * k2 * k3 / (k1 * k2 + k2 * k3 + k3 * k1) + 0.5) << endl;

	return 0;
}
