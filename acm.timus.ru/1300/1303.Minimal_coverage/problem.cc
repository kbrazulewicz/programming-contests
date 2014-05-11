/* @JUDGE_ID: 16232QS 1303 C++ */

#include <iostream>
#include <list>
#include <map>
using namespace std;

typedef struct {
	int l;
	int r;
} segment_t;

static const int MAX_I = 100000;


bool segment_cmp(const segment_t& a, const segment_t& b) 
{
	return (a.l < b.l || (a.l == b.l && b.r > a.r));
}

int main()
{
	int m = 0;
	segment_t segment;
	list<segment_t> segments;
	map<int, int> coverage;


	// input
	scanf("%d", &m);
	do {
		scanf("%d%d", &segment.l, &segment.r);
		if (segment.l > segment.r) swap(segment.l, segment.r);

		if (segment.l < m && segment.r > 0 && segment.l != segment.r) {
			segments.push_back(segment);
		}	
	} while (!(segment.l == 0 && segment.r == 0));

	// sort
	segments.sort(segment_cmp);

	// coverage
	for (list<segment_t>::const_iterator i = segments.begin(); i != segments.end(); i++)
	{
		coverage[i->l]++;
		coverage[i->r + 1]--;
	}

	int z = 0;
	for (map<int, int>::const_iterator i = coverage.begin(); i != coverage.end(); i++)
	{
		z += i->second;
		printf("coverage [%d] [%d]\n", i->first, z);
	}

	// check for no solution
	{
		int numberOfSegments = 0;
		bool noSolution = false;
		for (map<int, int>::const_iterator i = coverage.begin(); i != coverage.end() && !noSolution; i++)
		{
			if (0 < i->first && i->first <= m && numberOfSegments == 0) {
				noSolution = true;
			}
			numberOfSegments += i->second;
			if (0 <= i->first && i->first <= m && numberOfSegments == 0) {
				noSolution = true;
			}
		}

		if (noSolution) {
			printf("No solution\n");
			return 0;
		}
	}

	for (list<segment_t>::iterator i = segments.begin(); i != segments.end(); )
	{
	}


	for (list<segment_t>::iterator i = segments.begin(); i != segments.end(); )
	{
		list<segment_t>::iterator prev = i; prev--;
		list<segment_t>::iterator next = i; next++;

		if (i == segments.begin()) {
			if (next != segments.end()) {
				if (next->r >= i->r && next->l <= 0) {
					i = segments.erase(i);
					continue;
				}
			}
		} else {
			if (prev->r >= i->r) {
//				printf("Erasing.B [%d %d], prev [%d %d]\n", i->l, i->r, prev->l, prev->r);
				i = segments.erase(i);
				continue;
			} else if (next != segments.end()) {
				if (next->l <= prev->r) {
					if (i->r >= m && next->r >= m) {
						if (i->r >= next->r) {
							i = segments.erase(i);
							continue;
						}
					} else if (i->r <= next->r) {
						// printf("Erasing.C [%d %d], prev [%d %d], next [%d %d]\n", i->l, i->r, prev->l, prev->r, next->l, next->r);
						i = segments.erase(i);
						continue;
					}
				}
			}
		}
//		printf("Leaving [%d %d]\n", i->l, i->r);
		i++;
	}

	int r = 0;
	bool noSolution = false;
	for (list<segment_t>::iterator i = segments.begin(); i != segments.end() && !noSolution; i++)
	{
		if (i->l > r) {
			noSolution = true;
			break;
		} else {
			r = i->r;
		}
	}
	noSolution |= r < m;

	if (noSolution) {
		printf("No solution\n");
	} else {
		printf("%d\n", segments.size());

		for (list<segment_t>::iterator i = segments.begin(); i != segments.end(); i++) {
			printf("%d %d\n", i->l, i->r);
		}
	}
		
	return 0;
}
