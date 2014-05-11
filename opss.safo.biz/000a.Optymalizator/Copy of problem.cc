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

int optTest[RANGE_S];

bool optymalizator()
{
	int n, s, a, minS, maxS;
	int io, in;

	memset(optTest, 0, sizeof(optTest));

	scanf("%d%d%d", &n, &s, &a);
	minS = maxS = a;
	optTest[a - MIN_S] = 1;
//	printf("SUM [%d] using [%d:%d]\n", a, 0, a);
	for (int i = 1; i < n; i++) {
		scanf("%d", &a);

		if (optTest[s - MIN_S] == 0) {
			for (io = minS - MIN_S; io <= maxS - MIN_S; io++) {
				if (optTest[io] > 0 && optTest[io] <= i) {
					in = io + a;
					if (optTest[in] == 0) {
						optTest[in] = i + 1;
						// printf("SUM [%d] using [%d:%d]\n", j + a, i, a);
					}
				}
			}
			optTest[a - MIN_S] = i + 1;
//			printf("SUM [%d] using [%d:%d]\n", a, i, a);

			minS = min(min(minS, minS + a), a);
			maxS = max(max(maxS, maxS + a), a);
//			printf("MIN [%d] MAX [%d] using [%d:%d]\n", minS, maxS , i, a);
		}
	}

	return optTest[s - MIN_S] != 0;
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
