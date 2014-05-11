#define DEBUG 1

#if DEBUG
#define PRINTF(x) printf x
#else
#define PRINTF(x)
#endif

#define MIN(x,y) (x < y ? x : y)
#define MAX(x,y) (x > y ? x : y)

#include <stdio.h>
#include <string.h>

#define MAX_ODWAZ 1000
#define MAX_WAGA  50000

int elements[MAX_ODWAZ];

int main()
{
	int elementNumber;
	int i;

	scanf("%d\n", &elementNumber);

	for (i = 0; i < elementNumber; i++) {
		scanf("%d\n", &(elements[i]));
	}
	
	return 0;
}
