#include <algorithm>
#include <cstdio>
using namespace std;

#undef DEBUG

#define SUMA_CIAGU_ARYTMETYCZNEGO(n) (((n + 1) * n) / 2)

const int MAX_N = 2000;
const int MAX_C = 1e9;

typedef struct
{
	int i, j;
	int cost;
} range_t;

typedef struct
{	
	int index;
	range_t *range;
	int o_cnt; // number of ranges opening here
	int c_cnt; // number of ranges closing here
} kubek_t;

bool sortKubekPtrCostDesc(kubek_t *i, kubek_t *j) { return i->range->cost > j->range->cost; }
bool sortRangesCostDescLengthAscStartAsc(range_t *a, range_t *b) 
{
	if (a->cost == b->cost)
	{
		if ((a->j - a->i) == (b->j - b->i))
		{
			return a->i < b->i;
		}
		else return (a->j - a->i) < (b->j - b->i);
	}
	else return a->cost > b->cost; 
}
bool sortRangesCostDescLengthDescStartAsc(range_t *a, range_t *b) 
{
	if (a->cost == b->cost)
	{
		if ((a->j - a->i) == (b->j - b->i))
		{
			return a->i < b->i;
		}
		else return (a->j - a->i) > (b->j - b->i);
	}
	else return a->cost > b->cost; 
}
bool sortRangesCostAscLengthAscStartAsc(range_t *a, range_t *b) 
{
	if (a->cost == b->cost)
	{
		if ((a->j - a->i) == (b->j - b->i))
		{
			return a->i < b->i;
		}
		else return (a->j - a->i) < (b->j - b->i);
	}
	else return a->cost < b->cost; 
}
bool sortRangesLengthAscCostAscStartAsc(range_t *a, range_t *b) 
{
	if ((a->j - a->i) == (b->j - b->i))
	{
		if (a->cost == b->cost)
		{
			return a->i < b->i;
		}
		else return a->cost < b->cost; 
	}
	else return (a->j - a->i) < (b->j - b->i);
}

range_t  r[MAX_N][MAX_N];
range_t* rPtr[SUMA_CIAGU_ARYTMETYCZNEGO(MAX_N)];

kubek_t  k[MAX_N];
kubek_t* kCandidates[MAX_N];
kubek_t* kPtr[MAX_N];


int getCandidates(const range_t& range, kubek_t* candidates[])
{
	int candidateCount = 0;
	for (int x = range.i; x <= range.j; x++)
	{
		if (range.cost < k[x].range->cost)
		{
			candidates[candidateCount++] = &k[x];
		}
	}
	sort(candidates, candidates + candidateCount, sortKubekPtrCostDesc);

	return candidateCount;
}

bool canUseRangeFor(int n, const range_t& range, const kubek_t& candidate)
{
	// verify range to be removed
	const range_t* rToBeRemoved = candidate.range;

	// if we're removing range start, then previous cup must have range end
	if (rToBeRemoved->i != 0 && rToBeRemoved->i != range.i && k[rToBeRemoved->i].o_cnt == 1 && k[rToBeRemoved->i - 1].c_cnt == 0)
	{
#ifdef DEBUG
		printf("cup [%d]: not using range [%d -> %d] due to missing closing on cup [%d]\n", 
			candidate.index, range.i, range.j, rToBeRemoved->i - 1);
		printf("cup [%d]: range to be removed [%d -> %d]\n", candidate.index, rToBeRemoved->i, rToBeRemoved->j);
#endif
		return false;
	}

	// if we're removing range end, then next cup must have range start
	if (rToBeRemoved->j != n - 1 && rToBeRemoved->j != range.j && k[rToBeRemoved->j].c_cnt == 1 && k[rToBeRemoved->j + 1].o_cnt == 0)
	{
#ifdef DEBUG
		printf("cup [%d]: not using range [%d -> %d] due to missing opening on cup [%d]\n", 
			candidate.index, range.i, range.j, rToBeRemoved->j + 1);
		printf("cup [%d]: range to be removed [%d -> %d]\n", candidate.index, rToBeRemoved->i, rToBeRemoved->j);
#endif
		return false;
	}

	return true;	
}


void optimalCost(int n)
{
	// first unoptimal cost (all ranges of length 1)
	for (int i = 0; i < n; k[i].index = i, k[i].range = &r[i][i], k[i].o_cnt = 1, k[i].c_cnt = 1, i++);

	// sort ranges
	int rangeCount = SUMA_CIAGU_ARYTMETYCZNEGO(n);
	sort(rPtr, rPtr + rangeCount, sortRangesCostAscLengthAscStartAsc);

	for (int x = 0; x < rangeCount; x++)
	{		
		range_t* newRange = rPtr[x];
		// skip 1-element ranges
		if (newRange->i == newRange->j) continue;

		int candidateCount = getCandidates(*newRange, kCandidates);

#ifdef DEBUG
		printf("range [%d -> %d], cost [%d], candidates [%d]\n", newRange->i, newRange->j, newRange->cost, candidateCount);
#endif		

		for (int y = 0; y < candidateCount; y++)
		{
			kubek_t* candidate = kCandidates[y];

			if (canUseRangeFor(n, *newRange, *candidate))
			{
				// not using old range anymore
				range_t* oldRange = candidate->range;
				range_t* newRange = rPtr[x];
#ifdef DEBUG
				printf("cup [%d]: removing range [%d -> %d]\n", candidate->index, oldRange->i, oldRange->j);
#endif
				k[oldRange->i].o_cnt--;
				k[oldRange->j].c_cnt--;

#ifdef DEBUG
				printf("cup [%d]: using range [%d -> %d]\n", candidate->index, newRange->i, newRange->j);
#endif
				candidate->range = newRange;
				k[newRange->i].o_cnt++;
				k[newRange->j].c_cnt++;
				break;				
			}
		}
	}
}


int main()
{
	// input
	int n;
	scanf("%d", &n);

	for (int i = 0, l = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			r[i][j].i = i; r[i][j].j = j;
			scanf("%d", &r[i][j].cost);

			rPtr[l++] = &r[i][j];
		}
	}

	// calculate
	optimalCost(n);

	// output
	long long totalCost = 0;
	for (int i = 0; i < n; totalCost += k[i++].range->cost);

	printf("%lld\n", totalCost);

	return 0;
}
