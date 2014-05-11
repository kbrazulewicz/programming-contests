/* @JUDGE_ID: 16232QS 1139 C++ */

#include <iostream>
using namespace std;

/**
 * Greatest Common Divisor Euclidean algorithm
 *
 * O(n) complexity (n is the number of digits in the input)
 *
 * needs:
 * #include <stdlib.h>
 */
int greatestCommonDivisor(int a, int b)
{
	int tmp;
	while (b != 0) {
		tmp = a % b;
		a = b;
		b = tmp;
	}

	return abs(a);
}


int main()
{
	int n, m;

	cin >> n >> m;
	n--; m--;

	int gcd = greatestCommonDivisor(n, m);
	if (gcd == 1) {
		cout << m + n - 1 << endl;
	} else {
		cout << (m / gcd + n / gcd - 1) * gcd << endl;
	}

	return 0;
}
