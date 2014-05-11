#include <stdio.h>
using namespace std;

int main()
{
	int netPair;
	int nodesA, nodesB, edgesA, edgesB;
	int a, b;

	scanf("%d", &netPair);

	for (int i = 0; i < netPair; i++) {
		scanf("%d", &nodesA);
		edgesA = 2 * nodesA - 3;
		for (int j = 0; j < edgesA; j++) {
			scanf("%d %d", &a, &b);
		}
		scanf("%d", &nodesB);
		edgesB = 2 * nodesB - 3;
		for (int j = 0; j < edgesB; j++) {
			scanf("%d %d", &a, &b);
		}

		if (nodesA != nodesB) {
			printf("NIE\n");
		} else {
			printf("MOZLIWE\n");
		}
	}

	return 0;
}
