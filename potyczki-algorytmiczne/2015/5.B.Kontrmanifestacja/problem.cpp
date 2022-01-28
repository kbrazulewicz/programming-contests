#include <cstdio>
#include <deque>
#include <list>
#include <stack>
using namespace std;

#undef DEBUG

#define EVEN(X) (X % 2 == 0)
#define ODD(X) (X % 2 != 0)

#define FOR(E, I) for(auto E = I.begin(); E != I.end(); E++)

const int MAX_N = 500000;
const int MAX_M = 1000000;

typedef struct Node
{
#ifdef DEBUG
	int indexForDisplay;
#endif
	bool visited;
	bool visitedInCurrentPath;
	int cycleCount;
	int cycleStart, cycleEnd;
	list<Node*> connections;
} Node;

Node nodes[MAX_N];


int dfsAndMarkCycles(Node* startingNode)
{
	int totalCycleCount = 0, currentCycleCount = 0;
	stack<Node*> q;
	deque<Node*> backtrack;

	q.push(startingNode);

#ifdef DEBUG
	printf("DFS starts from node %d\n", startingNode->indexForDisplay);
#endif

	while (!q.empty())
	{
		Node *n = q.top();
#ifdef DEBUG_DEBUG
		printf("Node %d, backtrack ", n->indexForDisplay);
		for (auto bIter = backtrack.rbegin(); bIter != backtrack.rend(); bIter++)
		{
			printf("%d ", (*bIter)->indexForDisplay);
		}
		printf("\n");
#endif

		if (n->visitedInCurrentPath)
		{
			n->visitedInCurrentPath = false;

			currentCycleCount += n->cycleStart;
			n->cycleCount = currentCycleCount;
			currentCycleCount -= n->cycleEnd;

			backtrack.pop_back();
			q.pop();
		}
		else
		{
			n->visited = true;
			n->visitedInCurrentPath = true;
			backtrack.push_back(n);

			FOR(cIter, n->connections)
			{
				if ((*cIter)->visitedInCurrentPath) 
				{
					n->cycleStart++;
					(*cIter)->cycleEnd++;
					totalCycleCount++;

#ifdef DEBUG
					printf("cycle detected at node %d, previous node %d, cycle count %d\n", 
							(*cIter)->indexForDisplay, backtrack.back()->indexForDisplay, totalCycleCount);
#endif
				}
				else
				{
					q.push(*cIter);
#ifdef DEBUG_DEBUG
					printf("queued %d -> %d\n", n->indexForDisplay, (*cIter)->indexForDisplay);
#endif
				}
			}
		}
	}

#ifdef DEBUG
	printf("cycle count for subgraph starting from node %d is %d\n", startingNode->indexForDisplay, totalCycleCount);
#endif

	return totalCycleCount;
}


list<int> solution(int n)
{
	int cycleCount = 0;

	for (int i = 0; i < n; i++)
	{
		if (!nodes[i].visited)
		{
			cycleCount += dfsAndMarkCycles(&nodes[i]);
		}
	}

#ifdef DEBUG
	printf("total cycle count %d\n", cycleCount);
#endif

	list<int> result;
	if (cycleCount > 0)
	{
		for (int i = 0; i < n; i++)
		{
			if (nodes[i].cycleCount == cycleCount)
			{
				result.push_back(i + 1);
			}
		}
	}

#ifdef DEBUG
	printf("critical intersections %d\n", result.size());
#endif

	return result;
}


int main()
{
	int n, m;
	scanf("%d%d", &n, &m);

#ifdef DEBUG
	for (int i = 0; i < n; i++) nodes[i].indexForDisplay = i + 1;
#endif
	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);

		nodes[a - 1].connections.push_back(nodes + b - 1);
	}

	list<int> result = solution(n);
	result.sort();

	if (!result.empty())
	{
		printf("%d\n", result.size());
		FOR(rIter, result) printf("%d ", *rIter);
		printf("\n");
	}
	else
	{
		puts("NIE");
	}

	return 0;
}
