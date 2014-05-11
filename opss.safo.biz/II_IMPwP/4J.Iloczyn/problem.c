#include <stdio.h>

#define N_MAX 3001
char iloczyny[N_MAX * N_MAX + 1];

int main()
{
	int c, n;

//	cin >> c;
//	for (int i = 0; i < c; i++) {
//		cin >> n;
//	}

	int ileIloczynow = 0;
	int ileIloczynowTeraz = 0;

	for (int i = 1; i < N_MAX; i++) {
		ileIloczynowTeraz = 0;
		for (int j = 1; j <= i; j++) {
			if (iloczyny[i * j] == 0) {
				ileIloczynow++;
				ileIloczynowTeraz++;
				iloczyny[i * j] = 1;
			}
		}

		printf("%d +%d %d\n", i, ileIloczynowTeraz, ileIloczynow);
	}
	return 0;
}
