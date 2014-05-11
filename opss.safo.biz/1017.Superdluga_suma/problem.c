#include <stdio.h>

int main()
{
	int n, a, b, c;
	int p, c9 = 0;

	scanf("%d\n", &n);

	scanf("%d%d\n", &a, &b);
	p = a + b;
	n--;

	while (n--) {
		scanf("%d%d\n", &a, &b);
		c = a + b;

		if (c > 9) {
			putchar('0' + p + 1);
			while (c9--) putchar('0');
			p = c - 10; c9 = 0;
		} else if (c < 9) {
			putchar('0' + p);
			while (c9--) putchar('9');
			p = c; c9 = 0;
		} else {
			c9++;
		}
	}
	putchar('0' + p);
	while (c9--) putchar('9');
	putchar('\n');

	return 0;
}
