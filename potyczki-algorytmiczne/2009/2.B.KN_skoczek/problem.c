#include <stdio.h>
#include <stdlib.h>

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

int canReach(int k, int n, int x, int y)
{
	if (k == 0) {
		return (x % n == 0) && (y % n == 0);
	} else if (n == 0) {
		return (x % k == 0) && (y % k == 0);
	} else {
		int gcd = greatestCommonDivisor(k, n);

		x %= 2 * gcd; y %= 2 * gcd;
		k /= gcd; n /= gcd;

		if (x == 0 && y == 0) {
			return 1;
		}

		if ((k % 2 == 1) && (n % 2 == 1)) {
			return (x == gcd && y == gcd);
		}

		return (x % gcd == 0) && (y % gcd == 0);
	}
}

int main()
{
	int t, i;
	int k, n, x1, y1, x2, y2;

	scanf("%d", &t);

	for (i = 0; i < t; i++) 
	{
		scanf("%d%d%d%d%d%d", &k, &n, &x1, &y1, &x2, &y2);

		printf("%s\n", canReach(k, n, abs(x1 - x2), abs(y1- y2)) == 0 ? "NIE" : "TAK");
	}

	return 0;
}
