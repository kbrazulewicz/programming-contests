/* @JUDGE_ID: 16232QS 1656 C++ */

#include <algorithm>
#include <functional>
#include <iostream>
using namespace std;

static const int MAX_N = 9;

int soldiers[MAX_N * MAX_N];
int formation[MAX_N][MAX_N];

int offset[MAX_N] = {0, -1, 1, -2, 2, -3, 3, -4, 4};

int main()
{
	int n, s;

	scanf("%d", &n);
	s = n * n;

	for (int i = 0; i < s; i++) {
		scanf("%d", &soldiers[i]);
	}

	sort(soldiers, soldiers + s, greater<int>());

	for (int i = 0; i < n; i++) {
		int r = n / 2 + offset[i];
		for (int j = 0; j < n; j++) {
			int c = n / 2 + offset[j];

			formation[r][c] = soldiers[i * n + j];
		}
	}


	for (int r = 0; r < n; r++) {
		for (int c = 0; c < n; c++) {
			printf("%s%d", c == 0 ? "" : " ", formation[r][c]);
		}
		printf("\n");
	}

	return 0;
}
