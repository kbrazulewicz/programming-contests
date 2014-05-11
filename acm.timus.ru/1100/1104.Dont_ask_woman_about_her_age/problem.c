/* @JUDGE_ID: 16232QS 1104 C */

#include <stdio.h>

#define MAX(a,b) (a) > (b) ? (a) : (b)

#define MAX_K 36
#define MAX_LEN 1000000

char input[MAX_LEN + 1];
int modulus[MAX_K + 1];

int main()
{
	int minK = 2;
	int d, i;
	char *c = input;

	fgets(input, sizeof(input), stdin);
	while (*c != '\0' && *c != '\n') {
		if (*c >= '0' && *c <= '9')
			d = *c - '0';
		else
			d = *c - 'A' + 10;
		minK = MAX(minK, d + 1);

		for (i = minK; i <= MAX_K; ++i) {
			modulus[i] = (modulus[i] * i + d) % (i - 1);
		}
		c++;
	}

	for (i = minK; i <= MAX_K && modulus[i] != 0; ++i);

	if (i <= MAX_K) {
		printf("%d\n", i);
	} else {
		printf("No solution.\n");
	}

	return 0;
}
