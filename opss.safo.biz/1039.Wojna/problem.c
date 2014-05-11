#include <stdio.h>

#define MAX(x, y) (x > y ? x : y)
#define MIN(x, y) (x < y ? x : y)
#define SWAP(x, y) { int tmp = x; x = y; y = tmp }
#define SIGNUM(x) (x > 0 ? 1 : x < 0 ? -1 : 0)

int calculate()
{
	int lX, lY, k, x00, y00, x0, y0, x1, y1, cutNo = 0;
	int level;

	scanf("%d%d%d%d%d", &lX, &lY, &k, &x00, &y00);
	x0 = x00; y0 = y00; level = SIGNUM(y0 - lY);

	while (k--) {
		if (k) {
			scanf("%d%d", &x1, &y1);
		} else {
			x1 = x00; y1 = y00;
		}

		//printf("[%d;%d] [%d;%d] [%d]\n", x0, y0, x1, y1, level);

		if (lX == x0 && lY == y0) {
			cutNo = 1;
			break;
		}

		if (lX == x0 && lX == x1 && lY >= MIN(y0, y1) && lY <= MAX(y0, y1)) {
			cutNo = 1;
			break;
		}

		if (lY == y0 && lY == y1 && lX >= MIN(x0, x1) && lX <= MAX(x0, x1)) {
			cutNo = 1;
			break;
		}

		if ((level == 1 && y1 < lY) || (level == -1 && y1 > lY)) {
			level = -level;
			int xMin = MIN(x0, x1);
			int xMax = MAX(x0, x1);
			if (xMax >= lX) {
				if (xMin >= lX) cutNo++;
				else {
					double a = lY - y0, b = lY - y1, c = y1 - y0;
					a *= x1; b *= x0; c *= lX;
					double d = (a - b - c) / (y1 - y0);

					if (d >= 0) cutNo++;
				}
			}
		}
		if (level == 0) {
			level = SIGNUM(y1 - lY);
		}

		x0 = x1; y0 = y1;
	}

	while (k-- > 1) scanf("%d%d", &x1, &y1);

	return cutNo % 2;
}

int main()
{
	int d;
	scanf("%d", &d);
	while (d--) puts(calculate() ? "TAK" : "NIE");
	return 0;
}
