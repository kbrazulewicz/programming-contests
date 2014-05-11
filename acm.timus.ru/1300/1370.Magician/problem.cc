/* @JUDGE_ID: 16232QS 1370 C++ */

#include <iostream>
#include <string>
using namespace std;

static const int MAX_N = 1000;

int w[MAX_N];

int main()
{
	int n, m;

	scanf("%d%d", &n, &m);

	for (int i = 0; i < n; scanf("%d", &w[i++]));

	m %= n;

	for (int i = 0; i < 10; i++) {
		printf("%d", w[(m + i) % n]);
	}

	printf("\n");

	return 0;
}
