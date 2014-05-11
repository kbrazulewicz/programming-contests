/* @JUDGE_ID: 16232QS 1192 C++ */

#include <cmath>
#include <cstdio>
using namespace std;

static const double PI = 3.1415926535;

int main()
{
	double v, a, k;

	scanf("%lf %lf %lf", &v, &a, &k);

	double a1 = 2 * v * v * sin(a * PI / 180) * cos(a * PI / 180) / 10;
	double r = a1 / (1 - 1 / k);

	printf("%.2f\n", r);

	return 0;
}
