#define DEBUG 1

#if DEBUG
#define PRINTF(x) printf x
#else
#define PRINTF(x)
#endif

#define MIN(a,b) a < b ? a : b;
#define MAX(a,b) a > b ? a : b;

#define MAX_NODES	10000
#define MAX_EDGES	20000
#include <stdio.h>
#include <string.h>

int gAdjList[MAX_NODES][2];
int gArcUsed[MAX_NODES][2];
unsigned char gAdjListCnt[MAX_NODES];
int gVisitOrder[MAX_NODES];
int gCompletionOrder[MAX_NODES];
int gLowestReachable[MAX_NODES];

int gStack[MAX_NODES];
int gNodes = 0;



int solution1() 
{
	/* first vertex on a stack */
	int v = 0, visitOrder = 0, completionOrder = 0;
	int stackP = 0, minLowestReachable, stronglyConnectedComponents = 0;
	int i;
	gStack[stackP] = 0;

	while (completionOrder < gNodes) {

		v = gStack[stackP];

		if (!gVisitOrder[v]) {
			gLowestReachable[v] = (gVisitOrder[v] = ++visitOrder) - 1;
			/*PRINTF(("Vertex [%d] visited as [%d]\n", v + 1, gVisitOrder[v]));*/
		}
		minLowestReachable = gLowestReachable[v];

		/* first possible descendant */
		if (gAdjListCnt[v] > 0) {
			int x = gAdjList[v][0];
			if (!gArcUsed[v][0]) {
				gArcUsed[v][0] = 1;
				if (!gVisitOrder[x]) {
					gStack[++stackP] = x;
					continue;
				}/*
				else if (!gCompletionOrder[x]) {
					PRINTF(("Back edge  %d -> %d\n", v + 1, x + 1));
				}
				else if (gVisitOrder[x] > gVisitOrder[v]) {
					PRINTF(("Down edge  %d -> %d\n", v + 1, x + 1));
				}
				else {
					PRINTF(("Cross edge %d -> %d\n", v + 1, x + 1));
				}*/
			}
			minLowestReachable = MIN(minLowestReachable, gLowestReachable[x]);
		}
		/* second possible descendant */
		if (gAdjListCnt[v] > 1) {
			int x = gAdjList[v][1];
			if (!gArcUsed[v][1]) {
				gArcUsed[v][1] = 1;
				if (!gVisitOrder[x]) {
					gStack[++stackP] = x;
					continue;
				}/*
				else if (!gCompletionOrder[x]) {
					PRINTF(("Back edge  %d -> %d\n", v + 1, x + 1));
				}
				else if (gVisitOrder[x] > gVisitOrder[v]) {
					PRINTF(("Down edge  %d -> %d\n", v + 1, x + 1));
				}
				else {
					PRINTF(("Cross edge %d -> %d\n", v + 1, x + 1));
				}*/
			}
			minLowestReachable = MIN(minLowestReachable, gLowestReachable[x]);
		}
		PRINTF(("Lowest reachable for [%d] is [%d]\n", v + 1, minLowestReachable + 1));

		if (minLowestReachable == gLowestReachable[v]) {
			PRINTF(("Strong component found at %d\n", v + 1));
			stronglyConnectedComponents++;
			/*
			do {
				PRINTF(("%d\n", gStack[--stackP]));
			} while (gStack[stackP] != v);
			*/
		}
		else gLowestReachable[v] = minLowestReachable;

		
		gCompletionOrder[v] = ++completionOrder;
		PRINTF(("Vertex [%d] completed as [%d]\n", v + 1, gCompletionOrder[v]));

		if (!stackP && completionOrder < gNodes) {
			for (i = 0; i < gNodes; i++) {
				if (!gVisitOrder[i]) {
					gStack[stackP] = i;
					break;
				}
			}
		}
		else stackP--;
	}

	return stronglyConnectedComponents;
}



int solution2() 
{
	/* first vertex on a stack */
	int v = 0, visitOrder = 0, completionOrder = 0;
	int stackP = 0, minLowestReachable, stronglyConnectedComponents = 0;
	int i;
	gStack[stackP] = 0;

	while (completionOrder < gNodes) {

		v = gStack[stackP];

		if (!gVisitOrder[v]) {
			gLowestReachable[v] = (gVisitOrder[v] = ++visitOrder) - 1;
			/*PRINTF(("Vertex [%d] visited as [%d]\n", v + 1, gVisitOrder[v]));*/
		}
		minLowestReachable = gLowestReachable[v];

		/* first possible descendant */
		if (gAdjListCnt[v] > 0) {
			int x = gAdjList[v][0];
			if (!gArcUsed[v][0]) {
				gArcUsed[v][0] = 1;
				if (!gVisitOrder[x]) {
					gStack[++stackP] = x;
					continue;
				}
			}
			minLowestReachable = MIN(minLowestReachable, gLowestReachable[x]);
		}
		/* second possible descendant */
		if (gAdjListCnt[v] > 1) {
			int x = gAdjList[v][1];
			if (!gArcUsed[v][1]) {
				gArcUsed[v][1] = 1;
				if (!gVisitOrder[x]) {
					gStack[++stackP] = x;
					continue;
				}
			}
			minLowestReachable = MIN(minLowestReachable, gLowestReachable[x]);
		}
		/*PRINTF(("Lowest reachable for [%d] is [%d]\n", v + 1, minLowestReachable + 1));*/

		if (minLowestReachable == gLowestReachable[v]) {
			PRINTF(("Strong component found at %d\n", v + 1));
			stronglyConnectedComponents++;
			/*
			do {
				PRINTF(("%d\n", gStack[--stackP]));
			} while (gStack[stackP] != v);
			*/
		}
		else gLowestReachable[v] = minLowestReachable;

		
		gCompletionOrder[v] = ++completionOrder;
		/*PRINTF(("Vertex [%d] completed as [%d]\n", v + 1, gCompletionOrder[v]));*/

		if (!stackP && completionOrder < gNodes) {
			for (i = 0; i < gNodes; i++) {
				if (!gVisitOrder[i]) {
					gStack[stackP] = i;
					break;
				}
			}
		}
		else stackP--;
	}

	return stronglyConnectedComponents;
}


int main()
{
	int nEdges;
	int i, from, to;
	int result = 0;

	/* data entry */
	scanf("%d %d\n", &gNodes, &nEdges);
	memset(gAdjListCnt, 0, sizeof(gAdjListCnt[0]) * gNodes);
	memset(gVisitOrder, 0, sizeof(gVisitOrder[0]) * gNodes);
	memset(gCompletionOrder, 0, sizeof(gCompletionOrder[0]) * gNodes);
	memset(gLowestReachable, 0, sizeof(gLowestReachable[0]) * gNodes);
	memset(gArcUsed, 0, sizeof(gArcUsed));
	
	for (i = 0; i < nEdges; i++) {
		scanf("%d %d\n", &from, &to);
		from--; to--;
		gAdjList[from][gAdjListCnt[from]++] = to;
	}
	
	result = solution2();
	
	if (result) {
		printf("%d\n", result % 10000);
	} else {
		printf("NIE\n");
	}
	
	return 0;
}
