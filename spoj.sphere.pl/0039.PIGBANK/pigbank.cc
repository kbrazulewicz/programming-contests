#include <algorithm>
#include <cstdio>
#include <set>
using namespace std;

const int MAX_E = 10000;
const int MAX_F = 10000;
const int MAX_N = 500;
const int MAX_P = 50000;
const int MAX_W = 10000;

struct Coin {
	int p;
	int w;

	bool operator < (const Coin& rhs) const {
		return ((double) p / (double) w) < ((double) rhs.p / (double) rhs.w);
	}

	bool operator > (const Coin& rhs) const {
		return ((double) p / (double) w) > ((double) rhs.p / (double) rhs.w);
	}
};

Coin coins[MAX_N];

// index -> weight
// value -> value
int value[MAX_F + 1];

int calculateMinValue(int aWeight, int aCoinCount)
{
	fill(value, value + aWeight + 1, INT_MAX);
	sort(coins, coins + aCoinCount, less<Coin>());

	set<int> reachedWeights;
	value[0] = 0;
	reachedWeights.insert(0);

	for (int i = 0; i < aCoinCount; i++) {
		int p = coins[i].p;
		int w = coins[i].w;
		int wLimit = aWeight - w;

		for (set<int>::iterator i = reachedWeights.begin(); 
				i != reachedWeights.end() && *i <= wLimit && value[aWeight] == INT_MAX; 
				i++) 
		{
			printf("Coin [%d, %d]: setting value[%d] = %d\n", p, w, *i + w, min(value[*i + w], value[*i] + p));
			value[*i + w] = min(value[*i + w], value[*i] + p);
			reachedWeights.insert(i, *i + w);
		}
	}

	return value[aWeight];
}

int main()
{
	int t, e, f, n;

	scanf("%d", &t);

	while (t--) {
		scanf("%d%d%d", &e, &f, &n);
		for (int i = 0; i < n; i++) {
			scanf("%d%d", &(coins[i].p), &(coins[i].w));
		}

		int minValue = calculateMinValue(f - e, n);

		if (minValue != INT_MAX) {
			printf("The minimum amount of money in the piggy-bank is %d.\n", minValue);
		} else {
			printf("This is impossible.\n");
		}
	}

	return 0;
}
