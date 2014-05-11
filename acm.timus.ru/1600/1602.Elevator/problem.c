/* @JUDGE_ID: 16232QS 1602 C */

#include <stdio.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))

int bruteForce(int n, int k, double u, double v)
{
	double t, tMin;
	int r, x;

	tMin = (n - 1) * u;
	r = 1;
	x = n;

	while (x > 1) {
		t = MAX((n - x) * u, (k - 1) * v + 15) + 2 * (x - 1) * v + 5;
		if (t < tMin) {
			tMin = t;
			r = x;
		}
		x--;
	}

	return r;
}

int smartAss(int n, int k, double u, double v)
{
	double t, tMin;
	int r, x;

	if ((n - 1) * u <= (k - 1) * v + 15 + 5) {
		return 1;
	} else {
		return bruteForce(n, k, u, v);
	}
}

int main()
{
	int n, k, r;
	double u, v;

	scanf("%d %d %lf %lf", &n, &k, &u, &v);

	r = smartAss(n, k, u, v);

	printf("%d\n", r);

	return 0;
}
