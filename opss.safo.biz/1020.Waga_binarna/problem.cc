#include <cstdio>
#include <cstdlib>

using namespace std;

struct waga_t
{
	unsigned int l;
	unsigned int m;	
	unsigned int value;
};

static const int MAX_ELEMENTS 	= 20000;

waga_t waga[MAX_ELEMENTS];
waga_t *wagaPtr[MAX_ELEMENTS];


int waga_sort(const void* a, const void* b) 
{
	return (*((waga_t**)a))->value - (*((waga_t**)b))->value;
}

// one huge quick sort
void waga0(unsigned int n)
{
	for (unsigned int i = 0; i < n; i++) {
		scanf("%u%u", &(waga[i].l), &(waga[i].m));
		waga[i].value = (waga[i].l << (20 - waga[i].m)) + waga[i].l;
		wagaPtr[i] = waga + i;
	}
	qsort(&wagaPtr, n, sizeof(wagaPtr[0]), waga_sort);

	for (unsigned int j = 0; j < n; j++) {
		printf("%d %d\n", wagaPtr[j]->l, wagaPtr[j]->m);
	}
}

int main() 
{
	unsigned int n;

	scanf("%u", &n);
	waga0(n);

	return 0;
}
