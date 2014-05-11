#include <stdio.h>

int main()
{
	int d, n;
	double t, a, r;

	scanf("%d", &d);

	while (d--) {
		scanf("%lf %d", &t, &n);
		r = 0;

		do {
			scanf("%lf", &a);
			r *= t;
			r += a;
		} while (n--);

		printf("%.3f\n", r);
	}

	return 0;
}
