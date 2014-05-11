#include <stdio.h>

#define MAX_N 200

char output[2 * MAX_N];

int calculateSumOfDigits(int aInput)
{
	int output = 0;

	while (aInput) {
		output += aInput % 10;
		aInput /= 10;
	}

	return output;
}


void calculate(int n)
{
	int index = 2 * n - 1;
	int a = 0, c = 0;

	output[index--] = 0;

	while (index >= 0) {

		if (index >= n - 1) {
			a++;
		} else {
			a--;
		}

		output[index] = '0' + (a + c) % 10;
		c = (a + c) / 10;
		index--;
	}
}

int main()
{
	int k, n;

	scanf("%d", &k);

	while (k--) {
		scanf("%d", &n);

		calculate(n);
		puts(output);
	}
	return 0;
}
