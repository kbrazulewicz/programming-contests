#include <cstdio>
using namespace std;

#undef DEBUG

static const int MAX_N = 100000;

typedef struct employee_t {
	int id;
	employee_t* parent;

	employee_t* lNeighbour;
	employee_t* rNeighbour;

	employee_t* fChild;
	employee_t* lChild;
};


int employeeIdGenerator = 1;
employee_t employees[MAX_N + 1];

void actionZ_2(int p, int s)
{
	employee_t* e = &employees[p];

	e->id = p;
	e->parent = &employees[s];

#ifdef DEBUG
	printf("P[%d] S[%d]\n", p, s);
#endif

	if (e->parent->fChild == NULL) {
#ifdef DEBUG
		printf("FIRST CHILD OF S[%d]\n", s);
#endif
		// first child
		e->parent->lChild = e->parent->fChild = e;

		employee_t* parentLNeighbour = e->parent->lNeighbour;
		while (parentLNeighbour != NULL) 
		{
#ifdef DEBUG
//			printf("PARENTLNEIGHBOUR CHECKING [%d]\n", parentLNeighbour->id);
#endif
			if (parentLNeighbour->lChild != NULL) 
			{
				// set left neighbour
				e->lNeighbour = parentLNeighbour->lChild;
				// set right neighbour for left neighbour
				e->lNeighbour->rNeighbour = e;
				break;
			} else parentLNeighbour = parentLNeighbour->lNeighbour;
		}

		employee_t* parentRNeighbour = e->parent->rNeighbour;
		while (parentRNeighbour != NULL) 
		{
#ifdef DEBUG
//			printf("PARENTRNEIGHBOUR CHECKING [%d]\n", parentRNeighbour->id);
#endif
			if (parentRNeighbour->lChild != NULL) 
			{
				// set right neighbour
				e->rNeighbour = parentRNeighbour->fChild;
				// set left neighbour for right neighbour
				e->rNeighbour->lNeighbour = e;
				break;
			} else parentRNeighbour = parentRNeighbour->rNeighbour;
		}
	} else {
		// not the first child
#ifdef DEBUG
		printf("NOT THE FIRST CHILD OF S[%d]\n", s);
#endif

		// set left neighbour
		e->lNeighbour = e->parent->lChild;
		// set right neighbour
		e->rNeighbour = e->parent->lChild->rNeighbour;

		// set right neighbour for left neighbour
		e->lNeighbour->rNeighbour = e;

		if (e->rNeighbour != NULL) {
			// set left neighbour for right neighbour
			e->rNeighbour->lNeighbour = e;
		}
		// set last child for parent
		e->parent->lChild = e;
	}

#ifdef DEBUG
	printf("L NEIGHBOUR [%d]\n", e->lNeighbour ? e->lNeighbour->id : 0);
	printf("R NEIGHBOUR [%d]\n", e->rNeighbour ? e->rNeighbour->id : 0);
#endif
}



employee_t* dfsQueue[MAX_N];
int dfsQueueIndex;


int actionP_2(int q, int k)
{
#ifdef DEBUG
	printf("SEARCH Q[%d] LEVEL K [%d]\n", q, k);
#endif

	if (employees[q].fChild != NULL) 
	{
		bool backtrack = false;
		dfsQueueIndex = 0;
		dfsQueue[dfsQueueIndex++] = employees[q].fChild;

		while (dfsQueueIndex > 0 && dfsQueueIndex <= k) 
		{
			employee_t* node = dfsQueue[dfsQueueIndex - 1];
#ifdef DEBUG
			printf("L DFS ID[%d]\n", node->id);
#endif
			if (!backtrack && node->fChild != NULL) {
				dfsQueue[dfsQueueIndex++] = node->fChild;
			} else if (node->rNeighbour != NULL && node->parent == node->rNeighbour->parent) {
				dfsQueue[dfsQueueIndex - 1] = node->rNeighbour;
				backtrack = false;
			} else {
				dfsQueueIndex--;
				backtrack = true;
			}
		}

		if (dfsQueueIndex > 0) 
		{
			employee_t* leftmostChild  = dfsQueue[dfsQueueIndex - 1];

			bool backtrack = false;
			dfsQueueIndex = 0;
			dfsQueue[dfsQueueIndex++] = employees[q].lChild;

			while (dfsQueueIndex > 0 && dfsQueueIndex <= k) 
			{
				employee_t* node = dfsQueue[dfsQueueIndex - 1];
#ifdef DEBUG
				printf("R DFS ID[%d] LN[%d]\n", node->id, node->lNeighbour != NULL ? node->lNeighbour->id : 0);
#endif
				if (!backtrack && node->lChild != NULL) {
					dfsQueue[dfsQueueIndex++] = node->lChild;
				} else if (node->lNeighbour != NULL && node->parent == node->lNeighbour->parent) {
					dfsQueue[dfsQueueIndex - 1] = node->lNeighbour;
					backtrack = false;
				} else {
					dfsQueueIndex--;
					backtrack = true;
				}
			}

			employee_t* rightmostChild = dfsQueue[dfsQueueIndex - 1];

#ifdef DEBUG
			printf("LM CHILD OF Q[%d] LEVEL K [%d] IS [%d]\n", q, k, leftmostChild->id);
			printf("RM CHILD OF Q[%d] LEVEL K [%d] IS [%d]\n", q, k, rightmostChild->id);
#endif

			int length = 1;

			while (leftmostChild != rightmostChild) {
				leftmostChild = leftmostChild->rNeighbour;
				length++;
			}

			return length;
		}
	}

	return 0;
}



int main()
{
	int n;
	char o;
	int p, s;

	employees[1].id = 1;
	employees[1].parent = NULL;

	scanf ("%d\n", &n);

	for(int i = 1; i <= n; i++)
	{
		scanf("%c %d %d\n", &o, &p, &s);

		if (o == 'Z') {
			actionZ_2(p, s);
		} else {
			printf("%d\n", actionP_2(p, s));
		}

	}

	return 0;
}
