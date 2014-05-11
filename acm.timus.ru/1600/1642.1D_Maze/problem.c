/* @JUDGE_ID: 16232QS 1642 C */

#include <stdio.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

int main()
{
	int n, x, o;
	int l = -1000, r = 1000;
	int a, b;

	scanf("%d%d", &n, &x);
	while (n--) {
		scanf("%d", &o);
		if (o < 0) {
			l = MAX(l, o);
		} else {
			r = MIN(r, o);
		}
	}

	if (x > 0) {
		if (x > r) {
			printf("Impossible\n");
		} else {
			printf("%d %d\n", x, 2 * abs(l) + x);
		}
	} else {
		if (x < l) {
			printf("Impossible\n");
		} else {
			printf("%d %d\n", 2 * r + abs(x), abs(x));
		}
	}

	return 0;
}
