#include <stdio.h>

int main()
{
	int t, n, i;

	scanf("%d", &t);

	for (i = 0; i < t; i++) {
		scanf("%d", &n);

		int numberOfZeros = 0;
		while (n != 0) {
			n /= 5;
			numberOfZeros += n;
		}

		printf("%d\n", numberOfZeros);
	}
	return 0;
}
