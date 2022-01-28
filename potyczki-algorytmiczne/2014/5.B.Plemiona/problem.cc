#include <cstdio>
#include <list>
using namespace std;

#define DEBUG

#define EVEN(X) (X % 2 == 0)
#define ODD(X) (X % 2 != 0)

#define FOR(E, I) for(auto E = I.begin(); E != I.end(); E++)

struct Area
{
	int x1, x2, y1, y2;

	bool intersects(const Area &other) const
	{
		return other.x1 <= x2 && other.x2 >= x1 && other.y1 <= y2 && other.y2 >= y1;
	}
};


struct Interval
{
	int x1, x2;

	static bool compareLeftmostFirst(const Interval* a, const Interval* b)
	{
		return a->x1 < b->x1;
	}

	static bool compareRightmostFirst(const Interval* a, const Interval* b)
	{
		return b->x2 < a->x2;
	}
};

class IntervalTree
{
private:
	struct Node
	{
		int x;

		// overlapping elements: leftmost sorted, rightmost sorted
		std::list<Interval*> oL, oR;

		// L/R subtree
		Node *l, *r;
		// number of elements in L/R subtree
		int lWeight, rWeight;
	};

	Node *nodes;
	Node *nodePtr;

	Node* newNode(Interval* interval)
	{
		Node* node = nodePtr++;
		node->x = interval->x1;
		node->oL.push_back(interval);
		node->oR.push_back(interval);
	}

	void addNodeL(Node* node, Interval* interval)
	{
		node->lWeight++;
		if (node->l == NULL)
		{
			node->l = newNode(interval);
		}
		else
		{
			addNode(node->l, interval);
		}
	}

	void addNodeR(Node* node, Interval* interval)
	{
		node->rWeight++;
		if (node->r == NULL)
		{
			node->r = newNode(interval);
		}
		else
		{
			addNode(node->r, interval);
		}
	}

	void addNodeO(Node* node, Interval* interval)
	{
		node->oL.push_back(interval);
		node->oL.sort(Interval::compareLeftmostFirst);
		node->oR.push_back(interval);
		node->oR.sort(Interval::compareRightmostFirst);
	}

	void addNode(Node* node, Interval* interval)
	{
		if (interval->x2 < node->x) // left subtree
		{
			addNodeL(node, interval);
		}
		else if (interval->x1 > node->x) // right subtree
		{
			addNodeR(node, interval);
		}
		else // overlapping
		{
			addNodeO(node, interval);
		}
	}

public: 
	IntervalTree(int maxNodes)
	{
		nodes = new Node[maxNodes];
		nodePtr = nodes;
	}

	~IntervalTree()
	{
		delete [] nodes;
	}


	void addInterval(Interval* interval)
	{
		if (nodes == nodePtr)
		{
			newNode(interval);
		}
		else
		{
			addNode(nodes, interval);
		}
	}

	list<Interval*> checkOverlap(const Interval* interval)
	{
	}
};


int main()
{
	int n;
	scanf("%d", &n);

	IntervalTree tree(n);

	while(n--)
	{
		int x1, x2, y1, y2;
		scanf("%d%d%d%d", &x1, &x2, &y1, &y2);
	}

	Area a;
	a.x1 = 0;

	return 0;
}
