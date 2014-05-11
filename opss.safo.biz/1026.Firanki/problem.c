#include <stdio.h>

unsigned int firanka(unsigned int n)
{
	unsigned int x = 2;

	while (x < n) {
		x <<= 1;
	}

	return n - (x >> 1) - 1;
}

int main()
{
	unsigned int d, n;

	scanf("%u", &d);
	while (d--) {
		scanf("%u", &n);
		printf("%u\n", firanka(n));
	}
	return 0;
}
