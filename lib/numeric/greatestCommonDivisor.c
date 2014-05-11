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


/** 
 * Least Common Multiple algorithm
 */
int leastCommonMultiple(int a, int b)
{
	int gcd = greatestCommonDivisor(a, b);
	return (a / gcd) * b;
}
