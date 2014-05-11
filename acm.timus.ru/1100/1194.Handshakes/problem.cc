/* @JUDGE_ID: 16232QS 1194 C++ */

#include <iostream>
#include <string>
using namespace std;

int main()
{
	int n, k;

	cin >> n >> k;

	cout << n * (n - 1) / 2 - k << endl;

	return 0;
}
