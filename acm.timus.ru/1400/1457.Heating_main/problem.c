/* @JUDGE_ID: 16232QS 1457 C */

#include <stdio.h>

int main()
{
	int n, i, p, pSum = 0;

	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &p);
		pSum += p;
	}

	printf("%.6f\n", (double) pSum / n);

	return 0;
}
