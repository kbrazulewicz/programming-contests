/* @JUDGE_ID: 16232QS 1545 C */

#include <stdio.h>

#define MAX_N 1000

char dictionary['z' - 'a' + 1][3 * MAX_N + 1];
char* dictionaryPtr['z' - 'a' + 1];

int main()
{
	int n, i, f;
	char h[3];

	for (i = 0; i <= 'z' - 'a'; i++) {
		dictionaryPtr[i] = dictionary[i];
	}

	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%s", h);
		f = h[0] - 'a';
		*(dictionaryPtr[f]++) = h[0]; 
		*(dictionaryPtr[f]++) = h[1]; 
		*(dictionaryPtr[f]++) = '\n';
		*(dictionaryPtr[f]) = '\0';
	}

	scanf("%s", h);
	f = h[0] - 'a';
	if (dictionaryPtr[f] != dictionary[f]) {
		printf("%s", dictionary[f]);
	}



	return 0;
}
