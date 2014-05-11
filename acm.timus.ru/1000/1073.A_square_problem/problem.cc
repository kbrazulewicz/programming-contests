/**
 * Lagrange's Four-Square Theorem
 * http://mathworld.wolfram.com/LagrangesFour-SquareTheorem.html
 */
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

static const int MAX_N = 60000;

// 4^k(8m + 7)

inline bool isSquare(int n)
{
	int nsqrt = sqrt(double(n));
	return nsqrt * nsqrt == n;
}

int getNumOfSquares(int n)
{
	int nsqrt = sqrt(double(n));

	if (isSquare(n)) return 1;

	for (int i = 1; i <= nsqrt; i++) {
		if (isSquare(n - i * i)) return 2;
	}

	while (n % 4 == 0) n /= 4;

	return n % 8 == 7 ? 4 : 3;
}

int main()
{
	int n;

	cin >> n;
	cout << getNumOfSquares(n) << endl;

	return 0;
}
