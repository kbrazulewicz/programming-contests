/* @JUDGE_ID: 16232QS 1001 C */

#include <math.h>
#include <stdio.h>

double rootArray[0x20000];
char input[0x40000 + 1];

int main()
{
	int rootCount = -1;

	while (scanf("%lf", &rootArray[++rootCount]) != EOF);

	while (--rootCount >= 0) {
		printf("%.4f\n", sqrt(rootArray[rootCount]));
	}

	return 0;
}
