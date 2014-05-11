/* @JUDGE_ID: 16232QS 1178 C++ */

#include <algorithm>
#include <iostream>
using namespace std;

static const int MAX_N = 10000;

typedef struct {
	int x;
	int y;
	size_t n;
} town_t;

town_t town[MAX_N];

bool operator < (const town_t& a, const town_t& b)
{
	return a.x < b.x || (a.x == b.x && a.y < b.y);
}

int main()
{
	int n;

	scanf("%d", &n);

	for (int i = 0; i < n; i++) 
	{
		scanf("%d%d", &town[i].x, &town[i].y);
		town[i].n = i + 1;
	}

	sort(town, town + n);

	for (int i = 0; i < n; i += 2) 
	{
		printf("%d %d\n", town[i].n, town[i + 1].n);
	}

	return 0;
}
