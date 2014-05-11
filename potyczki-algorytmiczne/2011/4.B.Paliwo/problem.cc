#include <cstdio>
#include <queue>
#include <set>
using namespace std;

#undef DEBUG

const int MAX_N =    500000;
const int MAX_M = 200000000;

set<int> road[MAX_N + 1];

int main()
{
	int n, m, a, b;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < n - 1; i++)
	{
		scanf("%d %d", &a, &b);
		road[a].insert(b);
		road[b].insert(a);
	}

	queue<int> currentQ;
	set<int> leafCandidate;

	for (int i = 1; i <= n; i++) {
		if (road[i].size() == 1) {
			currentQ.push(i);
#ifdef DEBUG
			printf("Initial leaf [%d]\n", i);
#endif
		}
	}

	int distance = 0;
	while (!currentQ.empty()) {
#ifdef DEBUG
		printf("Distance [%d]\n", distance);
#endif
		while (!currentQ.empty()) {
			a = currentQ.front(); currentQ.pop();
			if (road[a].empty()) continue;

			b = *(road[a].begin());
			if (b == currentQ.back()) distance--;

#ifdef DEBUG
			printf("Removing [%d]:[%d]\n", a, b);
#endif

			road[a].erase(b);
			road[b].erase(a);

#ifdef DEBUG
			printf("New leaf candidate [%d]\n", b);
#endif
			leafCandidate.insert(b);
		}

#ifdef DEBUG
		printf("Future queue size [%d]\n", leafCandidate.size());
#endif

		while (!leafCandidate.empty()) {
			set<int>::iterator i = leafCandidate.lower_bound(1);
			a = *i;
			if (road[a].size() == 1) {
				currentQ.push(a);
#ifdef DEBUG
				printf("New leaf [%d]\n", a);
#endif
			}
			leafCandidate.erase(i);
		}

		distance += 2;
	}

#ifdef DEBUG
	printf("Max distance [%d]\n", distance);
#endif

	int maxCities;
	if (distance < m) {
		maxCities = distance + 1 + min((m - distance) / 2, n - (distance + 1));
	} else {
		maxCities = m + 1;
	}

	printf("%d\n", maxCities);

	return 0;
}
