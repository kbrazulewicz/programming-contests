#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 200

char lastDigit[] = "1397";

int main()
{
	char line[MAX_LEN + 4];
	int d;
	int x;

	scanf("%d\n", &d);
	while (d--) {
		fgets(line, sizeof(line) - 1, stdin);
		if (!isdigit(line[strlen(line) - 1])) {
			line[strlen(line) - 1] = 0;
		}

		if (strlen(line) > 2) {
			x = atoi(line + strlen(line) - 2);
		} else {
			x = atoi(line);
		}

		printf("%c\n", lastDigit[x % 4]);
	}
	return 0;
}
