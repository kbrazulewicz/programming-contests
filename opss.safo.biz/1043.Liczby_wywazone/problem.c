#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 200

char value[1 + MAX_DIGITS + 2];

void calculate()
{
	int shift[4] = {2, 1, 4, 3};
	int length, x, a, i;

	length = strlen(value) - 1;
	value[length] = 0;

	x = (value[length - 2] - '0') * 10 + value[length - 1];
	a = shift[x % 4];

	i = length - 1;
	while (a) {
		x = value[i] - '0' + a;
		value[i] = x % 10 + '0';
		a = x / 10;
		i--;
	}
}

int main()
{
	int c;

	scanf("%d\n", &c);

	while (c--) {
		value[0] = '0';
		fgets(value + 1, sizeof(value) - 1, stdin);
		calculate();
		puts(value[0] == '0' ? value + 1 : value);
	}

	return 0;
}
