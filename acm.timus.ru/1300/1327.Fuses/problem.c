/* @JUDGE_ID: 16232QS 1327 C */

#include <stdio.h>

int main()
{
	int a, b;

	scanf("%d %d", &a, &b);

	if (a % 2 == 0) a++;
	if (b % 2 == 0) b--;

	printf("%d\n", (b - a) / 2 + 1);
	
	return 0;
}
