/* @JUDGE_ID: 16232QS 1083 C++ */

#include <iostream>
#include <string>

using namespace std;

int main()
{
	int n, k, m;
	unsigned int factorial;
	string exclamations;

	cin >> n >> exclamations;
	k = exclamations.length();

	m = n;
	factorial = 1;

	while (m > 0) {
		factorial *= m;
		m -= k;
	}

	cout << factorial << endl;
	
	return 0;
}
