#include <cstdio>
#include <queue>
#include <set>
#include <stack>
#include <vector>

#define NODES_MAX (5000 + 1)

//#define DEBUG

/**
 * keywords: articulation point, cut vertex, weakly connected digraph
 */
class Node
{
	public:
		Node()
		{
			clear();
			incoming.reserve(128);
			outgoing.reserve(128);
		};

		void clear() 
		{
			visitOrder = 0;
			depth = 0;
			lastVisitedOutgoing = 0;
		};

		// check only after all children were traversed by DFS
		int checkHighestAncestor(const Node aNodes[])
		{
			int highestAncestor = NODES_MAX;
			std::vector<int>::const_iterator it  = incoming.begin();
			std::vector<int>::const_iterator itE = incoming.end();
			for (; it != itE; it++) {
				highestAncestor = std::min(highestAncestor, aNodes[*it].visitOrder);
				if (!highestAncestor) break;
			}
			return highestAncestor;
		};
		
		enum VisitState {
			UNVISITED,
			VISITED,
			COMPLETED
		};

		int visitOrder;
		int depth;

		std::vector<int> incoming;
		std::vector<int> outgoing;
		int lastVisitedOutgoing;
};

Node gNodes[NODES_MAX];
std::set<int> gCriticalNodes;

using namespace std;

void bfs(int aStartingNodeId, Node aNodes[])
{
	static std::queue<int> queue;
	int visitOrder = 1;

	queue.push(aStartingNodeId);
	aNodes[aStartingNodeId].visitOrder = visitOrder++;
	aNodes[aStartingNodeId].depth = 1;

	do {
		Node& node = aNodes[queue.front()];
#ifdef DEBUG
		printf("BFS order [%d], depth [%d], vertex[%d]\n", node.visitOrder, node.depth, queue.front());
#endif
		queue.pop();

		int numChildren = node.outgoing.size();
		for (int i = 0; i < numChildren; i++) {
			int childId = node.outgoing[i];
			if (!aNodes[childId].visitOrder) {
				aNodes[childId].visitOrder = visitOrder++;
				aNodes[childId].depth = node.depth + 1;
				queue.push(childId);
			}
		}
	} while (!queue.empty());
}

void dfs(int aStartingNodeId, Node aNodes[])
{
	static std::stack<int> stack;
	int visitOrder = 1;
	int depth = 1;

	stack.push(aStartingNodeId);
	aNodes[aStartingNodeId].visitOrder = visitOrder++;
	aNodes[aStartingNodeId].depth = 1;

	do {
		Node& node = aNodes[stack.top()];
#ifdef DEBUG
		printf("DFS order [%d], depth [%d], vertex[%d]\n", node.visitOrder, node.depth, stack.top());
#endif

		int numChildren = node.outgoing.size();
		for (; node.lastVisitedOutgoing < numChildren; node.lastVisitedOutgoing++) {
			int childId = node.outgoing[node.lastVisitedOutgoing];
			if (!aNodes[childId].visitOrder) {
				aNodes[childId].visitOrder = visitOrder++;
				aNodes[childId].depth = node.depth + 1;
				stack.push(childId);
				break;
			}
		}

		// branch end reached - backtrace
		if (node.lastVisitedOutgoing == numChildren) {
			// naive single parent check
			if (node.incoming.size() == 1) {
				gCriticalNodes.insert(node.incoming.front());
			} else if (numChildren) {
				// not a leaf
				int minHighestAncestor = NODES_MAX;
				for (int i = 0; i < numChildren; i++) {
					int childId = node.outgoing[i];
					minHighestAncestor = min(minHighestAncestor, aNodes[childId].checkHighestAncestor(gNodes));
				}
				if (minHighestAncestor == node.visitOrder) {
					gCriticalNodes.insert(stack.top());
				}
			}
			stack.pop();
		}
	} while (!stack.empty());
}


void clear()
{
	for (int i = 0; i < NODES_MAX; gNodes[i++].clear());
}

char outputBuffer[NODES_MAX * 5];

int main()
{
	int numComputer, numConnection;
	char* buffer = outputBuffer;

	scanf("%d%d", &numComputer, &numConnection);

	int n = numConnection;
	while (n--) {
		int a, b;
		scanf("%d%d", &a, &b);
		gNodes[a].outgoing.push_back(b);
		gNodes[b].incoming.push_back(a);
	}

	dfs(1, gNodes);

	// server is always critical
	gCriticalNodes.insert(1);

	set<int>::const_iterator it  = gCriticalNodes.begin();
	set<int>::const_iterator itE = gCriticalNodes.end();

	buffer += sprintf(buffer, "%d\n", gCriticalNodes.size());
	for (; it != itE; it++) {
		buffer += sprintf(buffer, "%d ", *it);
	}
	*(--buffer) = 0;
	puts(outputBuffer);

	return 0;
}
