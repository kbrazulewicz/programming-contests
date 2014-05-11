#include <stdio.h>

#define MIN(a,b) (a < b ? a : b)
#define MAX(a,b) (a > b ? a : b)


#define MAX_LEN 1000

int calculate(const char *aInput)
{
	int minBracket = 0;
	int bracketLevel = 0;

	while (*aInput == '(' || *aInput == ')') {
		if (*aInput == '(') {
			bracketLevel++;
		} else if (*aInput == ')') {
			bracketLevel--;
			minBracket = MIN(minBracket, bracketLevel);
		}

		aInput++;
	}

	bracketLevel += -minBracket;


	return abs(minBracket) + (bracketLevel > 0 ? bracketLevel : 0);
}


char input[MAX_LEN + 3];

int main()
{
	int c;

	scanf("%d\n", &c);

	while (c--) {
		fgets(input, sizeof(input), stdin);
		printf("%d\n", calculate(input));
	}

	return 0;
}
