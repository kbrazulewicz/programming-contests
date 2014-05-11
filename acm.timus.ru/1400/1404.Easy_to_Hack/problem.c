/* @JUDGE_ID: 16232QS 1404 C */

#include <stdio.h>

#define MAX_LEN 100

char encoded[MAX_LEN + 1];
char decoded[MAX_LEN + 1];

int main()
{
	int i = 0;
	fgets(encoded, sizeof(encoded), stdin);

	decoded[i] = (26 + encoded[i] - 'a' - 5) % 26 + 'a';
	while (encoded[++i] >= 'a') {
		decoded[i] = (26 + encoded[i] - encoded[i - 1]) % 26 + 'a';
	}
	decoded[i] = '\0';

	puts(decoded);

	return 0;
}
