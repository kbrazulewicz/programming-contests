/* @JUDGE_ID: 16232QS 1146 C++ */

#include <algorithm>
#include <cstdio>
using namespace std;

static const int MAX_N = 100;
static const int MIN_X = -127;

int input[MAX_N][MAX_N];
int partialSums[MAX_N][MAX_N][MAX_N + 1];

int calculateBrute(int n)
{
	int maxValue = MIN_X;

	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			partialSums[x][y][1] = input[x][y];
			maxValue = max(maxValue, partialSums[x][y][1]);
		}
		for (int x = 0; x < n; x++) {
			for (int w = 2, wLimit = n - x; w <= wLimit; w++) {
				partialSums[x][y][w] = partialSums[x][y][w - 1] + partialSums[x + w - 1][y][1];
				maxValue = max(maxValue, partialSums[x][y][w]);
			}
		}
	}

	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			for (int w = 1, wLimit = n - x; w <= wLimit; w++) {
				int blockSum = partialSums[x][y][w];
				for (int h = 2, hLimit = n - y; h <= hLimit; h++) {
					blockSum += partialSums[x][y + h - 1][w];
					maxValue = max(maxValue, blockSum);
				}
			}
		}
	}

	return maxValue;
}



int main()
{
	int n;

	scanf("%d", &n);
	for (int i = 0, iLimit = n * n; i < iLimit; i++) {
		scanf("%d", &input[i % n][i / n]);
	}

	printf("%d\n", calculateBrute(n));

	return 0;
}
