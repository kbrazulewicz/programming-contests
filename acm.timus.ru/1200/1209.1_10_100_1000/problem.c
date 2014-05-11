/* @JUDGE_ID: 16232QS 1209 C */

#include <math.h>
#include <stdio.h>

int main()
{
	int i, n, k;
	double k1;
	int k2;

	scanf("%d\n", &n);

	for (i = 0; i < n; i++) {
		scanf("%d\n", &k);

		k1 = k;
		k1 = sqrt(8 * k1 - 7);
		k2 = (int) k1;

		if (k1 == floor(k1) && k2 % 2) {
			putchar('1');
		} else {
			putchar('0');
		}
		putchar(' ');
	}
	putchar('\n');
	return 0;
}
