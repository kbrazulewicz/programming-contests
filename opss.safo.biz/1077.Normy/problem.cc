#include <iostream>
#include <map>
#include <string>
using namespace std;

static const unsigned int MAX_N = 100000;

int gSamples[MAX_N];


void calculate()
{
	int n, c, b1, b2, l, r, nSamples;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", gSamples + i);
	}

	multimap<int, int> sampleMap;

	sort(gSamples, gSamples + n);
	for (int i = 0; i < n; i++) {
		sampleMap.insert(sampleMap.end(), make_pair(gSamples[i], i));
	}

	scanf("%d", &c);

	for (int i = 0; i < c; i++) {
		scanf("%d %d", &b1, &b2);

		multimap<int, int>::const_iterator lb = sampleMap.lower_bound(b1);
		multimap<int, int>::const_iterator ub = sampleMap.upper_bound(b2);

		if (lb == sampleMap.end()) {
			nSamples = 0;
		} else {
			l = lb->second;
			if (ub == sampleMap.end()) {
				r = n;
			} else {
				r = ub->second;
			}
			nSamples = r - l;
		}

		printf("%d\n", nSamples);
	}
}

int main()
{
	int c;

	scanf("%d", &c);

	while (c--) {
		calculate();
	}
	
	return 0;
}
