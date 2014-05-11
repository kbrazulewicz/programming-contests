#include <stdio.h> 

#define  FIB_CALC_LENGTH 1000000
unsigned int fibCalc[FIB_CALC_LENGTH];

unsigned long long fib (unsigned int n, unsigned int m)
{
	unsigned long long a, b, c, r;

	if (n == 0) {
		r = 0;
	} else if (n < FIB_CALC_LENGTH && fibCalc[n]) {
		r = fibCalc[n];
	} else if (n % 4 == 1) {
		a = fib((n - 1) / 2, m);
		b = fib((n - 3) / 2, m);
		r = ((2 * a + b) % m) * ((2 * a - b + m) % m) + 2;
	} else if (n % 4 == 3) {
		a = fib((n - 1) / 2, m);
		b = fib((n - 3) / 2, m);
		r = ((2 * a + b) % m) * ((2 * a - b + m) % m) - 2;
	} else {
		a = fib(n / 2, m);
		b = fib((n - 2) / 2, m);
		r = a * ((a + 2 * b) % m);
	}

	if (n < FIB_CALC_LENGTH) {
		fibCalc[n] = r % m;
	}

	return r % m;
}


int main()
{
	int c;
	unsigned long long a, b, r;
	unsigned int n, m;


	scanf("%d", &c);

	while (c--) {
		memset(fibCalc, 0, sizeof(fibCalc));
		fibCalc[0] = 0;
		fibCalc[1] = 1;

		unsigned long long r;
		scanf("%Lu%Lu%u%u", &a, &b, &n, &m);

		r = fib(n + 1, m) * a + fib(n + 2, m) * b;
		printf("%u\n", r % m);
	}

	return 0;
}
