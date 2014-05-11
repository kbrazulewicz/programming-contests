/* @JUDGE_ID: 16232QS 1502 C */

#include <iostream>
using namespace std;

int main()
{
	int n, i;
	uint64_t r = 0L;

	cin >> n;

	for (i = 0; i <= n; i++) {
		r += (3 * i * (i + 1)) / 2;
	}

	cout << r << endl;

	return 0;
}
