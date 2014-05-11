#include <math.h>
#include <stdio.h>

const static int MAX_YEAR = 5000;
const static double BINET_A = (1 + sqrt(5))/2;
const static double BINET_B = (1 - sqrt(5))/2;
const static double BINET_A_YEAR = BINET_A * BINET_A * BINET_A * BINET_A * BINET_A * BINET_A * BINET_A * BINET_A * BINET_A * BINET_A * BINET_A * BINET_A;
const static double BINET_B_YEAR = BINET_B * BINET_B * BINET_B * BINET_B * BINET_B * BINET_B * BINET_B * BINET_B * BINET_B * BINET_B * BINET_B * BINET_B;
const static double BINET_A_LEN = log(BINET_A) / log(10);
const static double BINET_B_LEN = log(BINET_B) / log(10);


double binetA[MAX_YEAR], binetB[MAX_YEAR];
int decimalCorrection[MAX_YEAR];

int chomikCountMax;

void calculate(int n)
{
	for (int i = chomikCountMax + 1; i <= n; i++)
	{
	}
}


int main()
{
	// int c, n;

	/*
	chomikCountMax = 0;

	scanf("%d", &c);
	while (c--) {
		scanf("%d", &n);
	}
	*/

	printf("%f\n", BINET_A_YEAR + BINET_B_YEAR);

	return 0;
}
