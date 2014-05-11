/* @JUDGE_ID: 16232QS 1640 C++ */

#include <algorithm>
#include <iostream>
#include <cmath>
using namespace std;

static const int MAX_DAEMONS = 100;

typedef struct {
	int x;
	int y;
	double d;
} Daemon;

struct DaemonDistanceReversedSort
{
	bool operator()(const Daemon& d1, const Daemon& d2) const
	{
		return d1.d > d2.d;
	}
}; 

Daemon daemons[MAX_DAEMONS];

int main()
{
	int n, x, y;
	int xMin = 0, xMax = 0, yMin = 0, yMax = 0;

	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d%d", &x, &y);

		daemons[i].x = x;
		daemons[i].y = y;
		xMin = min(xMin, x);
		xMax = max(xMax, x);
		yMin = min(yMin, y);
		yMax = max(yMax, y);
	}

	x = xMin - 1; y = yMin - 1;

	for (int i = 0; i < n; i++) {
		int dX = daemons[i].x - x;
		int dY = daemons[i].y - y;
		daemons[i].d = sqrt((double)dX * dX + dY * dY);
	}

	sort(daemons, daemons + n, DaemonDistanceReversedSort());

	printf("%d %d %.9f\n", x, y, daemons[0].d);

	return 0;
}
