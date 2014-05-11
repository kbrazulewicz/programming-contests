#include <stdio.h>
#include <string.h>

#define MAX_M_LENGTH 256
#define MAX_N 200
#define __DEBUG

char power11[MAX_N + 1][MAX_M_LENGTH + 1];
char *ptrPower11[MAX_N + 1];

int maxPower = 0;

void initialize()
{
	strcpy(&power11[0][sizeof(power11[0]) - 2], "1");
	ptrPower11[0] = &power11[0][sizeof(power11[0]) - 2];
}


void calculate(int n) 
{
	int i, j, a;

	for (i = maxPower + 1; i <= n; i++) {
		j = sizeof(power11[0]) - 2;
		a = 1;
		do {
			power11[i][j] = '0' + a % 10;
			a /= 10;
			if (power11[i - 1][j]) a += power11[i - 1][j] - '0';
			j--;
			if (power11[i - 1][j]) a += power11[i - 1][j] - '0';
		} while (power11[i - 1][j] || a);
		ptrPower11[i] = &power11[i][j + 1];
	}
	maxPower = n;
}


int main()
{
	int i, n;

	initialize();

	scanf("%d\n", &i);
	while (i--) {
		scanf("%d\n", &n);
		calculate(n);
		puts(ptrPower11[n]);
	}
	return 0;
}
