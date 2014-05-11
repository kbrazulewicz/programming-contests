#include <cstdio>
#include <list>
#include <map>
#include <queue>
using namespace std;

#define __DEBUG__

const int MAX_N = 100000;
const int MAX_P = 10;

typedef struct node_t
{
	int val;
	int len;
	node_t* next;
};

node_t a[MAX_N];

typedef map<unsigned long long, node_t*> dict_t;
dict_t dict;

int indexLength[MAX_P + 1][MAX_N + 1];





void calculateIndexLengths(int n, int p)
{
	for (int iP = 0; iP <= p; iP++) {
		indexLength[iP][iP] = 1;
	}
	for (int iN = 0; iN <= n; iN++) {
		indexLength[0][iN] = 1;
	}
	for (int iP = 1; iP <= p; iP++) {
#ifdef __DEBUG__
		printf("calculateIndexLengts: iP:[1 - %d]\n", p);
#endif
		for (int iN = iP + 1; iN <= n; iN++) {
			indexLength[iP][iN] = indexLength[iP - 1][iN - 1] + indexLength[iP][iN - 1];
#ifdef __DEBUG__
			printf("calculateIndexLengts: (%d, %d) -> (%d)\n", iP, iN, indexLength[iP][iN]);
#endif
		}
	}
}

void createLinks(int n)
{
	list<node_t*> queue;
	
	// create links
	for (int i = 0; i < n; i++) {
		list<node_t*>::iterator qI = queue.begin();
		while (qI != queue.end()) {
			if ((*qI)->val > a[i].val) {
#ifdef __DEBUG__
				printf("createLinks q:[%d], l:[%d]\n", (*qI)->val, a[i].val);
#endif
				(*qI)->next = &a[i];
				queue.erase(qI++);
			} else qI++;
		}
		queue.push_back(&a[i]);
	}
}

void calculateChains(int n)
{
	for (int i = 0; i < n; i++) {
		if (a[i].len == 0) {
			node_t *node = &a[i];
			queue<node_t*> queue;
			queue.push(node);
			while (node->next) {
				node = node->next;
				queue.push(node);
			}

			while (!queue.empty()) {
				queue.front()->len = queue.size();
				queue.pop();
			}
		}
	}
}

void calculateIndex(int n, int p)
{
	unsigned long long currentIndex = 1;
	for (int i = 0; i < n; i++) {
		if (a[i].len >= p) {
#ifdef __DEBUG__
			printf("calculateIndex: index [%llu] -> [%d]; indexLength (%d, %d) -> (%d)\n", 
					currentIndex, i,
					p, a[i].len, indexLength[p - 1][a[i].len - 1]);
#endif
			dict[currentIndex] = &a[i];
			currentIndex += indexLength[p - 1][a[i].len - 1];
		}
	}
	dict[currentIndex] = NULL;
#ifdef __DEBUG__
	printf("calculateIndex: index [%llu] -> END;\n", currentIndex);
#endif
}

void prepare(int n, int p)
{
#ifdef __DEBUG__
	printf("prepare: n [%d]; p [%d]\n", n, p);
#endif
	calculateIndexLengths(n, p);
	createLinks(n);
	calculateChains(n);
	calculateIndex(n, p);


#ifdef __DEBUG__
	for (int i = 0; i < n; i++) {
		printf("[%.3d] val [%d]; len [%d]\n", i, a[i].val, a[i].len);
	}
#endif
}

void query(int n, int p, int k)
{
	dict_t::iterator i = dict.upper_bound(k);
	if (i == dict.end()) {
		printf("%d\n", -1);
	} else {
		i--;
		node_t* node = i->second;
#ifdef __DEBUG__
		printf("query: k [%d]; node [%d]; relative k [%d]\n", k, node - a, k - i->first);
#endif
		printf(p > 1 ? "%d " : "%d", node - a + 1);
		k -= i->first;
		node = node->next;
		p--;
		while (p > 0) {
#ifdef __DEBUG__
			printf("comparing k [%d] with (%d, %d) -> (%d)\n", k, p - 1, node->len - 1, indexLength[p - 1][node->len - 1]);
#endif
			if (k < indexLength[p - 1][node->len - 1]) {
				printf(p > 1 ? "%d " : "%d", node - a + 1);
				p--;
			} else {
				k -= indexLength[p - 1][node->len - 1];
			}
			node = node->next;
		}
		printf("\n");
	}
}


int main()
{
	int n, p, q;

	scanf("%d %d %d", &n, &p, &q);
	for (int i = 0; i < n; scanf("%d", &(a[i++].val)));

#ifdef __DEBUG__
	printf("n [%d]; p [%d]; q [%d]\n", n, p, q);
#endif

	prepare(n, p);

	for (int i = 0; i < q; i++)
	{
		int k;
		scanf("%d", &k);

		query(n, p, k);
	}

	return 0;
}
