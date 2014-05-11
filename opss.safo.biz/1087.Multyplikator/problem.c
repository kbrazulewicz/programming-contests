#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

char line[4 + MAX_N * 5 + 1];


int calculate(int n, const char* input) 
{
	int j, a;
	double r = 0;
	const char *ib, *ie;

	ib = input;

	for (j = 0; j < n; j++) {
		a = strtol(ib, &ie, 10);
		ib = ie;

		if (a != 0) {
			r += log10(abs(a));
		} else {
			r = 0;
			break;
		}

	}

	return (int)(floor(r) + 1);
}


int main()
{
	int c, n, a, i, j;

	scanf("%d\n", &c);
	for (i = 0; i < c; i++) {
		scanf("%d\n", &n);
		fgets(line, sizeof(line), stdin);
		printf("%d\n", calculate(n, line));

	}
	return 0;
}
