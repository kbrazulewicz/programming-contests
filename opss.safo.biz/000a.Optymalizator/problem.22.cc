//
// Subset sum problem
//

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

#define MAX_N 500
#define MAX_A 500
#define MIN_A -500
#define MAX_S (MAX_N * MAX_A)
#define MIN_S (MAX_N * MIN_A)
#define RANGE_S (MAX_S + 1)


unsigned int gMaskOne[32] = {
	1 << 31, 1 << 30, 1 << 29, 1 << 28, 1 << 27, 1 << 26, 1 << 25, 1 << 24,
	1 << 23, 1 << 22, 1 << 21, 1 << 20, 1 << 19, 1 << 18, 1 << 17, 1 << 16,
	1 << 15, 1 << 14, 1 << 13, 1 << 12, 1 << 11, 1 << 10, 1 <<  9, 1 <<  8,
	1 <<  7, 1 <<  6, 1 <<  5, 1 <<  4, 1 <<  3, 1 <<  2, 1 <<  1, 1 <<  0
};

static const int FIELD_WIDTH = sizeof(unsigned int) * 8;
unsigned int optTest[RANGE_S / FIELD_WIDTH + 1];

bool optymalizator()
{
	int n, s, a, minS = MAX_S, maxS = MIN_S;
	unsigned int sOffset, sMask;
	int sRange;
	unsigned int aOffset, aShift, aAbsShift;
	int j, k;
	int aList[MAX_N];

	memset(optTest, 0, sizeof(optTest));

	scanf("%d%d", &n, &s);

	for (int i = 0; i < n; i++) {
		scanf("%d", &a);
		if (i == 0) {
			maxS = minS = a;
		} else {
			maxS = max(max(maxS, maxS + a), a);
			minS = min(min(minS, minS + a), a);
		}
		aList[i] = a;
	}

	if (s < minS || s > maxS) return false;

	sOffset = (s - minS) / FIELD_WIDTH;
	sMask   = gMaskOne[(s - minS) % FIELD_WIDTH];
	sRange  = (maxS - minS) / FIELD_WIDTH;

	//printf("minS [%d] maxS [%d]\n", minS, maxS);
	//printf("S [%d] offset [%d], mask [%x], range [%d], max range [%d]\n", s, sOffset, sMask, sRange, sizeof(optTest) / sizeof(optTest[0]));

	for (int i = 0; i < n; i++) {
		a = aList[i];
		aOffset = a / FIELD_WIDTH;
		aShift  = a % FIELD_WIDTH;
		aAbsShift = abs(a);

		// printf("A [%d] offset [%d], shift[%d]\n",a, aOffset, aShift);

		if (a > 0) {
			if (aAbsShift) {
				for (j = sRange, k = j - aOffset; k > 0; j--, k--) {
					optTest[j] |= optTest[k] >> aAbsShift;
					optTest[j] |= optTest[k - 1] << (32 - aAbsShift);
				}
				optTest[j] |= optTest[k] >> aAbsShift;
			} else {
				for (j = sRange, k = j - aOffset; k >= 0; optTest[j--] |= optTest[k--]);
			}
		} else if (a < 0) {
			if (aAbsShift) {
				for (j = 0, k = j - aOffset; k < sRange; j++, k++) {
					optTest[j] |= optTest[k] << aAbsShift;
					optTest[j] |= optTest[k + 1] >> (32 - aAbsShift);
				}
				optTest[j] |= optTest[k] << aAbsShift;
			} else {
				for (j = 0, k = j - aOffset; k <= sRange; optTest[j++] |= optTest[k++]);
			}
				
		}
		//printf("X1 [%.8x]\n", optTest[0]);
		//printf("A [%d] offset [%d], mask [%x]\n", a, (a - minS) / FIELD_WIDTH, gMaskOne[(a - minS) % FIELD_WIDTH]);
		optTest[(a - minS) / FIELD_WIDTH] |= gMaskOne[(a - minS) % FIELD_WIDTH];
		//printf("X2 [%.8x]\n", optTest[0]);

		if ((optTest[sOffset] & sMask) != 0) return true;
	}

	return false;
}

int main()
{
	int c;
	scanf("%d", &c);

	while (c--) {
		printf("%s\n", optymalizator() ? "TAK" : "NIE");
	}
	
	return 0;
}
