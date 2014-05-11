/* @JUDGE_ID: 16232QS 1645 C++ */

#include <iostream>
using namespace std;

static const int MAX_N = 2000;

int participants[MAX_N + 1];
int best[MAX_N + 1];
int worst[MAX_N + 1];

int main()
{
	int n;

	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		scanf("%d", &participants[i]);
	}

	for (int i = 1; i <= n; i++) {
		int startingNumber = participants[i];
		best[startingNumber] = 1;
		worst[startingNumber] = i + n - startingNumber;
		for (int j = 1; j < i; j++) {
			if (participants[j] > startingNumber) {
				best[startingNumber]++;
				worst[startingNumber]--;
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		printf("%d %d\n", best[i], worst[i]);
	}

	return 0;
}
