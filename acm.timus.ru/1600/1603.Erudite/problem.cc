/* @JUDGE_ID: 16232QS 1603 C++ */

#include <cstdio>
using namespace std;

static const int MAX_X   = 4;


struct node_t {
	char value;
	bool visited;

	int neighbourCount;
	node_t *neighbours[4];
} nodes[MAX_X * MAX_X];

char search[MAX_X * MAX_X + 1];


bool testForString(node_t* node, const char* search)
{
	bool found = false;

	if (node->value == *search) {
		++search;
		if (*search == '\0') {
			found = true;
		} else {
			node->visited = true;
			for (int i = 0; i < node->neighbourCount && !found; ++i) {
				found = !node->neighbours[i]->visited && testForString(node->neighbours[i], search);
			}
			node->visited = false;
		}
	}

	return found;
}


int main()
{
	int n;

	for (int i = 0; i < MAX_X; ++i) {
		scanf("%c%c%c%c\n", &nodes[i * MAX_X + 0], &nodes[i * MAX_X + 1], &nodes[i * MAX_X + 2], &nodes[i * MAX_X + 3]);
		for (int j = 0; j < MAX_X; ++j) {
			int k = i * MAX_X + j;
			if (j > 0) {
				nodes[k].neighbours[nodes[k].neighbourCount++] = nodes + k - 1;
			}
			if (j < MAX_X - 1) {
				nodes[k].neighbours[nodes[k].neighbourCount++] = nodes + k + 1;
			}
			if (i > 0) {
				nodes[k].neighbours[nodes[k].neighbourCount++] = nodes + k - MAX_X;
			}
			if (i < MAX_X - 1) {
				nodes[k].neighbours[nodes[k].neighbourCount++] = nodes + k + MAX_X;
			}
		}
	}

	scanf("%d\n", &n);
	while (n--) {
		scanf("%s\n", &search);
		bool found = false;

		for (int i = 0; i < MAX_X * MAX_X && !found; ++i) {
			found = testForString(nodes + i, search);
		}

		printf("%s: %s\n", search, found ? "YES" : "NO");
	}

	return 0;
}
