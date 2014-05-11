#include <stdio.h>

int reverseNumber(int value)
{
	int r = 0;

	while (value) {
		r *= 10;
		r += value % 10;
		value /= 10;
	}

	return r;
}


int main() 
{
	int n, a, b;

	scanf("%d", &n);

	while (n--) {
		scanf("%d %d", &a, &b);

		printf("%d\n", reverseNumber(reverseNumber(a) + reverseNumber(b)));

	}

	return 0;
}
