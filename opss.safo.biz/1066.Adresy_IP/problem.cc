#include <algorithm>
#include <cstdio>
#include <map>
#include <set>
#include <vector>

using namespace std;

const int MAX_P = 10;
const int PRINT_LIMIT = 10000;

int permutation[MAX_P];
int printCount;

void print(int p)
{
	for (int i = 0; i < p; i++) {
		printf("%d%c", permutation[i], (i == p - 1) ? '\n' : '.');
	}
}


bool calc(const multiset<int>& k, int aStart, int aEnd) 
{
	if (aStart == aEnd) {
		print(aEnd);
		return ! (++printCount == PRINT_LIMIT);
	} else {
		set<int> v(k.begin(), k.end());
		multiset<int> k1(k);
		for (set<int>::const_iterator i = v.begin(); i != v.end(); i++) {
			permutation[aStart] = *i;
			k1.erase(k1.find(*i));
			if (!calc(k1, aStart + 1, aEnd)) {
				return false;
			}
			k1.insert(*i);
		}
	}
	return true;
}

int main()
{
	int p, v;
	multiset<int> k;

	scanf("%d", &p);
	for (int i = 0; i < p; i++) {
		scanf("%d", &v);
		k.insert(v);
	}
	printCount = 0;

	calc(k, 0, p);

	return 0;
}
