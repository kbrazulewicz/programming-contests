#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
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
	int n, s, aIn, minS, maxS;
	int j;
	vector<int> a;

	memset(optTest, 0, sizeof(optTest));

	scanf("%d%d", &n, &s);
	minS = maxS = 0;
	a.reserve(n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &aIn);
		a.push_back(aIn);
	}

	sort(a.begin(), a.end());
	return false;

	
	for (int i = 0; i < n; i++) {
		aIn = a[i];

		if (optTest[s - MIN_S] == 0) {
			if (aIn > 0) {
				for (j = maxS - MIN_S; j >= minS - MIN_S; j--) {
					optTest[j + aIn] |= optTest[j];
				}
				maxS = max(max(maxS, maxS + aIn), aIn);
			} else if (aIn < 0) {
				for (j = minS - MIN_S; j <= maxS - MIN_S; j++) {
					optTest[j + aIn] |= optTest[j];
				}
				minS = min(min(minS, minS + aIn), aIn);
			}
			optTest[aIn - MIN_S] = 1;
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
