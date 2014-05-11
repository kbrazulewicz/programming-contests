#include <stdio.h>

int main()
{
	int l, c, i, r;

	scanf("%d", &l);
	for (i = 0; i < l; i++) {
		scanf("%d", &c);

		if (c == 0) {
			r = 0;
		} else if (c % 2 == 0) {
			if (c % 4 == 0) {
				r = (c / 2 - 2) / 2;
			} else {
				r = -1;
			}
		} else {
			r = (c - 1) / 2;
		}

		printf("%d\n", r);
	}
	return 0;
}
