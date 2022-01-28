#include <algorithm>
#include <cstdio>
#include <map>
using namespace std;

#undef DEBUG

#define FOR(E, I) for(auto E = I.begin(); E != I.end(); E++)

const unsigned int MAX_N = 500000;
const unsigned int MAX_M = 500000;

unsigned long long dailyGrowth[MAX_N];
unsigned long long accumulatedDailyGrowth[MAX_N + 1];

typedef struct {
	unsigned long long day;
	unsigned long long height;
	int beg;
} mowing;

mowing mowingHistory[MAX_M + 1];

map<int, mowing*> intervalsByEnd;


int findFirstFieldToMow(unsigned long long day, unsigned long long height)
{
	// stupid linear search
	FOR(i, intervalsByEnd) 
	{
		mowing* m = i->second;
		int intervalBeg = m->beg;
		int intervalEnd = i->first;
		unsigned long long heightAtTheIntervalBeg = m->height + (day - m->day) * dailyGrowth[intervalBeg];
		unsigned long long heightAtTheIntervalEnd = m->height + (day - m->day) * dailyGrowth[intervalEnd - 1];

		if (heightAtTheIntervalBeg > height)
		{
			return intervalBeg;
		}
		if (heightAtTheIntervalEnd > height)
		{
			unsigned long long heightDiff = height - m->height;
			unsigned long long dayDiff = day - m->day;

			unsigned long long minDailyGrowth = heightDiff / dayDiff + (heightDiff % dayDiff == 0 ? 0 : 1);

			return lower_bound(dailyGrowth + intervalBeg, dailyGrowth + intervalEnd, minDailyGrowth) - dailyGrowth;
		}
	}

	return -1;
}


int main()
{
	int n, m;

	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &dailyGrowth[i]);
	}

	// slowest growing first
	sort(dailyGrowth, dailyGrowth + n);
	
	// accumulated daily growth
	for (int i = 0; i < n; i++)
	{
		accumulatedDailyGrowth[i + 1] = i == 0 ? dailyGrowth[i] : accumulatedDailyGrowth[i] + dailyGrowth[i];
#ifdef DEBUG_DEBUG
		printf("accumulatedDailyGrowth[%d] : + %lld = %lld\n", i, dailyGrowth[i], accumulatedDailyGrowth[i + 1]);
#endif
	}

	mowingHistory[0] = mowing {0, 0, 0};
	intervalsByEnd[n] = mowingHistory + 0;

	for (int i = 1; i <= m; i++)
	{
		unsigned long long yield = 0;
		scanf("%Ld%Ld", &mowingHistory[i].day, &mowingHistory[i].height);

		// find which fields will be mowed
		int fieldIndex = findFirstFieldToMow(mowingHistory[i].day, mowingHistory[i].height);
		mowingHistory[i].beg = fieldIndex;

		if (fieldIndex >= 0)
		{
#ifdef DEBUG
			puts("Intervals before");
			FOR(ibe, intervalsByEnd) 
			{
				printf("  [%d, %d], day %lld, height %lld\n", ibe->second->beg, ibe->first - 1, ibe->second->day, ibe->second->height);
			}
#endif
			auto firstOverlappingInterval = intervalsByEnd.upper_bound(fieldIndex);
			mowing* firstOverlappingMowing = firstOverlappingInterval->second;

			for (auto h = firstOverlappingInterval; h != intervalsByEnd.end(); h++)
			{
				mowing& m = *(h->second);

				unsigned int beg = max(m.beg, fieldIndex);
				unsigned int end = h->first;

				yield += (accumulatedDailyGrowth[end] - accumulatedDailyGrowth[beg]) * (mowingHistory[i].day - m.day);
				yield += (m.height - mowingHistory[i].height) * (end - beg);
			}

			intervalsByEnd.erase(firstOverlappingInterval, intervalsByEnd.end());
#ifdef DEBUG
			puts("Intervals after erase");
			FOR(ibe, intervalsByEnd) 
			{
				printf("  [%d, %d], day %lld, height %lld\n", ibe->second->beg, ibe->first - 1, ibe->second->day, ibe->second->height);
			}
#endif
			if (fieldIndex != firstOverlappingMowing->beg)
			{
				intervalsByEnd[fieldIndex] = firstOverlappingMowing;
			}
			intervalsByEnd[n] = mowingHistory + i;

#ifdef DEBUG
			puts("Intervals after");
			FOR(ibe, intervalsByEnd) 
			{
				printf("  [%d, %d], day %lld, height %lld\n", ibe->second->beg, ibe->first - 1, ibe->second->day, ibe->second->height);
			}
#endif
		}

		printf("%lld\n", yield);
	}

	return 0;
}
