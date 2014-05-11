#include <stdio.h>

#define MAX_LENGTH 20000

char queue[MAX_LENGTH + 1];
char input[MAX_LENGTH + 1];

int main() 
{
	int length, i;
	int depth = 0, maxDepth = 0;
	int cut = 0, minCut = 0;

	scanf("%d%s", &length, input);

	for (i = 0; i < length; i++) {
		char x = input[i] - '0';

		if (x) {
			cut++;
			queue[++depth] = 2;
			if (depth > maxDepth) {
				maxDepth = depth;
				minCut = cut;
			}
		} else {
			while(!(--queue[depth]) && depth--);
		}
	}

	printf("%d\n", minCut);

	return 0;
}
