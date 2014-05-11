#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

const int MAX_N = 50000;


struct DecisionNode {
	int position;
	int weight;
	unsigned long long work;

	friend ostream& operator << (ostream& os, const DecisionNode& node) {
		os << "position [" << node.position << "] "
           << "weight [" << node.weight << "] "
           << "work [" << node.work << "]";

		return os;
	}
};


DecisionNode nodes[MAX_N];

typedef multimap< int, DecisionNode*, greater<int> > decisionQueue_type;
decisionQueue_type decisionQueue;


unsigned long long process(int n, int p, int k) {
	decisionQueue_type qTowards;
	decisionQueue_type qAway;
	set<DecisionNode*> qAllNodes;
	set<DecisionNode*> qChangedNodes;

	int step = (k > p) ? -1 : 1;
	int weight = nodes[k].weight;

	qAllNodes.insert(&nodes[p]);

	// find towards nodes
	for (int i = k + step; i != p; i += step) {
		if (nodes[i].weight < weight) {
			qAllNodes.insert(&nodes[i]);
			qTowards.insert(make_pair(nodes[i].weight, &nodes[i]));
			weight = nodes[i].weight;
		}
	}

	// find away nodes
	weight = nodes[k].weight;
	for (int i = k - step; i >= 0 && i < n; i -= step) {
		if (nodes[i].weight < weight) {
			qAllNodes.insert(&nodes[i]);
			qAway.insert(make_pair(nodes[i].weight, &nodes[i]));
			weight = nodes[i].weight;
		}
	}


	int previousPosition = k;
	nodes[k].work = 0LL;
	for (decisionQueue_type::iterator i = qTowards.begin(); i != qTowards.end(); i++) {
		DecisionNode& node = *(i->second);
		node.work = nodes[previousPosition].work + nodes[previousPosition].weight * abs(previousPosition - node.position);
		previousPosition = node.position;
		qChangedNodes.insert(i->second);
	}

	nodes[p].work = nodes[previousPosition].work + nodes[previousPosition].weight * abs(previousPosition - p);

	for (decisionQueue_type::iterator i = qAway.begin(); i != qAway.end(); i++) {
		DecisionNode& node = *(i->second);
		node.work = nodes[k].weight * abs(node.position - k);
		qChangedNodes.insert(i->second);
	}

	while (!qChangedNodes.empty()) {
		set<DecisionNode*>::iterator changedNodeIterator = qChangedNodes.begin();
		const DecisionNode& changedNode = **changedNodeIterator;

		decisionQueue_type::iterator qti = qTowards.lower_bound(changedNode.weight - 1);
		if (qti != qTowards.end()) {
			DecisionNode& node = *(qti->second);
			unsigned long long projectedWork = changedNode.work + changedNode.weight * abs(changedNode.position - node.position);

			if (projectedWork < node.work) {
				qChangedNodes.insert(qti->second);
				node.work = projectedWork;
			}
		}
		decisionQueue_type::iterator qai = qAway.lower_bound(changedNode.weight - 1);
		if (qai != qAway.end()) {
			DecisionNode& node = *(qai->second);
			unsigned long long projectedWork = changedNode.work + changedNode.weight * abs(changedNode.position - node.position);

			if (projectedWork < node.work) {
				qChangedNodes.insert(qai->second);
				node.work = projectedWork;
			}
		}
		{
			DecisionNode& node = nodes[p];
			unsigned long long projectedWork = changedNode.work + changedNode.weight * abs(changedNode.position - node.position);

			if (projectedWork < node.work) {
				node.work = projectedWork;
			}
		}

		qChangedNodes.erase(changedNodeIterator);
	}
	

	return nodes[p].work;
}



int main()
{
	int d, n, p, k;

	scanf("%d", &d);
	for(int i = 0; i < d; i++) {
		scanf("%d %d %d", &n, &p, &k);
		p--; k--;

		for(int j = 0; j < n; j++) {
			scanf("%d", &nodes[j].weight);
			nodes[j].position = j;
		}

		cout << process(n, p, k) + nodes[p].weight * abs(k - p) << endl;
	}

	return 0;
}
