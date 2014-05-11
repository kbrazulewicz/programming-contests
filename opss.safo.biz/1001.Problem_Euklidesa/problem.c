#include <stdio.h>
#include <stdlib.h>

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
	int n, a, b;
	int i;

	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d %d", &a, &b);
		printf("%d\n", greatestCommonDivisor(a, b));
	}
	
	return 0;
}
