#include <cstdio>
#include <cstring>

#include <set>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

#define MAX_N 10000
#define MAX_M 100000

unsigned short degree[MAX_N];
set<int> adjacency[MAX_N];
set<int> adjacencyDFS[MAX_N];
set<int> cycle[MAX_N];
bool visited[MAX_N];

void dfs(int aNumberOfVertices)
{
	int currVertex, nextVertex;
	vector<int> queue;

	queue.reserve(aNumberOfVertices);
	memset(visited, 0, sizeof(visited));

	for (int i = 0; i < aNumberOfVertices; i++) {
		adjacencyDFS[i] = adjacency[i];
	}

	currVertex = 0;
	queue.push_back(currVertex);

	do {
		set<int>::const_iterator i;
		int nextVertex = -1;

		currVertex = queue.back(); queue.pop_back();
		printf("dfs: %d\n", currVertex);
		visited[currVertex] = true;

		// search for next unvisited vertex
		i = adjacencyDFS[currVertex].begin();
		while (nextVertex < 0 && i != adjacencyDFS[currVertex].end()) {
			printf("dfs: checking %d\n", *i);
			if (visited[*i]) {
				// cycle ?
				if (!queue.empty() && currVertex != *i && queue.back() != *i) {
					int cycleBegin = *i, cycleEnd = currVertex;
					int a = cycleEnd;
					int b = cycleBegin;
					int l = b;
					printf("dfs: cycle at %d, detected from %d, queue back is %d\n", b, a, queue.back());
					vector<int>::const_iterator qbacktracer = queue.end();
					do {
						printf("dfs: backtrace %d - %d, limit %d\n", a, b, l);
						cycle[a].insert(b);
						cycle[b].insert(a);
						qbacktracer--;
						b = a;
						a = *qbacktracer;
					} while (b != l);
					adjacencyDFS[cycleBegin].erase(cycleEnd);
					adjacencyDFS[cycleEnd].erase(cycleBegin);
					i = adjacencyDFS[cycleEnd].lower_bound(cycleBegin);
				} else {
					i++;
				}
			} else {
				nextVertex = *i;
			}
		}

		if (nextVertex < 0) {
			if (!queue.empty()) {
				queue.pop_back();
			}
		} else {
			adjacencyDFS[currVertex].erase(nextVertex);
			adjacencyDFS[nextVertex].erase(currVertex);
			queue.push_back(currVertex);
			queue.push_back(nextVertex);
		}

	} while (!queue.empty());
}

int main()
{
	int n, m;
	int a, b;

	memset(degree, 0, sizeof(degree));
	
	scanf("%d %d", &n, &m);

	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		adjacency[a - 1].insert(b - 1);
		degree[a - 1]++;
		adjacency[b - 1].insert(a - 1);
		degree[b - 1]++;
	}

	dfs(n);

	int numberOfOddVertices = 0;
	int numberOfEulerPaths = 0;
	list<int> oddVertices;
	for (int i = 0; i < n; i++) {
		if (degree[i] % 2) {
			oddVertices.push_back(i);
		}
	}
	numberOfOddVertices = oddVertices.size();

	if (numberOfOddVertices) {
		numberOfEulerPaths = numberOfOddVertices / 2;
	} else {
		numberOfEulerPaths = 1;
		oddVertices.push_back(0);
	}

		
	printf("%d\n", numberOfEulerPaths);

	vector<int> eulerPath;
	eulerPath.reserve(m);
	

	while (numberOfEulerPaths--) {

		int currVertex = oddVertices.front();
		oddVertices.pop_front();

		eulerPath.push_back(currVertex);

		do {
			int nextVertex = -1;
			set<int>::const_iterator currVertexListEnd = adjacency[currVertex].end();
			set<int>::const_iterator nextVertexIt      = currVertexListEnd;
			set<int>::const_iterator i                 = currVertexListEnd;

			while (nextVertexIt == currVertexListEnd && !cycle[currVertex].empty()) {
				int cycleStart = *cycle[currVertex].begin();
				cycle[currVertex].erase(cycle[currVertex].begin());

				nextVertexIt = adjacency[currVertex].find(cycleStart);
			}

			// search for first even
			for (i = adjacency[currVertex].begin(); nextVertexIt == currVertexListEnd && i != currVertexListEnd; i++) {
				if (! degree[*i] % 2) {
					nextVertexIt = i;
				}
			}

			// search for odd > 1
			if (nextVertexIt == currVertexListEnd) {
				for (i = adjacency[currVertex].begin(); nextVertexIt == currVertexListEnd && i != currVertexListEnd; i++) {
					if (degree[*i] > 1) {
						nextVertexIt = i;
					}
				}
			}

			// take first one
			if (nextVertexIt == adjacency[currVertex].end()) {
				nextVertexIt = adjacency[currVertex].begin();
			}

			
			nextVertex = *nextVertexIt;
			adjacency[currVertex].erase(nextVertexIt);
			degree[currVertex]--;
			adjacency[nextVertex].erase(currVertex);
			degree[nextVertex]--;
			currVertex = nextVertex;

			if (!degree[currVertex]) {
				oddVertices.remove(currVertex);
			}
			eulerPath.push_back(currVertex);
		} while (degree[currVertex]);



		printf("%d", eulerPath.size());
		for (vector<int>::const_iterator i = eulerPath.begin(); i < eulerPath.end(); i++) {
			printf(" %d", *i + 1);
		}
		printf("\n");
		eulerPath.clear();
	}
	
	return 0;
}
