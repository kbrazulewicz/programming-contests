/* @JUDGE_ID: 16232QS 1506 C */

#include <stdio.h>

#define MAX_N 100

int values[MAX_N + 1];

int main()
{
	int n, k, h, o, i, j;

	scanf("%d%d", &n, &k);
	for (i = 0; i < n; i++) {
		scanf("%d", &values[i]);
	}

	if (n % k == 0) {
		h = n / k;
	} else {
		h = n / k + 1;
	}

	for (i = 0; i < h; i++) {
		for (j = 0; j < k; j++) {
			o = j * h + i;
			if (o < n) {
				printf("%4d", values[o]);
			}
		}
		printf("\n");
	}
	return 0;
}
