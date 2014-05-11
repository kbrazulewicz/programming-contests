#include <stdio.h>
#include <stdlib.h>

unsigned int calculate(unsigned int n)
{
	return ((1 + n) * n) >> 1;
}

int main()
{
	int n, i;

	scanf("%d", &n);

	while (n--) {
		scanf("%d", &i);

		switch(i) {
			case -1: printf("%d\n", 0); break;
			case 0:  printf("%d\n", 1); break;
			default: {
						 if (i > 0) {
							 printf("%u\n", calculate(abs(i)));
						 } else {
							 printf("-%u\n", calculate(abs(i)) - 1);
						 }
					 }
		}
	}

	return 0;
}
