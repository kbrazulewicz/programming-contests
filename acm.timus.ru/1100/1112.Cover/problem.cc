/* @JUDGE_ID: 16232QS 1112 C++ */

#include <algorithm>
#include <iostream>
#include <list>
using namespace std;

static const int MAX_N = 100;

typedef struct {
	int l;
	int r;
} segment_t;

bool operator < (const segment_t& a, const segment_t& b) {
//	return a.l < b.l || (a.l == b.l && a.r < b.r);
	return a.r < b.r;
}

segment_t segments[MAX_N];

int main()
{
	int n, a, b;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &segments[i].l, &segments[i].r);
		if (segments[i].l > segments[i].r) {
			swap(segments[i].l, segments[i].r);
		}
	}

	sort(segments, segments + n);

	list<segment_t> cover;
	cover.push_back(segments[0]);

	for (int i = 1; i < n; i++) {
		if (segments[i].l >= cover.back().r) {
			cover.push_back(segments[i]);
		}
	}

	printf("%d\n", cover.size());
	for (list<segment_t>::const_iterator i = cover.begin(); i != cover.end(); i++) {
		printf("%d %d\n", i->l, i->r);
	}

	return 0;
}
