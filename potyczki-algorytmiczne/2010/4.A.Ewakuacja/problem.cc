#include <algorithm>
#include <cstdio>
#include <deque>
#include <functional>
#include <list>
#include <set>
using namespace std;

#undef DEBUG

static const int MAX_N = 1000;
static const int MAX_M = MAX_N * (MAX_N - 1);

typedef struct {
	bool exists;
	int  a;
	int  b;
	int  score;
} edge_t;

struct sort_edge_ptr_by_score : public binary_function<edge_t*, edge_t*, bool> {
	bool operator()(edge_t* const& a, edge_t* const& b) { return (a->score > b->score) || (a->score == b->score && a->b > b->b); }
};


typedef struct {
	edge_t* a;
	edge_t* b;
} route2_t;

typedef struct {
	edge_t* a;
	edge_t* b;
	edge_t* c;
} route3_t;


edge_t edge[MAX_N + 1][MAX_N + 1];


void edgeIncreaseScore(edge_t* e, deque<edge_t*>& collection)
{
	if (e->score == 0) collection.push_back(e);
	e->score++;
}

void edgeDecreaseScore(int a, int b, deque<edge_t*>& collection)
{
	edge_t* e = &edge[a][b];

	if (e->score > 0) {
		e->score--;
	}
}



int main()
{
	int n, m;
	int edgesToRemove = 0, palaceOutboud = 0, shelterInbound = 0;

	scanf("%d%d", &n, &m);

	for (int i = 0; i < m; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);

		edge_t& e = edge[a][b];

		e.exists = true;
		e.a = a;
		e.b = b;
	}

	// distance: 1
	if (edge[1][n].exists) {
		edgesToRemove++;
		edge[1][n].score = 1;
#ifdef DEBUG		
		printf("EDGE [%d:%d]\n", 1, n);
#endif		
	}

	deque<edge_t*> potentialTarget;

	list<route2_t> route2;
	list<route3_t> route3;

	// distance: 2
	for (int i = 2; i < n; i++) {
		route2_t route;
		route.a = &edge[1][i];
		route.b = &edge[i][n];

		if (route.a->exists && route.b->exists) {
			route.a->score++;
			route.b->score++;
			route2.push_back(route);

#ifdef DEBUG		
			printf("EDGE [%d:%d:%d]\n", 1, i, n);
#endif		
		}
	}

	// distance: 3
	for (int i = 2; i < n; i++) {
		for (int j = 2; j < n; j++) {
			route3_t route;
			route.a = &edge[1][i];
			route.b = &edge[i][j];
			route.c = &edge[j][n];
			if (route.a->exists && route.b->exists && route.c->exists) {
				route.a->score++;
				route.b->score++;
				route.c->score++;
				route3.push_back(route);
#ifdef DEBUG		
				printf("EDGE [%d:%d:%d:%d]\n", 1, i, j, n);
#endif				
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		if (edge[1][i].score > 0) palaceOutboud++;
		if (edge[i][n].score > 0) shelterInbound++;
	}

#ifdef DEBUG		
	printf("PALACE OUTBOUND [%d], SHELTER INBOUND [%d]\n", palaceOutboud, shelterInbound);
#endif				


	set<edge_t*> potentialTargetX;

	for (list<route2_t>::iterator i = route2.begin(); i != route2.end(); i++)
	{
		if (i->a->score == 1 && i->b->score == 1) {
			edgesToRemove++;
		} else {
			potentialTargetX.insert(i->a);
			potentialTargetX.insert(i->b);
		}
	}

	for (list<route3_t>::iterator i = route3.begin(); i != route3.end(); i++)
	{
		if (i->a->score == 1 && i->b->score == 1 && i->c->score == 1) {
			edgesToRemove++;
		} else {
			potentialTargetX.insert(i->a);
			potentialTargetX.insert(i->b);
			potentialTargetX.insert(i->c);
		}
	}

	copy(potentialTargetX.begin(), potentialTargetX.end(), inserter(potentialTarget, potentialTarget.begin()));

#ifdef DEBUG		
	printf("FOUND [%d]\n", potentialTarget.size());
#endif				
	sort(potentialTarget.begin(), potentialTarget.end(), sort_edge_ptr_by_score());

	while (!potentialTarget.empty() && potentialTarget.front()->score > 0) 
	{
		edge_t* e = potentialTarget.front();

#ifdef DEBUG		
		for (deque<edge_t*>::const_iterator i = potentialTarget.begin(); i != potentialTarget.end(); i++)
		{
			const edge_t* e = *i;
			if (e->score > 0) {
				printf("EDGE [%d:%d], SCORE [%d]\n", e->a, e->b, e->score);
			}	
		}
		printf("REMOVING [%d:%d], SCORE [%d]\n", e->a, e->b, e->score);
#endif				

		edgesToRemove++;

		if (e->a == 1) {
			if (edge[e->b][n].exists) {
				edgeDecreaseScore(e->b, n, potentialTarget);
			}
			for (int i = 2; i < n; i++) {
				if (edge[e->b][i].exists && edge[i][n].exists) {
					edgeDecreaseScore(e->b, i, potentialTarget);
					edgeDecreaseScore(i, n, potentialTarget);
				}
			}
		} else if (e->b == n) {
			if (edge[1][e->a].exists) {
				edgeDecreaseScore(1, e->a, potentialTarget);
			}
			for (int i = 2; i < n; i++) {
				if (edge[1][i].exists && edge[i][e->a].exists) {
					edgeDecreaseScore(1, i, potentialTarget);
					edgeDecreaseScore(i, e->a, potentialTarget);
				}
			}
		} else {
			edgeDecreaseScore(1, e->a, potentialTarget);
			edgeDecreaseScore(e->b, n, potentialTarget);
		}

		e->score = 0;
		e->exists = false;
		potentialTarget.pop_front();
		sort(potentialTarget.begin(), potentialTarget.end(), sort_edge_ptr_by_score());
	}

	printf("%d\n", min(edgesToRemove, min(palaceOutboud, shelterInbound)));

	return 0;
}
