#include <stdio.h>
#include <map>
#include <set>

using namespace std;

int degree[4000];
set<int> passage[2000];
multimap<int, int, greater<int> > countryOrdered;

int main()
{
	int countA, countB;
	int passageCount, internationalPassageCount = 0;
	int i, a, b, t;

	scanf("%d %d %d", &countA, &countB, &passageCount);
	memset(degree, 0, sizeof(degree));

	for (i = 0; i < passageCount; i++) {
		scanf("%d %d", &a, &b);
		if (a > b) {
			t = a; a = b; b = t;
		}
		if (a <= countA && b > countA) {
			a--; b--;
			degree[a]++;
			degree[b]++;
			passage[a].insert(b);
			internationalPassageCount++;
		}
	}

	for (i = 0; i < countA; i++) {
		countryOrdered.insert(pair<int, int>(degree[i], i));
	}
	
	multimap<int, int>::iterator it = countryOrdered.begin();
	set<int>::iterator jt;
	while (it != countryOrdered.end()) {
		a = it->second;
		
		jt = passage[a].begin();
		while (degree[a] > 1 && jt != passage[a].end()) {
			b = *jt;
			if (degree[b] > 1) {
				passage[a].erase(jt);
				degree[a]--;
				degree[b]--;
				internationalPassageCount--;
			}
			jt++;
		}
		it++;
	}

	printf("%d\n", internationalPassageCount);
	
	return 0;
}
