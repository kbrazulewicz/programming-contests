#include <stdio.h>

int main()
{
#if 0
	int a, b, c;

	scanf("%d%d", &a, &b);
	c = 2 * (a / (b - a)) * b + (2 * (a % (b - a)) * b) / (b - a);
	printf("%d\n", c);
#else
	double a, b, c;

	scanf("%lf%lf", &a, &b);
	c = 2 * a * b / (b - a);
	printf("%d\n", (int)c);
#endif
	
	return 0;
}
