/* @JUDGE_ID: 16232QS 1100 C */

#include <stdio.h>

#define MAX_N 150000
#define MAX_M 100

int result[MAX_M + 1][MAX_N];
int resultIndex[MAX_M + 1];

int main()
{
	int n;
	int id, m;
	int i, j;

	scanf("%d", &n);
	for (i = 0; i < n; ++i) {
		scanf("%d%d", &id, &m);
		result[m][resultIndex[m]++] = id;
	}

	for (i = MAX_M; i >= 0; --i) {
		for (j = 0; j < resultIndex[i]; ++j) {
			printf("%d %d\n", result[i][j], i);
		}
	}

	return 0;
}
