/* @JUDGE_ID: 16232QS 1149 C */

#include <stdio.h>
#include <string.h>

#define MAX_N 200

char gClosingBracket[MAX_N];
char gOpeningBracket[MAX_N];


void printAn(int n)
{
	int i;
	char* sign[] = {"+", "-"};

	for (i = 1; i <= n; i++) {
		printf("sin(%d%s", i, i == n ? "" : sign[i % 2]);
	}

	printf("%.*s", n, gClosingBracket);
}

void printSn(int n)
{
	int i;

	printf("%.*s", n - 1, gOpeningBracket);

	for (i = 1; i <= n; i++) {
		printAn(i);
		printf("+%d%s", n + 1 - i, i != n ? ")" : "");
	}
}

int main()
{
	int n;

	scanf("%d", &n);

	memset(gClosingBracket, ')', n);
	memset(gOpeningBracket, '(', n);

	printSn(n);
	
	return 0;
}
