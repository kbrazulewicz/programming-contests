/* @JUDGE_ID: 16232QS 1607 C */

#include <stdio.h>

int main()
{
	int a, b, c, d;
	int n, m;
	int r;

	scanf("%d%d%d%d", &a, &b, &c, &d);

	if (c <= a) {
		r = a;
	} else {
		n = (c - a) / (b + d);
		m = (c - a) % (b + d);
		if (m >= b) {
			r = a + (n + 1) * b;
		} else {
			r = c - n * d;
		}
	}

	printf("%d\n", r);

	return 0;
}
