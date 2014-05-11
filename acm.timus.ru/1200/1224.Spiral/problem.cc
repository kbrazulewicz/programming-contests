/* @JUDGE_ID: 16232QS 1224 C++ */

#include <iostream>
#include <string>
using namespace std;

int main()
{
	int n, m;

	cin >> n >> m;

	int a = min(n, m);

	unsigned int r = n > m ? 1 : 0;

	if (a != 1) {
		r += (a - 1) * 2;
	}

	cout << r << endl;

	return 0;
}
