/* @JUDGE_ID: 16232QS 1106 C++ */

#include <iostream>
#include <queue>
#include <set>
using namespace std;

static const int MAX_N = 100;
enum Color { NONE = 0, RED = 1, BLACK = 2 };

set<int> graph[MAX_N + 1];
int color[MAX_N + 1];


void dfs(deque<int>& nodes, int nodeColor)
{
	int node = nodes.front(); 

	if (color[node] == NONE) {
		color[node] = nodeColor;
		for (set<int>::const_iterator i = graph[node].begin(); i != graph[node].end(); i++) {
			if (color[*i] == NONE) {
				nodes.push_front(*i);
				dfs(nodes, nodeColor == RED ? BLACK : RED);
			}
		}
	}
	nodes.pop_front();
}


int main()
{
	int n, k;

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) 
	{
		do {
			scanf("%d", &k);
			if (k != 0) {
				graph[i].insert(k);
			}
		} while (k != 0);
	}

	deque<int> nodeQueue;
	for (int i = 1; i <= n; nodeQueue.push_back(i++));

	while (!nodeQueue.empty()) {
		dfs(nodeQueue, RED);
	}

	set<int> red;
	for (int i = 1; i <= n; i++) {
		if (color[i] == RED) {
			red.insert(i);
		}
	}

	printf("%d\n", red.size());
	for (set<int>::const_iterator i = red.begin(); i != red.end(); i++) {
		printf("%s%d", i == red.begin() ? "" : " ", *i);
	}
	printf("\n");

	return 0;
}
