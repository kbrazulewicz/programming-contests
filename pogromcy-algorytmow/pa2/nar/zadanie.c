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

#define MAX_NODES 5000
#define MAX_EDGES (3 * MAX_NODES - 6)

int gNodeLevel[MAX_NODES];

int gChildrenNumber[MAX_NODES];
int gChildrenOffset[MAX_NODES];
int gChildren[MAX_EDGES];

void bfs()
{
	static int stack[MAX_NODES];
	static int state[MAX_NODES];
	int *head = stack, *tail = stack;
	
	memset(state, 0, sizeof(state));
	*(tail++) = 0;
}


void dfs()
{
	static int stack[MAX_NODES];
	static int lastVisited[MAX_NODES]; /* index of last visited child */
	int *stackPtr = stack;
	int v;

	memset(lastVisited, 0, sizeof(lastVisited));
	
	*stackPtr = 0;

	while (stackPtr >= stack) {
		v = *stackPtr;
		if (lastVisited[v] < gChildrenNumber[v]) {
			*(++stackPtr) = gChildren[gChildrenOffset[v] + lastVisited[v]];
			PRINTF(("%d -> %d\n", v + 1, (*stackPtr) + 1));
			lastVisited[v]++;
		}
		else {
			stackPtr--;
		}
	}
}



int main()
{
	int nNodes, nChildren, node;
	int *childPtr;
	int i;

	scanf("%d\n", &nNodes);
	memset(gNodeLevel, 0, sizeof(gNodeLevel[0]) * nNodes);
	childPtr = gChildren;

	for (i = 0; i < nNodes - 1; i++) {
		scanf("%d", &nChildren);
		gChildrenNumber[i] = nChildren;
		gChildrenOffset[i] = childPtr - gChildren;
		while (nChildren--) {
			scanf("%d", &node);
			node--;
			*(childPtr++) = node;
			gNodeLevel[node] = MAX(gNodeLevel[node], gNodeLevel[i] + 1);
		}
	}
/*	
	for (i = 0; i < nNodes; i++) {
		PRINTF(("%d: %d\n", i + 1, gNodeLevel[i]));
		for (j = 0; j < gChildrenNumber[i]; j++) {
			PRINTF(("%d ", gChildren[gChildrenOffset[i] + j] + 1));
		}
		PRINTF(("\n"));
	}
*/	
	dfs();
	
	return 0;
}
