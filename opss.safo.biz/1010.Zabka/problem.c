#include <stdio.h>

#define MAX_N 1000

int frog[MAX_N + 1];

int calculate(int n, int kMin, int kMax)
{
	memset(frog, 0, sizeof(frog));

	frog[1] = 1;

	for (int i = kMin; i <= kMax; i++) {
		for (int j = 1; j <= n - i; j++) {
			frog[j + i] += frog[j];
		}
	}

	return frog[n];
}

int main()
{
	int m, n, kMin, kMax;

	scanf("%d", &m);

	while (m--) {
		scanf("%d%d%d", &n, &kMin, &kMax);
		printf("%d\n", calculate(n, kMin, kMax));
	}

	return 0;
}
