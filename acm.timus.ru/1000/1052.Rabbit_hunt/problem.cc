/* @JUDGE_ID: 16232QS 1052 C++ */

#include <cstdio>
using namespace std;

static const int MAX_RABBITS = 200;

struct {
	int x;
	int y;
} rabbit[MAX_RABBITS + 1];

int det[MAX_RABBITS + 1][MAX_RABBITS + 1];

int main()
{
	int n;
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &rabbit[i].x, &rabbit[i].y);
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			det[i][j] = rabbit[i].x * rabbit[j]
		}
	}

	return 0;
}
