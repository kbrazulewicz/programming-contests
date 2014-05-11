#include <iostream>
#include <string>
using namespace std;

const static unsigned int MAX_N = 50;
const static unsigned int MAX_K = 1000;

static int temperatureLimit[MAX_N][2];

int main()
{
	int n, k, m;
	int a, tMin, tMax;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &temperatureLimit[i][0], &temperatureLimit[i][1]);
	}

	scanf("%d", &k);
	for (int i = 0; i < k; i++) {
		scanf("%d %d", &m, &a);
		tMin = temperatureLimit[a - 1][0];
		tMax = temperatureLimit[a - 1][1];
		for (int j = 1; j < m; j++) {
			scanf("%d", &a);
			tMin = max(tMin, temperatureLimit[a - 1][0]);
			tMax = min(tMax, temperatureLimit[a - 1][1]);
		}

		if (tMin <= tMax) {
			printf("%d %d\n", tMin, tMax);
		} else {
			printf("NIE\n");
		}
	}

	return 0;
}
