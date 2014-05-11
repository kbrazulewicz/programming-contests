#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n;

	scanf("%d", &n);
	printf("%d\n", ((1 + n) * (abs(n - 1) + 1)) / 2);
	return 0;
}
