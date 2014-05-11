#include <algorithm>
#include <cstdio>
using namespace std;

#undef DEBUG

int main()
{
	int n, maxPairs;
	int l, r;
	int marginUp, marginDown;
	int lastHeight;

	scanf("%d", &n);
	maxPairs = n - 1;

	scanf("%d %d", &l, &r);
	marginUp = r;
	marginDown = l;
	lastHeight = r;

#ifdef DEBUG
	printf("L: %d; R: %d; MU: %d; MD: %d\n", l, r, marginUp, marginDown);
#endif

	while (--n) {
		scanf("%d %d", &l, &r);

		if (l + r >= lastHeight) {
			r = r + l - lastHeight;
			l = lastHeight;

			lastHeight = r;

			swap(marginUp, marginDown);

			marginUp = min(marginUp, r);
			marginDown = min(marginDown, l);
		} else if (lastHeight - (l + r) <= marginUp) {
			int pullUp = lastHeight - (l + r);
			lastHeight -= pullUp;
			marginUp -= pullUp;
			marginDown += pullUp;

			r = r + l - lastHeight;
			l = lastHeight;
			lastHeight = r;

			swap(marginUp, marginDown);

			marginUp = min(marginUp, r);
			marginDown = min(marginDown, l);
		} else {
			maxPairs--;
			marginUp = r;
			marginDown = l;
			lastHeight = r;
		}
#ifdef DEBUG
		printf("L: %d; R: %d; MU: %d; MD: %d\n", l, r, marginUp, marginDown);
#endif
	}

	printf("%d\n", maxPairs);

	return 0;
}
