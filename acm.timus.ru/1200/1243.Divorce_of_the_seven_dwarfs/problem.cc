/* @JUDGE_ID: 16232QS 1243 C++ */

#include <iostream>
using namespace std;

int main()
{
	int result = 0;
	char c;

	while (cin >> c) {
		if (c >= '0' && c <= '9') {
			result *= 10;
			result += c - '0';
			result %= 7;
		}
	}

	cout << result << endl;

	return 0;
}
