#include <cstdio>
#include <list>
#include <set>
using namespace std;

#undef DEBUG

#define EVEN(X) (X % 2 == 0)
#define ODD(X) (X % 2 != 0)

#define FOR(E, I) for(typeof(I.begin()) E = I.begin(); E != I.end(); E++)

typedef struct 
{
	int x1A, x2A, y1A, y2A;
	int x1B, x2B, y1B, y2B;
	int l; // furthest left this car had to be
	int r; // furthest right this car had to be
	int height;
} car_t;

struct event_t
{
	bool isLeftSide;
	int location;
	int height;

	bool operator< (const event_t& rhs)
	{
		if (location == rhs.location)
		{
			return !isLeftSide;
		}

		return location < rhs.location;
	}
};

const int MAX_N = 50000;

car_t car[MAX_N];

bool testujParking(int n, int w)
{
	list<event_t> events;

	for (int i = 0; i < n; i++)
	{
#ifdef DEBUG
//		printf("car %d: l %d r %d h %d\n", i, car[i].l, car[i].r, car[i].height);
#endif
		event_t startOfCar;
		event_t endOfCar;

		startOfCar.isLeftSide = true;
		startOfCar.location = car[i].l;
		startOfCar.height = car[i].height;
		endOfCar.isLeftSide = false;
		endOfCar.location = car[i].r;
		endOfCar.height = car[i].height;

		events.push_back(startOfCar);
		events.push_back(endOfCar);
	}

	events.sort();

	multiset<int> heights;

	while(!events.empty())
	{
		event_t &e = events.front();
		events.pop_front();

#ifdef DEBUG
		printf("event at %d, %s, height %d\n", e.location, e.isLeftSide ? "L" : "R", e.height);
#endif

		if (e.isLeftSide)
		{
			if (!heights.empty())
			{
				if (e.height + *heights.crbegin() > w) 
				{
#ifdef DEBUG
					printf("event height %d, max stored height %d\n", e.height, *heights.crbegin());
#endif
					return false;
				}
			}
			
			heights.insert(e.height);
		}
		else
		{
			heights.erase(heights.find(e.height));
		}
	}

	return true;
}

int main()
{
	int t;
	scanf("%d", &t);

	while (t--)
	{
		int n, w;
		scanf("%d%d", &n, &w);

		for (int i = 0; i < n; i++)
		{
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

			car[i].x1A = min(x1, x2);
			car[i].x2A = max(x1, x2);
			car[i].y1A = min(y1, y2);
			car[i].y2A = max(y1, y2);

			car[i].height = car[i].y2A - car[i].y1A;
		}
		for (int i = 0; i < n; i++)
		{
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

			car[i].x1B = min(x1, x2);
			car[i].x2B = max(x1, x2);
			car[i].y1B = min(y1, y2);
			car[i].y2B = max(y1, y2);

			car[i].l = min(car[i].x1A, car[i].x1B);
			car[i].r = max(car[i].x2A, car[i].x2B);
		}

		puts(testujParking(n, w) ? "TAK" : "NIE");
	}

	return 0;
}
