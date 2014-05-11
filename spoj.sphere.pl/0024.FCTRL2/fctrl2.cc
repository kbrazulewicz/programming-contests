#include <cstdio>
#include <cstring>
using namespace std;

const int MAX_VALUE = 1000000;

unsigned int number[30];

void multiply(int n)
{
	static const int length = sizeof(number) / sizeof(number[0]);

	unsigned int a = 0;

	for (int i = 0; i < length; i++) {
		a += number[i] * n;

		number[i] = a % MAX_VALUE;
		a /= MAX_VALUE;
	}
}

void print()
{
	static const int length = sizeof(number) / sizeof(number[0]);

	int i = length;

	while (!number[--i]);
	printf("%d", number[i--]);
	while (i >= 0) printf("%.6d", number[i--]);
}

void calculate(int n)
{
	memset(number, 0, sizeof(number));
	number[0] = 1;

	for (int i = 2; i <= n; i++) {
		multiply(i);
	}
}


int main()
{
	int t, n;

	scanf("%d", &t);

	while (t--) {
		scanf("%d", &n);
		calculate(n);
		print(); putchar('\n');
	}
	return 0;
}
