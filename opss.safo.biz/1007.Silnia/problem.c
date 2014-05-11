#include <stdio.h>

int main()
{
	int n, s;

	scanf("%d", &n);

	switch(n) {
		case 0:
		case 1: s = 1; break;
		case 2: s = 2; break;
		case 3: s = 6; break;
		case 4: s = 4; break;
		default: s = 0; 
	}

	printf("%d\n", s);
	return 0;
}
