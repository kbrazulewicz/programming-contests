/* @JUDGE_ID: 16232QS 1658 C */

#include <stdio.h>

int helper[10] = { 
	0, 0, 1 * 2, 2 * 3, 3 * 4, 4 * 5,
	5 * 6, 6 * 7, 7 * 8, 8 * 9
}

#define MAX_OUTPUT 100
char output[MAX_OUTPUT + 1];

void resolve(int s1, int s2)
{
	int d = 9;
	if (s1 > s2) {
		printf("No solution\n");
		return;
	}

	memset(output, sizeof(output), 0);
	char *o = output[MAX_OUTPUT - 1];

	while (1) {
		if (s1 != s2) {
			if (s2 - s1 > helper[d]) {
			} else {
				while (s2 - s1 < helper[--d]);
			}

			int n = (s2 - s1) / helper[d];
		}
	}

}

int main()
{
	int t, s1, s2;

	scanf("%d", &t);

	while (t--) {
		scanf("%d%d", &s1, &s2);
		resolve(s1, s2);
	}

	return 0;
}
