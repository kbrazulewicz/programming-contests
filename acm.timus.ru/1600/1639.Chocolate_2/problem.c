/* @JUDGE_ID: 16232QS 1639 C */

#include <stdio.h>

int main()
{
	int m, n, cuts;

	scanf("%d%d", &m, &n);

	cuts = (n - 1) + n * (m - 1);

	printf("%s\n", cuts % 2 ? "[:=[first]" : "[second]=:]");

	return 0;
}
