/* @JUDGE_ID: 16232QS 1110 C */

#include <stdio.h>

int main()
{
	int n, m, y;
	int xn;
	int i, j;
	char found = 0;

	scanf("%d%d%d", &n, &m, &y);

	if (y < m) {
		for (i = 0; i < m; i++) {
			xn = 1;
			for (j = 1; j <= n; j++) {
				xn *= i;
				xn %= m;
			}
			if (xn == y) {
				if (found == 0) {
					printf("%d", i);
					found = 1;
				} else {
					printf(" %d", i);
				}
			}
		}
	}

	printf(found == 0 ? "-1\n" : "\n");

	return 0;
}
