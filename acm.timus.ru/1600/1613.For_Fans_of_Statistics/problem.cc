/* @JUDGE_ID: 16232QS 1613 C++ */

#include <algorithm>
#include <cstdio>
using namespace std;

static const int MAX_N = 70000;
static const int MAX_Q = 70000;

struct tramStats_t {
	int index;
	int volume;
};


bool operator < (const tramStats_t& a, const tramStats_t& b)
{
	return (a.volume < b.volume) || (a.volume == b.volume && a.index < b.index);
}

tramStats_t tramStats[MAX_N];
char result[MAX_Q + 1];

int main()
{
	int n, q;
	tramStats_t l, r;

	scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &(tramStats[i].volume));
		tramStats[i].index = i + 1;
	}

	sort(tramStats, tramStats + n);

	scanf("%d", &q);
	for (int i = 0; i < q; ++i) {
		scanf("%d%d%d", &l.index, &r.index, &l.volume);
		r.volume = l.volume;

		const tramStats_t *lb = lower_bound(tramStats, tramStats + n, l);
		const tramStats_t *rb = lower_bound(tramStats, tramStats + n, r);

		result[i] = ((lb != tramStats + n) && (lb->volume == l.volume) && (lb != rb || (rb->volume == r.volume && rb->index == r.index))) ? '1' : '0';
	}

	puts(result);

	return 0;
}
