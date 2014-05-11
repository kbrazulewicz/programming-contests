#include <iostream>
#include <set>
using namespace std;

static const int MAX_N =  1000000;
static const int MAX_M = 10000000;

struct diagonal_t {
	int a;
	int b;
	int i;
} diagonal[MAX_M];

diagonal_t *a0[MAX_N], *a1[MAX_N];
set<int> d0, d1;

int main()
{
	int n, m;
	int a, b;

	scanf("%d%d", &n, &m);

	memset(a0, 0, sizeof(a0[0]) * n);
	memset(a1, 0, sizeof(a1[0]) * n);

	for (int i = 0; i < m; i++) {

		diagonal_t *d = &diagonal[i];

		scanf("%d%d", &a, &b);

		if (b < a) swap(a, b);
		d->a = --a;
		d->b = --b;
		d->i = i + 1;

		set<int>::const_iterator d0_b = d0.upper_bound(a);
		set<int>::const_iterator d0_e = d0.lower_bound(b);
		for (set<int>::const_iterator j = d0_b; j != d0_e; j++) {
			if (b < a0[*j]->b) {
				printf("%d %d\n", a0[*j]->i,  d->i);
				return 0;
			}
		}

		set<int>::const_iterator d1_b = d1.upper_bound(a);
		set<int>::const_iterator d1_e = d1.lower_bound(b);
		for (set<int>::const_iterator j = d1_b; j != d1_e; j++) {
			if (a1[*j]->a < a) {
				printf("%d %d\n", a1[*j]->i,  d->i);
				return 0;
			}
		}

		if (a0[a] == NULL) {
			a0[a] = d;
			d0.insert(a);
		} else if (a0[a]->b < b) {
			a0[a] = d;
		}
		if (a1[b] == NULL) {
			a1[b] = d;
			d1.insert(b);
		} else if (a < a1[b]->a) {
			a1[b] = d;
		}
	}

	printf("NIE\n");

	return 0;
}
