#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
using namespace std;

#define MAX_N 500
#define MAX_A 500
#define MIN_A -500
#define MAX_S (MAX_N * MAX_A)
#define MIN_S (MAX_N * MIN_A)
#define RANGE_S (MAX_S - MIN_S + 1)

bool optymalizator()
{
	int n, s, a;
	bool found = false;

	set<int> optTest;

	scanf("%d%d", &n, &s);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a);

		if (!found) {
			vector<int> optTestAdd(optTest.begin(), optTest.end());
			vector<int>::iterator otaC = optTestAdd.begin();
			vector<int>::iterator otaE = optTestAdd.end();
			while (otaC != otaE) {
				*otaC += a;
				otaC++;
			}

			optTest.insert(optTestAdd.begin(), optTestAdd.end());
			optTest.insert(a);

			found = optTest.find(s) != optTest.end();
		}
		printf("%d %d\n", i, optTest.size());
	}

	return found;
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
