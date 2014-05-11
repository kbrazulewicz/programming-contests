/* @JUDGE_ID: 16232QS 1214 C++ */

#include <iostream>
using namespace std;

int main()
{
	int x, y;

	cin >> x >> y;

	if (x > 0 && y > 0 && (x + y) % 2 == 1) {
		swap(x, y);
	}

	cout << x << " " << y << endl;

	return 0;
}
