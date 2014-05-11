#include <iostream>
using namespace std;

#undef PA_DEBUG

static const int MAX_N = 5000000 * 2;

int gHeight[MAX_N + 1];

int gField[MAX_N + 1];
int gFieldBeg = MAX_N / 2;
int gFieldEnd = gFieldBeg;

int main()
{
	int a, b, c, d, x, y, l;
	int minS, maxS;
	int pX = 0, pY = 0;
	int v;
	long long int noOfAlignments = 0;


	scanf("%d %d %d %d", &a, &b, &c, &d);

	memset(gHeight, 0, a * sizeof(gHeight[0]));
	minS = min(c, d); maxS = max(c, d);

	for (int i = 0; i < b; i++) {
		scanf("%d %d", &x, &l);

		y = x + l;

		if (l == 0) {
			gFieldBeg = MAX_N / 2;
			gFieldEnd = gFieldBeg;
		} else {
			if (x >= pY || y <= pX) {
				gFieldBeg = MAX_N / 2;
				gFieldEnd = gFieldBeg;
				gField[gFieldEnd++] = x; gHeight[x] = 1;
				gField[gFieldEnd++] = y; gHeight[y] = -1;
#ifdef PA_DEBUG
				printf("inserting %d %d\n", x, gHeight[x]);
				printf("inserting back %d %d\n", y, gHeight[y]);
#endif
			} else {
				if (x == pX) {
					gHeight[x]++;
#ifdef PA_DEBUG
					printf("updating %d %d\n", x, gHeight[x]);
#endif
				} else {
					int lv = 1, v;
					while (gFieldBeg < gFieldEnd && (v = gField[gFieldBeg]) <= x) {
						lv += gHeight[v];
						gFieldBeg++;
					}
					gField[--gFieldBeg] = x; gHeight[x] = lv;
#ifdef PA_DEBUG
					printf("inserting %d %d\n", x, gHeight[x]);
#endif
				}

				if (y == pY) {
					gHeight[y]--;
#ifdef PA_DEBUG
					printf("updating back %d %d\n", y, gHeight[y]);
#endif
				} else {
					int rv = -1, v;
					while (gFieldBeg < gFieldEnd && (v = gField[gFieldEnd - 1]) >= y) {
						rv += gHeight[v];
						gFieldEnd--;
					}
					gField[gFieldEnd++] = y; gHeight[y] = rv;
#ifdef PA_DEBUG
					printf("inserting back %d %d\n", y, gHeight[y]);
#endif
				}
			}
		}

		{
			int h = 0, p;

			int i = gFieldBeg;
			int ie = gFieldEnd;

			int loBS = 0, loBE = 0, hiBS = 0, hiBE = 0;

			while (i < ie && loBE == 0) {
				p = gField[i];
				h += gHeight[p];

				if (loBS == 0 && h >= minS) loBS = p;
				if (hiBS == 0 && h >= maxS) hiBS = p;
				if (loBS != 0 && loBE == 0 && h < minS) loBE = p;
				if (hiBS != 0 && hiBE == 0 && h < maxS) hiBE = p;

				i++;
			}

#ifdef PA_DEBUG
			printf("block lo [%d %d] hi [%d %d]\n", loBS, loBE, hiBS, hiBE);
#endif

			if (loBE - loBS >= maxS) {
				noOfAlignments += 1 + loBE - loBS - maxS;
			}

			if (minS != maxS && hiBE - hiBS >= minS) {
				noOfAlignments += 1 + hiBE - hiBS - minS;
			}
		}

		pX = x; pY = y;

#ifdef PA_DEBUG
		for (int i = gFieldBeg; i < gFieldEnd; i++) {
			int p = gField[i];
			printf("%d -> %d\n", p, gHeight[p]);
		}

		printf("%d %lld\n", i, noOfAlignments);
#endif

	}

	printf("%lld\n", noOfAlignments);
	return 0;
}
