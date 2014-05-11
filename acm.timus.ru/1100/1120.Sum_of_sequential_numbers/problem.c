/* @JUDGE_ID: 16232QS 1120 C */

#include <math.h>
#include <stdio.h>

int main()
{
	unsigned int n;
	unsigned int a, p;

	scanf("%u", &n);
	p = sqrt(2 * n);


	while (p > 0) {
		a = (2 * n - p * p + p) / (2 * p);
		if ((2 * a + p - 1) * p == 2 * n) {
			break;
		}
		p--;
	}

	printf("%u %u\n", a, p);

	return 0;
}
