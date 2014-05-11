#include <iostream>
#include <iterator>
#include <list>
#include <set>
using namespace std;

#define DEBUG

static const int MAX_N =         300;
static const int MIN_C = -1000000000;
static const int MAX_C =  1000000000;

long long gain[MAX_N + 1][MAX_N + 1];
char road[MAX_N + 1][MAX_N + 1];

set<int> edgeI[MAX_N + 1];
set<int> edgeO[MAX_N + 1];

int dfsQueue[1 + MAX_N];
int dfsQueueNextEdge[1 + MAX_N];
int money[MAX_N + 1];

char dfsVisited[MAX_N + 1];

int main()
{
	int n, m;
	int a, b, c, g;

	int iterationCount = 0;
	set<int> result;
	set<int> activeNodeList;

	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			gain[i][j] = MIN_C - 1;
		}
		activeNodeList.insert(i);
	}

	for (int i = 1; i <= m; i++) {
		cin >> a >> b >> c;

		gain[a][b] = c;
		road[a][b] = 1;

		edgeI[b].insert(a);
		edgeO[a].insert(b);
	}

	printf("Number of all nodes [%d]\n", activeNodeList.size());

	// eliminate vertices not included in cycles
	set<int> eliminate;

	for (int i = 1; i <= n; i++) {
		if (edgeI[i].empty()) {
			eliminate.insert(i);
		}
	}

	while (!eliminate.empty()) {
		int node = *(eliminate.begin());
		eliminate.erase(eliminate.begin());

		set<int>::const_iterator e = edgeO[node].end();

		for (set<int>::const_iterator it = edgeO[node].begin(); it != e; it++) {
			edgeI[*it].erase(node);
			if (edgeI[*it].empty()) {
				eliminate.insert(*it);
			}
		}

		edgeO[node].clear();
		activeNodeList.erase(node);
	}

	for (int i = 1; i <= n; i++) {
		if (edgeO[i].empty()) {
			eliminate.insert(i);
		}
	}

	while (!eliminate.empty()) {
		int node = *(eliminate.begin());
		eliminate.erase(eliminate.begin());

		set<int>::const_iterator e = edgeI[node].end();

		for (set<int>::const_iterator it = edgeI[node].begin(); it != e; it++) {
			edgeO[*it].erase(node);
			if (edgeO[*it].empty()) {
				eliminate.insert(*it);
			}
		}
		edgeI[node].clear();
		activeNodeList.erase(node);
	}

	printf("Number of nodes in cycles [%d]\n", activeNodeList.size());

#if 0

	for (int i = 1; i <= n; i++) {

		if (result.find(i) != result.end()) {
			continue;
		}

		dfsQueue[0] = 0;

		memset(dfsVisited, 0, sizeof(dfsVisited));

		dfsQueue[++dfsQueue[0]] = i;
		dfsQueueNextEdge[dfsQueue[0]] = 1;
		dfsVisited[i] = 1;
		money[i] = 0;

		while (dfsQueue[0] > 0) {
			iterationCount++;

			int node = dfsQueue[dfsQueue[0]];
			int nodeNextEdge = dfsQueueNextEdge[dfsQueue[0]];
			if (nodeNextEdge > connF[node][0]) {
				// traceback
				dfsQueue[0]--;
				dfsVisited[node] = 0;
#ifdef DEBUG
				printf("[%d] - trackback\n", node);
#endif
			} else {
				// increase next edge index
				dfsQueueNextEdge[dfsQueue[0]]++;
				// go deeper - decision
				int nodeNext = connF[node][nodeNextEdge];
				road[i][nodeNext] = 1;
				if (dfsVisited[nodeNext] == 0) {
					dfsQueue[++dfsQueue[0]] = nodeNext;
					dfsQueueNextEdge[dfsQueue[0]] = 1;
					dfsVisited[nodeNext] = 1;

					money[nodeNext] = money[node] + gain[node][nodeNext];

#ifdef DEBUG
					printf("[%d -> %d], money [%d]\n", node, nodeNext, money[nodeNext]);
#endif
				} else {
					if (nodeNext == i) {
						if (money[nodeNext] < money[node] + gain[node][nodeNext]) {
							result.insert(&dfsQueue[1], &dfsQueue[dfsQueue[0] + 1]);
#ifdef DEBUG
							printf("[%d -> %d] looped to top with gain\n", node, nodeNext);
#endif
							break;
						} else {
#ifdef DEBUG
							printf("[%d -> %d] looped to top with no gain\n", node, nodeNext);
#endif
						}
					} else {
						if (money[nodeNext] < money[node] + gain[node][nodeNext]) {
							result.insert(nodeNext);
#ifdef DEBUG
							printf("[%d -> %d] looped with gain\n", node, nodeNext);
#endif
						} else {
#ifdef DEBUG
							printf("[%d -> %d] looped with no gain\n", node, nodeNext);
#endif
						}
					}
				}
			}
		}
	}
#endif
	cout << result.size() << endl;
	copy(result.begin(), result.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

#ifdef DEBUG
	cout << iterationCount << endl;
#endif

	return 0;
}
