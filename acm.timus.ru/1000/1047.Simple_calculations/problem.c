/* @JUDGE_ID: 16232QS 1047 C */

#include <stdio.h>

int main()
{
	int n, i;
	double a0, aN1, cN;
	double a1;

	scanf("%d%lf%lf", &n, &a0, &aN1);

	a1 = n * a0 + aN1;

	for (i = 1; i <= n; i++) {
		scanf("%lf", &cN);
		a1 -= 2 * (n + 1 - i) * cN;
	}

	a1 /= (n + 1);

	printf("%.2f\n", a1);
	
	return 0;
}
