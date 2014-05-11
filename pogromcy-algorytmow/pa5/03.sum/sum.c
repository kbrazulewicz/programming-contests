#include <math.h>
#include <stdio.h>

int main()
{
	unsigned long long n, s = 0, l;
	unsigned long long i;

	scanf("%llu", &n);

	l = sqrt(n);

	for (i = 1; i <= l; i++) {
		s += n / i;
	}
	s <<= 1;
	s -= (l * l);

	printf("%llu\n", s);

	return 0;
}
