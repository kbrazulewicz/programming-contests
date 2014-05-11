#include <algorithm>
#include <cstdio>
using namespace std;

static const int MAX_B = 100000;

int pIn[MAX_B], pOut[MAX_B];

int main()
{
	int b;

	scanf("%d", &b);
	for (int i = 0; i < b; i++) {
		scanf("%d%d", pIn + i, pOut + i);
	}

	sort(pIn,  pIn + b);
	sort(pOut, pOut + b);

	int iPIn  = 0, iPOut = 0;
	int count = 0, maxCount = 0;

	while (iPIn < b) {
		if (pIn[iPIn] < pOut[iPOut]) {
			iPIn++;
			maxCount = max(maxCount, ++count);
		} else {
			iPOut++;
			count--;
		}
	}

	printf("%d\n", maxCount);
	return 0;
}
