/* @JUDGE_ID: 16232QS 1573 C++ */

#include <iostream>
#include <string>
using namespace std;

int main()
{
	int b, r, y, k;
	int result = 1;
	string color;

	cin >> b >> r >> y >> k;
	while (k--) {
		cin >> color;
		if (color == "Blue") {
			result *= b;
		} else if (color == "Red") {
			result *= r;
		} else if (color == "Yellow") {
			result *= y;
		}
	}

	cout << result << endl;

	return 0;
}
