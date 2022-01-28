#include <algorithm>
#include <cstdio>
#include <iterator>
#include <set>
#include <vector>
using namespace std;

#undef DEBUG

#define EVEN(X) (X % 2 == 0)
#define ODD(X) (X % 2 != 0)

#define FOR(E, I) for(typeof(I.begin()) E = I.begin(); E != I.end(); E++)


void setIntersection(const set<int> &i1, const set<int> &i2, set<int> &o)
{
	vector<int> v(min(i1.size(), i2.size()));
	vector<int>::iterator it = set_intersection(i1.begin(), i1.end(), i2.begin(), i2.end(), v.begin());
	o.insert(v.begin(), it);
}

bool jestOfertaMajoryzujaca(int n)
{
	int w1Min = 1e9 + 1, w2Max = 0, h1Min = 1e9 + 1, h2Max = 0;
	int w1, w2, h1, h2;
	set<int> w1Set, w2Set, h1Set, h2Set;

	while (n--)
	{
		scanf("%d%d%d%d", &w1, &w2, &h1, &h2);
		if (w1 < w1Min)
		{
			w1Min = w1;
			w1Set.clear();
			w1Set.insert(n);
		}
		else if (w1 == w1Min)
		{
			w1Set.insert(n);
		}
		if (w2 > w2Max)
		{
			w2Max = w2;
			w2Set.clear();
			w2Set.insert(n);
		}
		else if (w2 == w2Max)
		{
			w2Set.insert(n);
		}
		if (h1 < h1Min)
		{
			h1Min = h1;
			h1Set.clear();
			h1Set.insert(n);
		}
		else if (h1 == h1Min)
		{
			h1Set.insert(n);
		}
		if (h2 > h2Max)
		{
			h2Max = h2;
			h2Set.clear();
			h2Set.insert(n);
		}
		else if (h2 == h2Max)
		{
			h2Set.insert(n);
		}
	}

	set<int> wCandidates, hCandidates, finalOffer;

#ifdef DEBUG
	FOR(iw1, w1Set) { printf("w1: %d\n", *iw1); }
	FOR(iw2, w2Set) { printf("w2: %d\n", *iw2); }
	FOR(ih1, h1Set) { printf("h1: %d\n", *ih1); }
	FOR(ih2, h2Set) { printf("h2: %d\n", *ih2); }
#endif

	setIntersection(w1Set, w2Set, wCandidates);
#ifdef DEBUG
	FOR(i, wCandidates) { printf("wCandidate: %d\n", *i); }
#endif

	setIntersection(h1Set, h2Set, hCandidates);
#ifdef DEBUG
	FOR(i, hCandidates) { printf("hCandidate: %d\n", *i); }
#endif
	setIntersection(wCandidates, hCandidates, finalOffer);

	return !finalOffer.empty();
}

int main()
{
	int t, n;

	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &n);
		puts(jestOfertaMajoryzujaca(n) ? "TAK" : "NIE");
	}

	return 0;
}
