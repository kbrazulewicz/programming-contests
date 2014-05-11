/**
 * http://www.research.att.com/~njas/sequences/A001835
 *
 * Ways of packing a 3 X 2(n-1) rectangle with dominoes.
 * a(n) = 4a(n-1) - a(n-2).
 */
#include <iostream>
#include <string>
using namespace std;

static const int aLimit = 1000000;
unsigned int a[(100000 + 2) / 2 + 1];
int aMax = 0;

unsigned int calculate(int n)
{
	int r;

	n = (n + 2) / 2;

	for (; aMax <= n; aMax++) {
		r = ((4 * a[aMax - 1]) % aLimit) - a[aMax - 2];
		if (r < 0) {
			r += aLimit;
		}
		a[aMax] = r;
	}

	return a[n];
}

int main()
{
	int c, n;

	a[0] = a[1] = 1;
	aMax = 2;

	cin >> c;
	while (c--) {
		cin >> n;
		if (n % 2) {
			cout << 0 << endl;
		} else {
			cout << calculate(n) << endl;
		}
	}

	return 0;
}
