#include <stdio.h>

int period[10] = {1, 1, 4, 4, 2, 1, 1, 4, 4, 2};
int lastDigit[10][4] = {
	{0, 0, 0, 0},
	{1, 0, 0, 0},
	{2, 4, 8, 6},
	{3, 9, 7, 1},
	{4, 6, 0, 0},
	{5, 0, 0, 0},
	{6, 0, 0, 0},
	{7, 9, 3, 1},
	{8, 4, 2, 6},
	{9, 1, 0, 0},
};

int main()
{
	int a, b;

	scanf("%d %d", &a, &b);

	int x = lastDigit[a % 10][(b - 1) % period[a % 10]];

	printf("%d\n", x);

	return 0;
}
