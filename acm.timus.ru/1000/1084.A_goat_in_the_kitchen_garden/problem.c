/* @JUDGE_ID: 16232QS 1084 C */
#include <math.h>
#include <stdio.h>

#define M_PI	3.14159265358979323846	/* pi */
#define M_SQRT2	1.41421356237309504880	/* sqrt(2) */

int main()
{
	double g, r, d, x, field;

	scanf("%lf %lf", &g, &r);
	d = g / 2;


	if (d * M_SQRT2 < r) {
		field = g * g;
	} else if (d < r) {
		x = r * r * acos(d / r) - d * sqrt(r * r - d * d);
		field = M_PI * r * r - 4 * x;
	} else {
		field = M_PI * r * r;
	}

	printf("%.3f\n", field);

	return 0;
}
