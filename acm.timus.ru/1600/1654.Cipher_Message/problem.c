/* @JUDGE_ID: 16232QS 1654 C */

#include <stdio.h>

#define MAX_LENGTH 200000

int main()
{
	char input[MAX_LENGTH + 1];
	char output[MAX_LENGTH + 1];
	char *i = input, *o = output;

	fgets(input, sizeof(input), stdin);

	while (*i != '\0' && *i != '\n') {

		if (o == output) {
			*(o++) = *(i++);
		} else if (*(o - 1) == *i) {
			--o;
			i++;
		} else {
			*(o++) = *(i++);
		}
	}

	*o = '\0';

	puts(output);

	return 0;
}
