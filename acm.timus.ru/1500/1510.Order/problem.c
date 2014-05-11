/* @JUDGE_ID: 16232QS 1510 C */

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500000
int notes[MAX_N + 1];

int qsort_int(const void* a, const void* b) {
	return *((int*) a) - *((int*) b);
}

int main()
{
	int n, i;

	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &notes[i]);
	}

	qsort(notes, n, sizeof(notes[0]), qsort_int);

	printf("%d\n", notes[n/2]);

	return 0;
}
