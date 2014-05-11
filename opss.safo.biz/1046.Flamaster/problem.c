#include <stdio.h>

void rle()
{
	char i, p = getchar();
	int c = 1;

	do {
		i = getchar();
		if (i == p) {
			c++;
		} else {
			putchar(p);
			if (c == 2) {
				putchar(p);
			} else if (c > 2) {
				printf("%d", c);
			}
			c = 1;
		}
		p = i;
	} while (i != '\n');
}

int main()
{
	int c;

	scanf("%d\n", &c);

	while(c--) {
		rle();
		putchar('\n');
	}
	
	return 0;
}
