#include <stdio.h>

#define MAX(a,b) (a) > (b) ? (a) : (b)
#define MIN(a,b) (a) < (b) ? (a) : (b)

int simplify(int m, int n)
{
	int r[3][3] = {
		{2, 2, 2},
		{2, 1, 1},
		{2, 1, 1},
	};

	int x = MIN(m, n);
	int y = MAX(m, n);
	if (x == 1) return y / 2 + y % 2;

	return r[m % 3][n % 3];
}

int main()
{
	int m, n;
	scanf("%d %d", &m, &n);
	printf("%d\n", simplify(m, n));
	return 0;
}
