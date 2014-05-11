/* @JUDGE_ID: 16232QS 1210 C++ */

#include <iostream>
#include <string>
using namespace std;

static const int MAX_N = 29;
static const int MAX_COST = 32767;

int planets[MAX_N + 1][MAX_N + 1];

int main()
{
	int n, k;

	scanf("%d", &n);

	planets[0][1] = 0;

	for (int i = 1; i <= n; i++) {
		scanf("%d", &k);

		for (int j = 1; j <= k; j++) {
			int from, cost;

			planets[i][j] = MAX_COST * MAX_N;
			
			do {
				scanf("%d", &from);
				if (from != 0) {
					scanf("%d", &cost);
					planets[i][j] = min(planets[i][j], planets[i - 1][from] + cost);
				}
			} while (from != 0);
		}

		scanf("\n*");
	}

	int minCost = planets[n][1];
	for (int j = 2; j <= k; j++) {
		minCost = min(minCost, planets[n][j]);
	}

	printf("%d\n", minCost);

	return 0;
}
