#include <stdio.h>

int main()
{
	int n, k;
	int a, o, a1, o1;

	scanf("%d%d", &n, &k);

	a = k - 1; o = 0;

	while (n > 1) {
		a1 = a * k - o;
		o1 = a - o;

		a = a1;
		o = o1;
		n--;
	}

	printf("%d\n", a);

	return 0;
}
