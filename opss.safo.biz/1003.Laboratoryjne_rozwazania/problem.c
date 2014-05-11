#include <stdio.h>

int main()
{
	int c, n, i, j, x, s;

	scanf("%d", &c);
	for(i = 0; i < c; i++) {
		scanf("%d", &n);

		s = 0;
		for(j = 0; j < n; j++) {
			scanf("%d", &x);
			s += x;
		}
		printf("%d\n", s);
	}
	return 0;
}
