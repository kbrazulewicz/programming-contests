#include <stdio.h>

int main()
{
	int fib1 = 1, fib2 = 1, fib = 0;

	printf("%d\n%d\n", fib1, fib2);
	
	while (fib < 100000) {
		fib = fib1 + fib2;	
		fib1 = fib2;
		fib2 = fib;
		printf("%d\n", fib);
	}
	return 0;
}
