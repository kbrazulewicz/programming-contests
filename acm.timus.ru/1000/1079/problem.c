/* @JUDGE_ID: 16232QS 1079 C */

#include <stdio.h>

#define MAX_N 100000
#define MAX(a, b) (a > b ? a : b)

int a[MAX_N];
int maxA[MAX_N];

int main()
{
	int i;
	int runningMax = 1;

	maxA[0] = a[0] = 0; 
	maxA[1] = a[1] = 1;
	for (i = 2; i < MAX_N; i++) {
		if (i & 0x00000001) {
			a[i] = a[i/2] + a[i/2 + 1];
		} else {
			a[i] = a[i/2];
		}
		runningMax = MAX(runningMax, a[i]);
		maxA[i] = runningMax;
	}

	int n; 
	scanf("%d", &n);
	do {
		printf("%d\n", maxA[n]);
		scanf("%d", &n);
	} while (n != 0);

	return 0;
}
