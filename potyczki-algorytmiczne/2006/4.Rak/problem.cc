#include <iostream>
#include <list>
using namespace std;

#undef PA_DEBUG

static const int MAX_N = 10000;
static const int MAX_M = 100000;

struct {
	list<int> inbound;
	list<int> outbound;
	list<int> revInbound;
	list<int> revOutbound;
} gHome[MAX_N + 1];

char canGetHereForward[MAX_N + 1];
char canGetHereBackward[MAX_N + 1];
char canGetFromHereForward[MAX_N + 1];
char canGetFromHereBackward[MAX_N + 1];

int calculate(int n, int start)
{
	memset(canGetHereForward, 0, sizeof(canGetHereForward));
	memset(canGetHereBackward, 0, sizeof(canGetHereBackward));
	memset(canGetFromHereForward, 0, sizeof(canGetFromHereForward));
	memset(canGetFromHereBackward, 0, sizeof(canGetFromHereBackward));

	list<int> dfsQueueForward, dfsQueueBackward;
	list<int>::const_iterator iC, iE;

	// can get here DFS
	dfsQueueBackward.push_back(start);
	while (!(dfsQueueBackward.empty() && dfsQueueForward.empty())) {
		if (!dfsQueueBackward.empty()) {
			int x = dfsQueueBackward.front();
#ifdef PA_DEBUG
			printf("%d: jestem w [%d] tylem\n", start, x);
#endif
			iC = gHome[x].inbound.begin(); iE = gHome[x].inbound.end();
			while (iC != iE) {
				if (!canGetHereBackward[*iC]) {
					canGetHereBackward[*iC] = 1;
					dfsQueueBackward.push_back(*iC);
#ifdef PA_DEBUG
					printf("%d: dojde do [%d] tylem\n", start, *iC);
#endif
				}
				iC++;
			}
			iC = gHome[x].revInbound.begin(); iE = gHome[x].revInbound.end();
			while (iC != iE) {
				if (!canGetHereForward[*iC]) {
					canGetHereForward[*iC] = 1;
					dfsQueueForward.push_back(*iC);
#ifdef PA_DEBUG
					printf("%d: dojde do [%d] przodem\n", start, *iC);
#endif
				}
				iC++;
			}
			dfsQueueBackward.pop_front();
		}

		if (!dfsQueueForward.empty()) {
			int x = dfsQueueForward.front();
#ifdef PA_DEBUG
			printf("%d: jestem w [%d] przodem\n", start, x);
#endif
			iC = gHome[x].outbound.begin(); iE = gHome[x].outbound.end();
			while (iC != iE) {
				if (!canGetHereForward[*iC]) {
					canGetHereForward[*iC] = 1;
					dfsQueueForward.push_back(*iC);
#ifdef PA_DEBUG
					printf("%d: dojde do [%d] przodem\n", start, *iC);
#endif
				}
				iC++;
			}
			iC = gHome[x].revOutbound.begin(); iE = gHome[x].revOutbound.end();
			while (iC != iE) {
				if (!canGetHereBackward[*iC]) {
					canGetHereBackward[*iC] = 1;
					dfsQueueBackward.push_back(*iC);
#ifdef PA_DEBUG
					printf("%d: dojde do [%d] tylem\n", start, *iC);
#endif
				}
				iC++;
			}
			dfsQueueForward.pop_front();
		}
	}

	// can get from here DFS
	dfsQueueBackward.push_back(start);
	while (!(dfsQueueBackward.empty() && dfsQueueForward.empty())) {
		if (!dfsQueueBackward.empty()) {
			int x = dfsQueueBackward.front();
#ifdef PA_DEBUG
			printf("%d: jestem w [%d] tylem\n", start, x);
#endif
			iC = gHome[x].outbound.begin(); iE = gHome[x].outbound.end();
			while (iC != iE) {
				if (!canGetFromHereBackward[*iC]) {
					canGetFromHereBackward[*iC] = 1;
					dfsQueueBackward.push_back(*iC);
#ifdef PA_DEBUG
					printf("%d: wroce z [%d] tylem\n", start, *iC);
#endif
				}
				iC++;
			}
			iC = gHome[x].revInbound.begin(); iE = gHome[x].revInbound.end();
			while (iC != iE) {
				if (!canGetFromHereForward[*iC]) {
					canGetFromHereForward[*iC] = 1;
					dfsQueueForward.push_back(*iC);
#ifdef PA_DEBUG
					printf("%d: wroce z [%d] przodem\n", start, *iC);
#endif
				}
				iC++;
			}
			dfsQueueBackward.pop_front();
		}

		if (!dfsQueueForward.empty()) {
			int x = dfsQueueForward.front();
#ifdef PA_DEBUG
			printf("%d: jestem w [%d] przodem\n", start, x);
#endif
			iC = gHome[x].inbound.begin(); iE = gHome[x].inbound.end();
			while (iC != iE) {
				if (!canGetFromHereForward[*iC]) {
					canGetFromHereForward[*iC] = 1;
					dfsQueueForward.push_back(*iC);
#ifdef PA_DEBUG
					printf("%d: wroce z [%d] przodem\n", start, *iC);
#endif
				}
				iC++;
			}
			iC = gHome[x].revOutbound.begin(); iE = gHome[x].revOutbound.end();
			while (iC != iE) {
				if (!canGetFromHereBackward[*iC]) {
					canGetFromHereBackward[*iC] = 1;
					dfsQueueBackward.push_back(*iC);
#ifdef PA_DEBUG
					printf("%d: wroce z [%d] tylem\n", start, *iC);
#endif
				}
				iC++;
			}
			dfsQueueForward.pop_front();
		}
	}
	
	int visited = 0;
	for (int i = 1; i <= n; i++) {
		if (i == start) continue;
		if (
				(canGetHereForward[i] && canGetFromHereForward[i]) 
				||
				(canGetHereBackward[i] && canGetFromHereBackward[i]) 
		   ) 
		{
			visited++;
#ifdef PA_DEBUG
			printf("%d: odwiedzony [%d] \n", start, i);
#endif
		}
	}

	return visited;
}

int main()
{
	int n, m, a, b, s;

	scanf("%d %d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d %d %d", &a, &b, &s);
		if (s) {
			gHome[a].revOutbound.push_back(b);
			gHome[b].revInbound.push_back(a);
		} else {
			gHome[a].outbound.push_back(b);
			gHome[b].inbound.push_back(a);
		}
	}

	for (int i = 1; i <= n; i++) {
		printf("%d\n", calculate(n, i));
	}
	
	return 0;
}
