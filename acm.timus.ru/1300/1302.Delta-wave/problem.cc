/* @JUDGE_ID: 16232QS 1302 C++ */

#include <cmath>
#include <iostream>
using namespace std;

int calculate(int m, int n)
{
	if (m > n) swap(m, n);

	int mL = sqrt((double)m - 1), nL = sqrt((double)n - 1);
	int mP = m - 1 - mL * mL;
	int nP = n - 1 - nL * nL;

	if (nL == mL) {
		return nP - mP;
	} 

	int d = 2 * (nL - mL);
	int l = mP - (mP % 2);
	int r = mP + (mP % 2) + d;

	int adj[2][2] = {{0, -1}, {1, 0}};

	if (l <= nP && nP <= r) {
		d += adj[mP % 2][nP % 2];
	} else {
		d += adj[mP % 2][0];
		if (nP < l) {
			d += l - nP;
		} else if (r < nP) {
			d += nP - r;
		}
	}

	return d;
}

int main()
{
	int m, n;

	cin >> m >> n;

	cout << calculate(m, n) << endl;

	return 0;
}
