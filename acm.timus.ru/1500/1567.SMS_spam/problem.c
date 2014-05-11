/* @JUDGE_ID: 16232QS 1567 C */

#include <stdio.h>

/*                          " !          , ." */
char costA['.' - ' ' + 1] = "13          2 1";
/*                          "abcdefghijklmnopqrstuvwxyz" */
char costB['z' - 'a' + 1] = "12312312312312312312312312";

int main()
{
	int r = 0;
	char c;

	while ((c = getchar()) != EOF) {
		if (c >= ' ' && c <= '.') {
			r += costA[c - ' '] - '0';
		} else if (c >= 'a' && c <= 'z') {
			r += costB[c - 'a'] - '0';
		}
	}

	printf("%d\n", r);

	return 0;
}
