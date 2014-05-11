/* @JUDGE_ID: 16232QS 1330 C++ */

#include <iostream>
#include <string>
using namespace std;

static const int MAX_N = 10000 + 1;

int k[MAX_N];

int main()
{
	int n, q;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &k[i]);
		if (i > 0) {
			k[i] += k[i - 1];
		}
	}

	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		int a, b;
		scanf("%d%d", &a, &b);

		printf("%d\n", a == 1 ? k[b - 1] : (k[b - 1] - k[a - 2]));
	}

	return 0;
}
