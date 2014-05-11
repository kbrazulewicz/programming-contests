#include <cstdio>
#include <map>

using namespace std;

typedef pair<int, int> item_t;
typedef map<int, item_t> list_t;
list_t inout;


int main()
{
	int p, k, n, a, b;
	int pMax, pMin;

	scanf("%d%d%d", &p, &k, &n);
	pMax = 0; pMin = n;
	inout[p] = make_pair(0, 0);
	inout[k] = make_pair(0, 0);

	while (n--) {
		scanf("%d%d", &a, &b);
		inout[a].first++;
		inout[b].second++;
	}

	list_t::const_iterator it(inout.begin());
	list_t::const_iterator itE(inout.end());

	int m = -1, in, out, total = 0;
	for (;it != itE && m < k; it++) {
		m   = (*it).first;
		in  = (*it).second.first;
		out = (*it).second.second;

		if (p <= m && m <= k) {
			if (p == k) pMax = pMin = total + in;
			else if (m == k) {
				pMax = max(pMax, total + in);
			} else {
				pMax = max(pMax, total + in);
				pMin = min(pMin, total + in - out);
			}
		}
			
		total = total + in - out;
	}

	printf("%d %d\n", pMin, pMax);
	
	return 0;
}
