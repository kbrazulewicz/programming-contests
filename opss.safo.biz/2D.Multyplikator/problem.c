#include <stdio.h>
#include <math.h>

int aMul[1000];

int main()
{
	int c, n, a;


	scanf("%d", &c);

	while (c--) {
		memset(aMul, 0, sizeof(aMul));
		scanf("%d", &n);

		while (n--) {
			scanf("%d", &a);
			aMul[a]++;
		}

		if (aMul[0]) {
			printf("1\n");
		} else {
			unsigned int m = 1;
			double ml = 0.0;

			for (int i = 1; i < 1000; i++) {
				while (aMul[i]) {
					m *= i;
					if (m > 4000000) {
						ml += log(m);
						m = 1;
					}
					aMul[i]--;
				}
			}

			ml += log(m);
			ml /= log(10);
			printf("%d\n", (int) (floor(ml) + 1));
		}
	}

	return 0;
}
