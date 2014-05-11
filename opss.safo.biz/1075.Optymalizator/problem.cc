#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAX_N 500
#define MAX_A 500
#define MIN_A -500
#define MAX_S (MAX_N * MAX_A)
#define MIN_S (MAX_N * MIN_A)
#define RANGE_S (MAX_S - MIN_S + 1)

char optTest[RANGE_S];

bool optymalizator()
{
	int n, s, a, minS, maxS;
	int aList[MAX_N];

	memset(optTest, 0, sizeof(optTest));

	scanf("%d%d", &n, &s);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a);
		if (i == 0) {
			maxS = minS = a;
		} else {
			maxS = max(max(maxS, maxS + a), a);
			minS = min(min(minS, minS + a), a);
		}
		aList[i] = a;
	}

	if (s < minS || s > maxS) return false;
	
	for (int i = 0; i < n; i++) {
		a = aList[i];

		if (a > 0) {
			for (int j = maxS - minS + 1 - a; j >= 0; j--) {
				optTest[j + a] |= optTest[j];
				// printf("SUM [%d] using [%d:%d]\n", j + a, i, a);
			}
		} else if (a < 0) {
			for (int j = 0; j <= maxS - minS + 1 + a; j++) {
				optTest[j] |= optTest[j - a];
				// printf("SUM [%d] using [%d:%d]\n", j + a, i, a);
			}
		}
		optTest[a - minS] = 1;
//		printf("SUM [%d] using [%d:%d]\n", a, i, a);

		if (optTest[s - minS] != 0) return true;
	}

	return false;
}

int main()
{
	int c;
	scanf("%d", &c);

	while (c--) {
		printf("%s\n", optymalizator() == 1 ? "TAK" : "NIE");
	}
	
	return 0;
}
