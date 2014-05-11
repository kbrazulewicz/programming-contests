#include <cstdio>
using namespace std;

int main()
{
	int n;

	scanf("%d", &n);

	int maxLength = 1 + (n - 2) / 2;
	int middle = maxLength;
	int pairCount;

	if (n == 1) pairCount = 0;
	else if (n == 2) pairCount = 1;
	else if (n == 3) pairCount = 3;
	else pairCount = (n - 2) * 3;

	printf("%d\n", pairCount);
	printf("%d %d %d\n", 0, middle - maxLength, middle + maxLength);
	for (int i = 1; i < n; i++) {
		int d, g;

		if (i % 2) {
			d = middle;
			g = d + (i + 1) / 2;
		} else {
			g = middle;
			d = g - (i + 1) / 2;
		}

		printf("%d %d %d\n", i, d, g);
	}

	return 0;
}
