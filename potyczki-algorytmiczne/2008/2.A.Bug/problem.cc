#include <iostream>
#include <list>
#include <map>
#include <set>
using namespace std;

static const int MAX_N = 200000;
static const int MAX_M = 500000;
static const int MAX_C = 1000;

bool visitedOdd[MAX_N];
bool visitedEven[MAX_N];

int shortestOdd[MAX_N];
int shortestEven[MAX_N];

struct roads_t {
	int a;
	int b;
	int c;
} roads[MAX_M];

list<roads_t*> roadsFrom[MAX_N];

set<int> queue;

int main()
{
	int n, m;
	int a, b, c;

	cin >> n >> m;

	// initialization
	for (int i = 0; i < n; i++) {
		visitedOdd[i] = visitedEven[i] = false;
		shortestOdd[i] = shortestEven[i] = MAX_N * MAX_C;
	}
	visitedEven[0] = true;
	shortestEven[0] = 0;

	for (int i = 0; i < m; i++) {
		cin >> roads[i].a >> roads[i].b >> roads[i].c;
		roads[i].a--;
		roads[i].b--;

		roadsFrom[roads[i].a].push_back(&roads[i]);
		roadsFrom[roads[i].b].push_back(&roads[i]);
	}

	queue.insert(0);

	while (!queue.empty()) {
		int node = *(queue.begin());
		queue.erase(node);

		list<roads_t*>::const_iterator i = roadsFrom[node].begin();
		list<roads_t*>::const_iterator e = roadsFrom[node].end();

		for (; i != e; i++) {
			int nodeDst  = (*i)->a == node ? (*i)->b : (*i)->a;
			int distance = (*i)->c;

//			cout << "Checking road from [" << node << "] to [" << nodeDst << "]" << endl;

			if (visitedEven[node]) {
				int routeLength = shortestEven[node] + distance;
				if (routeLength % 2) {
					if (!visitedOdd[nodeDst] || routeLength < shortestOdd[nodeDst]) {
						visitedOdd[nodeDst] = true;
						shortestOdd[nodeDst] = routeLength;
						queue.insert(nodeDst);

//						cout << "Visiting [" << nodeDst << "] as ODD, shortest [" << routeLength << "]" << endl;
					}
				} else {
					if (!visitedEven[nodeDst] || routeLength < shortestEven[nodeDst]) {
						visitedEven[nodeDst] = true;
						shortestEven[nodeDst] = routeLength;
						queue.insert(nodeDst);

//						cout << "Visiting [" << nodeDst << "] as EVEN, shortest [" << routeLength << "]" << endl;
					}
				}
			}
			if (visitedOdd[node]) {
				int routeLength = shortestOdd[node] + distance;
				if (routeLength % 2) {
					if (!visitedOdd[nodeDst] || routeLength < shortestOdd[nodeDst]) {
						visitedOdd[nodeDst] = true;
						shortestOdd[nodeDst] = routeLength;
						queue.insert(nodeDst);
//						cout << "Visiting [" << nodeDst << "] as ODD, shortest [" << routeLength << "]" << endl;
					}
				} else {
					if (!visitedEven[nodeDst] || routeLength < shortestEven[nodeDst]) {
						visitedEven[nodeDst] = true;
						shortestEven[nodeDst] = routeLength;
						queue.insert(nodeDst);
//						cout << "Visiting [" << nodeDst << "] as EVEN, shortest [" << routeLength << "]" << endl;
					}
				}
			}
		}
	}

	cout << (visitedOdd[n - 1] ? shortestOdd[n - 1] : 0) << endl;

	return 0;
}
