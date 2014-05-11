/* @JUDGE_ID: 16232QS XXXX C++ */

#include <iostream>
using namespace std;

static const int MAX_N = 150;
static const int MIN_A = 600;
static const int MAX_A = 700;


size_t a[MAX_A - MIN_A + 1];


int main()
{
	int n, t, r = 0;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &t);
		++a[t - MIN_A];
	}

	for (int i = 0; i < MAX_A - MIN_A + 1; i++) {
		r += a[i] / 4;
	}

	printf("%d\n", r);

	return 0;
}
