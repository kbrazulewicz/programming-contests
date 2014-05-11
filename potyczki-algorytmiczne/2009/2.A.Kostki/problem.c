#include <stdio.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

// max memory is 32MB, double is 8 bytes long, double* is 4 bytes long
double prob[3000000];

#define PRECALCULATE_ROLL_LIMIT 1500
double *F[PRECALCULATE_ROLL_LIMIT + 1];

double getF(int n, int k)
{
	if (k < n || 6 * n < k) {
		return 0;
	}

	if (7 * n < 2 * k) {
		k = 7 * n - k;
	}

	return F[n][k];
}

void precalculate()
{
	for (int i = 1, j = 1; i <= PRECALCULATE_ROLL_LIMIT; i++)
	{
		F[i] = prob + j - i;

		j += (5 * i) / 2 + 1;
	}

	// initialize F6,1(k)
	for (int i = 1; i <= 6; i++)
	{
		F[1][i] = (double) 1 / 6;
	}

	for (int i = 2; i <= PRECALCULATE_ROLL_LIMIT; i++)
	{
		for (int k = i; k <= (7 * i) / 2; k++)
		{
			F[i][k] = 0;
			for (int n = 1; n <= MIN(k, 6); n++) 
			{
				F[i][k] += getF(i - 1, k - n) / 6;
			}
//			printf("F[%d][%d] = %f\n", i, k, F[i][k]);
		}
	}
}

double calculate(int i, int k)
{
	if (k < i || 6 * i < k) {
		return 0;
	}

	if (i <= PRECALCULATE_ROLL_LIMIT) 
	{
		return getF(i, k);
	}	

	if (7 * i < 2 * k) {
		k = 7 * i - k;
	}

	double result = 0;

	for (int n = 1; n < k; n++) 
	{
		result += calculate(i / 2, n) * calculate(i - i / 2, k - n);
	}

	return result;
}

int main()
{
	int t, n, k;

	precalculate();

	scanf("%d", &t);

	while (t--) {
		scanf("%d%d", &n, &k);
		printf("%d\n", (int) floor(100 * calculate(n, k)));
	}

	return 0;
}
