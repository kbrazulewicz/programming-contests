#include <iostream>
#include <list>
#include <set>
using namespace std;

const int MAX_M = 50000;
const int MAX_N = 50000;

struct {
	bool beetle;
	set<int> neighbours;
} gNodes[MAX_N + 1];

int gDistance[MAX_N + 1];

set<int> gNodesLeft;


// eliminate outbound empty nodes
void simplifyGraph(int n)
{
	list<int> outboundVertexes;

	for (int i = 1; i <= n; i++) {
		if (!gNodes[i].beetle && gNodes[i].neighbours.size() == 1) {
			outboundVertexes.push_back(i);
		}
	}

	while (! outboundVertexes.empty()) {
		int x = outboundVertexes.front();
		int y = *(gNodes[x].neighbours.begin());

		gNodes[x].neighbours.clear();
		gNodes[y].neighbours.erase(x);
		if (!gNodes[y].beetle && gNodes[y].neighbours.size() == 1) {
			outboundVertexes.push_back(y);
		}

		// printf("remove [%d], left [%d]\n", x, gNodesLeft.size());
		gNodesLeft.erase(x);
		outboundVertexes.pop_front();
	}
}


int calculate(int n)
{
	int maxPath = 0;

	// eliminate outbound empty nodes
	simplifyGraph(n);

	list<int> outboundVertexes;

	for (set<int>::const_iterator i = gNodesLeft.begin(); i != gNodesLeft.end(); i++) {
		// printf("checking [%d] [%d] vertices\n", *i, gNodes[*i].neighbours.size());
		if (gNodes[*i].neighbours.size() == 1) {
			outboundVertexes.push_back(*i);
		}
	}
	
	while (! outboundVertexes.empty()) {
		int x = outboundVertexes.front();
		int y = *(gNodes[x].neighbours.begin());
		int dx = gDistance[x] + 1;
		int dy = gDistance[y];


		if (gNodes[y].beetle && (dx % 2 == 1)) return -1;
		if (dy != 0 && (dx + dy) % 2 == 1) return -1;

		gDistance[y] = max(dx, dy);
		maxPath = max(maxPath, dx + dy);
		//printf("analyze [%d -> %d] [%d]\n", x, y, distance);

		gNodes[x].neighbours.clear();
		gNodes[y].neighbours.erase(x);
		if (gNodes[y].neighbours.size() == 1) {
			outboundVertexes.push_back(y);
		}

		outboundVertexes.pop_front();
	}

	return maxPath / 2;
}


int main()
{
	int n, m, k;
	int a, b, d;

	memset(gDistance, 0, sizeof(gDistance));
	
	// input
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; gNodesLeft.insert(gNodesLeft.end(), i++));
	for (int i = 1; i <= m; i++) {
		scanf("%d %d", &a, &b);
		gNodes[a].neighbours.insert(b);
		gNodes[b].neighbours.insert(a);
	}

	scanf("%d", &k);
	for (int i = 1; i <= k; i++) {
		scanf("%d", &d);
		gNodes[d].beetle = true;
	}

	// calculate
	int result = calculate(n);

	// output
	if (result < 0) {
		printf("NIE\n");
	} else {
		printf("%d\n", result);
	}
	
	return 0;
}
