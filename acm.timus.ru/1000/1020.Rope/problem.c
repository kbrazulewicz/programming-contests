/* @JUDGE_ID: 16232QS 1020 C */

#include <math.h>
#include <stdio.h>

#define MAX_N 100

double x[MAX_N], y[MAX_N];

int main()
{
	int n;
	double radius;
	double rope = 0.0;
	int i;

	scanf("%d %lf", &n, &radius);

	rope = 2 * M_PI * radius;
	scanf("%lf %lf", &x[0], &y[0]);

	for (i = 1; i < n; i++) {
		scanf("%lf %lf", &x[i], &y[i]);
		rope += sqrt((x[i] - x[i-1]) * (x[i] - x[i-1]) + (y[i] - y[i-1]) * (y[i] - y[i-1]));
	}
	rope += sqrt((x[n - 1] - x[0]) * (x[n-1] - x[0]) + (y[n-1] - y[0]) * (y[n-1] - y[0]));

	printf("%.2f\n", rope);
	
	return 0;
}
