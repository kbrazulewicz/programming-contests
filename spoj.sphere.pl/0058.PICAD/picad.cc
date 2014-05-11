#include <cstdio>

#include <map>
#include <utility>

using namespace std;

typedef std::map< int, std::pair<int, int> > timespace_type;
timespace_type gTimespace;


void runTest()
{
	int p, k, n;

	gTimespace.clear();

	scanf("%d %d %d", &p, &k, &n);

	int currentNumber = 0;

	for (int i = 0; i < n; i++) {
		int a, b;

		scanf("%d %d", &a, &b);

		if (b >= p && a <= k) {
			gTimespace[a].first++;
			gTimespace[b].second++;
			if (a <= p) currentNumber++;
		}
	}

	int minP = currentNumber, maxP = currentNumber;
	timespace_type::const_iterator tti = gTimespace.lower_bound(p);
	timespace_type::const_iterator tte = gTimespace.upper_bound(k);

	while (tti != tte) {
		if (tti->first == p) {
			currentNumber -= tti->second.second;
			minP = min(minP, currentNumber);
		} else if (tti->first == k) {
			currentNumber += tti->second.first;
			maxP = max(maxP, currentNumber);
		} else {
			currentNumber += tti->second.first;
			maxP = max(maxP, currentNumber);
			currentNumber -= tti->second.second;
			minP = min(minP, currentNumber);
		}
		tti++;
	}

	printf("%d %d\n", minP, maxP);
}


int main()
{
	for (int i = 0; i < 10; i++) {
		runTest();
	}

	return 0;
}
