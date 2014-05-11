#include <stdio.h>

#include <set>
using namespace std;

set<int> adjMatrix[10000];
int backtrack[10000];
int nodeVisited[10000];


bool iterDFS(set<int> aAdjMatrix[],
		int aNodeVisited[],
		int aQueue[],
		int aNodeCount, 
		int aSource,
		int aDestination)
{
	int lNode = aSource;
	int lQueuePtr = 0;
	set<int>::iterator lIt;
	memset(aNodeVisited, 0, sizeof(aNodeVisited[0]) * aNodeCount);

	aNodeVisited[lNode] = true;
	aQueue[lQueuePtr++] = lNode;

	while (lNode != aDestination && lQueuePtr) {
		lIt = aAdjMatrix[lNode].begin();
		while (lIt != aAdjMatrix[lNode].end()) {
			if (!aNodeVisited[*lIt]) break;
			lIt++;
		}
		if (lIt != aAdjMatrix[lNode].end()) {
			lNode = *lIt;
			aNodeVisited[lNode] = 1;
			aQueue[lQueuePtr++] = lNode;
		} else {
			if (--lQueuePtr) {
				int tmpTo = lNode;
				lNode = aQueue[lQueuePtr - 1];
				aAdjMatrix[lNode].erase(tmpTo);
			}
		}
	}
	if (lNode == aDestination) {
		for (int i = 1; i < lQueuePtr; i++) {
			aAdjMatrix[aQueue[i - 1]].erase(aQueue[i]);
		}
		return true;
	}
	
	return false;
}


int main()
{
	int serverNumber, connectionNumber;
	int from, to;
	int trap = -1;

	scanf("%d %d", &serverNumber, &connectionNumber);

	for (int i = 0; i < connectionNumber; i++) {
		scanf("%d %d", &from, &to);
		adjMatrix[from - 1].insert(to - 1);
	}

	do {
		trap++;
	} while (iterDFS(adjMatrix, nodeVisited, backtrack, serverNumber, 0, serverNumber - 1));

	printf("%d\n", trap);

	return 0;
}
