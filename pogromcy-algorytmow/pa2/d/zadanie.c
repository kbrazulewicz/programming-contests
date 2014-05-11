#include <stdio.h>

int main()
{
	int bugsTotal, bugsToCatch;
	int i, x1, x2, y1, y2;

	/* data entry */
	scanf("%d %d\n", &bugsTotal, &bugsToCatch);
	for (i = 0; i < bugsToCatch; i++) {
		scanf("%d %d %d %d\n", &x1, &y1, &x2, &y2);
	}
	
	printf("Hello world\n");
	return 0;
}
