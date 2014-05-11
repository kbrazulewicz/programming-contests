/* @JUDGE_ID: 16232QS 1638 C */

#include <stdio.h>

int main()
{
	int t1, t2, i1, i2, r;

	scanf("%d%d%d%d", &t1, &t2, &i1, &i2);

	if (i2 > i1) {
		r = 2 * t2 + (i2 - i1 - 1) * (t1 + 2 * t2);
	} else {
		r = (i1 - i2 + 1) * t1 + (i1 - i2) * (2 * t2);
	}

	printf("%d\n", r);

	return 0;
}
