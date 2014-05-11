/* @JUDGE_ID: 16232QS 1604 C++ */

#include <stdio.h> 
#include <map>
using namespace std;

typedef multimap< int, int, greater<int> > signs_t;

int main()
{
	int k, n, lastUsed = 0;
	signs_t signs;

	scanf("%d", &k);
	for(int i = 0; i < k; ++i) {
		scanf("%d", &n);
		signs.insert(make_pair(n, i + 1));
	}


	while (!signs.empty()) {
		signs_t::iterator i = signs.begin();
		if (i->second == lastUsed) {
			if (signs.size() > 1) 
				++i;
		}

		printf(lastUsed == 0 ? "%d" : " %d", i->second);
		lastUsed = i->second;

		if (i->first > 1) {
			signs.insert(make_pair(i->first - 1, i->second));
		}
		signs.erase(i);
	}

	printf("\n");

	return 0;
}
