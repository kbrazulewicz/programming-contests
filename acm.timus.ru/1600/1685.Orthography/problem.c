/* @JUDGE_ID: 16232QS 1685 C */

#include <stdio.h>

#define MAX_LENGTH 20000

char input[MAX_LENGTH + 1];
char output[MAX_LENGTH + 1];
char *i = input;

void decode(int l, int r)
{
	int m = (l + r) / 2;
	output[m] = *(i++);
	if (l < m) {
		decode(l, m - 1);
	}
	if (m < r) {
		decode(m + 1, r);
	}
}

int main()
{
	int s, l, r;
	fgets(input, sizeof(input), stdin);

	s = strlen(input);
	if (input[s - 1] == '\n') {
		input[--s] = '\0';
	}
	output[s] = '\0';

	decode(0, s - 1);

	puts(output);

	return 0;
}
