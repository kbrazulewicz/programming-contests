#include <stdio.h>

#define MAX_N 5000000

char input[2 * MAX_N];

int x[4][4] = {
	{0, 2, 0, 2},
	{0, 0, 0, 0},
	{0, 2, 0, 2},
	{0, 0, 0, 0},
};

int main()
{
	int i, n, r;
	char *p1, *p2;

	scanf("%d\n", &n);
	fgets(input, sizeof(input), stdin);

	i = 0;
	r = 0;

	while (i < n - 1) {
		p1 = input + 2 * i;
		p2 = input + 2 * i + 2;

		if (x[(*p1) - 'A'][(*p2) -'A'] == 2) {
			i += 2;
			r += 2;
		} else if (*p2 == 'A' || *p2 == 'C') {
			(*p2)++; 
			i++;
			r++;
		} else {
			i++;
			r++;
		}
	}

	printf("%d\n", r);

	return 0;
}
