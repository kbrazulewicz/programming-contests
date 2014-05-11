/* @JUDGE_ID: 16232QS 1636 C */

#include <stdio.h>

int main()
{
	int t1, t2, n, p = 0, i;

	scanf("%d%d", &t1, &t2);
	for (i = 0; i < 10; i++) 
	{
		scanf("%d", &n);
		p += n * 20;
	}

	printf("%s\n", t2 - t1 - p >= 0 ? "No chance." : "Dirty debug :(");

	return 0;
}
