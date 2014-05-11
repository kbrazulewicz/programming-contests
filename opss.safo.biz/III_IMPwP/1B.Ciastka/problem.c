#include <stdio.h>

int main() 
{
	int d, n, c;
	int x, xd;

	int i, j;

	scanf("%d", &d);
	
	for (i = 0; i < d; i++) {
		scanf("%d", &n);
		for (j = 0, x = 0; j < n; j++) {
			scanf("%d", &xd);
			x += xd;
		}
		scanf("%d", &c);
		printf("%d\n", (x != 0) ? c % x : c);
	}

	return 0;
}
