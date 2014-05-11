//
// Krystian Brazulewicz
// krystian.brazulewicz@iq.pl
//
// Note:
// Usage of unsigned short type is connected with MAX_NODES value. 
// If it exceedes unsigned short range - unsigned short type has to be changed to unsigned int.
//
#include <iostream>
using namespace std;

//#define __DEBUG

const static unsigned int MAX_NODES = 1000;


struct edge_t 
{
	unsigned short a;
	unsigned short b;
	int load;
};

struct edgeLink_t
{
	edge_t*		edge;
	edgeLink_t*	link;
};

 
edge_t edge[MAX_NODES];
edge_t *edgeQueue[MAX_NODES];
edge_t **edgeQueuePtr = edgeQueue;

// indexed by vertex index (which starts from 1)
edgeLink_t edgeLink[MAX_NODES * 2 + 1];
unsigned int edgeIndex = MAX_NODES + 1;


int main()
{
	unsigned int numberOfNodes, i;

	// initialization
	for (i = 0; i < MAX_NODES; i++) {
		edgeLink[i].edge = NULL;
		edgeLink[i].link = NULL;
	}

	cin >> numberOfNodes;

	
	for (i = 0; i < (numberOfNodes - 1); i++) {
		cin >> edge[i].a >> edge[i].b;
		edge[i].load = 0;

		// list of edges adjacent to vertex a
		if (!edgeLink[edge[i].a].edge) {
			edgeLink[edge[i].a].edge = &edge[i];
		}
		else {
			edgeLink[edgeIndex].edge = &edge[i];
			edgeLink[edgeIndex].link = edgeLink[edge[i].a].link;
			edgeLink[edge[i].a].link = &edgeLink[edgeIndex];
			edgeIndex++;
		}

		// list of edges adjacent to vertex b
		if (!edgeLink[edge[i].b].edge) {
			edgeLink[edge[i].b].edge = &edge[i];
		}
		else {
			edgeLink[edgeIndex].edge = &edge[i];
			edgeLink[edgeIndex].link = edgeLink[edge[i].b].link;
			edgeLink[edge[i].a].link = &edgeLink[edgeIndex];
			edgeIndex++;
		}
	}

	// now we can traverse graph

	// get vertex
	// find all edges adjacent to that vertex 

	unsigned short currentVertex = edge[0].a;
	unsigned short edgesAdded;
	unsigned int currentLoad;
	edge_t *currentEdge = NULL;
	edgeLink_t *currentEdgeLink = NULL;
	
	edge[0].load = -1;
	*edgeQueuePtr = &edge[0];
	edgeQueuePtr++;
	
	
	while (edgeQueuePtr != edgeQueue) {
		currentVertex = (*(edgeQueuePtr - 1))->b;
		currentEdgeLink = &edgeLink[currentVertex];
		edgesAdded = 0;

#ifdef __DEBUG
		cout << "Current vertex: [" << currentVertex << "]" << endl;
#endif

		while (currentEdgeLink && currentEdgeLink->edge) {
			currentEdge = currentEdgeLink->edge;

#ifdef __DEBUG
		cout << "Current edge: [" << currentEdge->a << ":" << currentEdge->b << ":" << currentEdge->load << "]" << endl;
#endif

			if (!currentEdge->load) {
				// so currentEdge->b == currentVertex
				if (currentEdge->a != currentVertex) {
					currentEdge->b = currentEdge->a;
					currentEdge->a = currentVertex;
				}
				currentEdge->load = -1;

				// add to queue
				*edgeQueuePtr = currentEdge;
				edgeQueuePtr++;
				edgesAdded++;
			}

			currentEdgeLink = currentEdgeLink->link;
		}

		// no new edges
		if (!edgesAdded) {
			edgeQueuePtr--;
			currentLoad = 1;
			currentEdgeLink = &edgeLink[currentVertex];

			// traverse again - calculate load
			while (currentEdgeLink && currentEdgeLink->edge) {
				currentEdge = currentEdgeLink->edge;

				if (currentEdge->load > 0) {
					currentLoad += currentEdge->load;
				}

				currentEdgeLink = currentEdgeLink->link;
			}
			(*edgeQueuePtr)->load = currentLoad;
#ifdef __DEBUG
			cout << "Final load: [" << (*edgeQueuePtr)->a << ":" << (*edgeQueuePtr)->b << ":" << (*edgeQueuePtr)->load << "]" << endl;
#endif
		}
	}


	// finally calcucate load
	int maxLoad = 0;
	for (i = 0; i < (numberOfNodes - 1); i++) {
		edge[i].load *= (numberOfNodes - edge[i].load);

		if (edge[i].load > maxLoad) maxLoad = edge[i].load;

#ifdef __DEBUG
		cout << edge[i].a << ":" << edge[i].b << ":" << edge[i].load << endl;
#endif

	}

	cout << maxLoad << endl;

	return 0;
}
