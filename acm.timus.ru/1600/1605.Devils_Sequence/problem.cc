/* @JUDGE_ID: 16232QS 1605 C++ */

#include <iostream>
#include <string>
using namespace std;

int main()
{
	int n, r;

	cin >> n;

	r = (n / 10) * 3;

	n %= 10;
	if (n > 8) {
		r += 2;
	} else if (n > 4) {
		r += 1;
	}

	cout << r << endl;
	return 0;
}
