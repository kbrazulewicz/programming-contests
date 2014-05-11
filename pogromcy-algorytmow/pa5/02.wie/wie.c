#include <stdio.h>

#define MAX_S 20000

int main()
{
	int s, x;
	int i;
	int w, result = 0;

	scanf("%d%d", &s, &x);

	for (i = 0; i < s; i++) {
		scanf("%d", &w);

		result = (result * x + w) % 1000;
	}

	printf("%03d\n", abs(result));

	return 0;
}
