/* @JUDGE_ID: 16232QS 1200 C++ */

#include <cmath>
#include <iostream>
using namespace std;

static const int MAX_K = 10000;

pair<int, int> calculate(double a, double b, int k)
{
	pair<int, int> result;

	int optX = a > 0 ? (a + 0.999) / 2 : 0;
	int optY = b > 0 ? (b + 0.999) / 2 : 0;

	while (optX + optY > k) {
		double gX = a - 2 * optX + 1;
		double gY = b - 2 * optY + 1;

		if (optX == 0) {
			optY--;
		} else if (optY == 0) {
			optX--;
		} else if (gX > gY) {
			optY--;
		} else {
			optX--;
		}
	}

	result = make_pair(optX, optY);

	return result;
}

int main()
{
	double a, b, p = 0.0;
	int k;

	cin >> a >> b >> k;

	pair<int, int> result = calculate(a, b, k);

	if (result.first != 0) {
		p += a * result.first - result.first * result.first;
	}
	if (result.second != 0) {
		p += b * result.second - result.second * result.second;
	}

	printf("%.2f\n%d %d\n", p, result.first, result.second);

	return 0;
}
