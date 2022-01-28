#include <algorithm>
#include <cstdio>
#include <list>
using namespace std;

/*
1D bin packing problem
http://www.or.deis.unibo.it/kp/Chapter8.pdf
 */

#undef DEBUG

#define FOR(E, I) for(typeof(I.begin()) E = I.begin(); E != I.end(); E++)

const int MAX_N = 24;
const int MAX_M = 100;

int a[MAX_N];
int c[MAX_M];

int bppBestFitDecreasing(int n, int m)
{
	sort(a, a + n, std::greater<int>());
	sort(c, c + m, std::greater<int>());

	list<int> bins;
	list<int> usedBins;

	for (int i = 0; i < m; bins.push_back(c[i]), i++);

	for (int i = 0; i < n; i++)
	{
#ifdef DEBUG
		printf("Checking item of size %d\n", a[i]);
#endif

		usedBins.sort(std::less<int>());

		if (!usedBins.empty() && usedBins.back() >= a[i])
		{
#ifdef DEBUG
			printf("biggest bin %d\n", usedBins.back());
#endif				
			FOR(ub, usedBins)
			{
				if (*ub >= a[i])
				{
					*ub -= a[i];
				}
			}
		}
		else
		{
#ifdef DEBUG
			if (bins.empty())
			{
				printf("no unitialized bins\n");
			}
			else
			{
				printf("biggest unitialized bin %d\n", bins.front());
			}
#endif				
			if (!bins.empty() && bins.front() >= a[i])
			{
				usedBins.push_back(bins.front() - a[i]);
				bins.pop_front();
			}
			else return -1;
		}
	}

	return usedBins.size();
}

int bppFirstFitDecreasing(int n, int m)
{
	sort(a, a + n, std::greater<int>());
	sort(c, c + m, std::greater<int>());

	list<int> bins;
	list<int> usedBins;

	for (int i = 0; i < m; bins.push_back(c[i]), i++);

	for (int i = 0; i < n; i++)
	{
#ifdef DEBUG
		printf("Checking item of size %d\n", a[i]);
#endif
		usedBins.sort(std::greater<int>());
		if (!usedBins.empty() && usedBins.front() >= a[i])
		{
#ifdef DEBUG
			printf("biggest bin %d\n", usedBins.front());
#endif				
			usedBins.front() -= a[i];
		}
		else
		{
#ifdef DEBUG
			if (bins.empty())
			{
				printf("no unitialized bins\n");
			}
			else
			{
				printf("biggest unitialized bin %d\n", bins.front());
			}
#endif				
			if (!bins.empty() && bins.front() >= a[i])
			{
				usedBins.push_back(bins.front() - a[i]);
				bins.pop_front();
			}
			else return -1;
		}
	}

	return usedBins.size();
}


int main()
{
	int n, m;

	scanf("%d%d", &n, &m);

	for (int i = 0; i < n; scanf("%d", &a[i++]));
	for (int i = 0; i < m; scanf("%d", &c[i++]));

	{
		int usedBins = min(bppFirstFitDecreasing(n, m), bppBestFitDecreasing(n, m));
		if (usedBins > 0)
		{
			printf("%d\n", usedBins);
		}
		else
		{
			puts("NIE");
		}
	}

	return 0;
}
