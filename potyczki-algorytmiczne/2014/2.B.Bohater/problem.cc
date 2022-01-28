#include <algorithm>
#include <cstdio>
using namespace std;

#undef DEBUG

const int MAX_N = 100000;

typedef struct
{	
	int d, a;	
	int gain;
	bool canBeFirst;
} duel_t;

bool duelSortFunction(duel_t *x, duel_t *y) 
{
#ifdef DEBUG
	printf("duelSortFunction x[%d, %d] y[%d, %d]\n", x->d, x->a, y->d, y->a);
#endif
	if (x->canBeFirst && y->canBeFirst)
	{
		return x->d < y->d;
	}
	else if (x->canBeFirst || y->canBeFirst)
	{
		return x->canBeFirst;
	}

	if (x->gain >= 0 && y->gain >= 0)
	{
		return x->d < y->d;
	}
	else if (x->gain < 0 && y->gain < 0)
	{
		int xFirstMin = y->d + 1 - x->gain;
		int yFirstMin = x->d + 1 - y->gain;

		if (xFirstMin == yFirstMin)
		{
			return x->d > y->d;
		}

		return xFirstMin < yFirstMin;
	}
	else return x->gain > 0;
}

duel_t duel[MAX_N];
duel_t* duelSort[MAX_N];

int main()
{
	int n, z;

	scanf("%d%d", &n, &z);
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d", &duel[i].d, &duel[i].a);
		duel[i].gain = duel[i].a - duel[i].d;
		if (duel[i].gain >= 0 && duel[i].d < z)
		{
			duel[i].canBeFirst = true;
		}
		duelSort[i] = duel + i;
	}

	sort(duelSort, duelSort + n, duelSortFunction);

#ifdef DEBUG
	for (int i = 0; i < n; i++)
	{
		printf("d: %d, a: %d\n", duelSort[i]->d, duelSort[i]->a);
	}
#endif

	for (int i = 0; i < n; i++)
	{
		z -= duelSort[i]->d;

		if (z <= 0)
		{
			puts("NIE");
			return 0;
		}
		
		z += duelSort[i]->a;
	}

	puts("TAK");

	for (int i = 0; i < n; i++)
	{
		printf("%d%s", duelSort[i] - duel + 1, i == n - 1 ? "\n" : " ");
	}

	return 0;
}
