#include <math.h>
#include <stdio.h>

int calculate(long double a, long double b, long double c)
{
	long double k, z, r;

	k = tanl(M_PI_2 / a * c);
	z = (-1 + sqrt(1 + 4 * k * k)) / (2 * k);
	r = (2 * a) / M_PI * asinl(z);

	return (int) (r + 0.5);
}

int main()
{
	int n, i;
	int a, b, c, r;

	scanf("%d", &n);
	for (i = 0; i < n ; i++) {
		scanf("%d%d%d", &a, &b, &c);
		a *= 1760 * 3 * 12;
		b *= 1760 * 3 * 12;
		c *= 1760 * 3 * 12;
		r = calculate(a, b, c);
		{
			int m, j, s, c;
			c = r % 12;
			s = (r / 12) % 3;
			j = (r / 12 / 3) % 1760;
			m = r / 12 / 3 / 1760;

			printf("%d %d %d %d\n", m, j, s, c);
		}
	}
	return 0;
}
