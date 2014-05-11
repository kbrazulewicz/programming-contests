/* @JUDGE_ID: 16232QS 1263 C++ */

#include <iostream>
#include <string>
using namespace std;

static const int MAX_N = 10000;

int election[MAX_N + 1];

int main()
{
	int n, m, v;

	scanf("%d%d", &n, &m);
	for (int i = 0; i < m; i++) {
		scanf("%d", &v);
		election[v]++;
	}

	for (int i = 1; i <= n; i++) {
		printf("%.2f%%\n", (double) election[i] * 100 / m);
	}

	return 0;
}
