#include <iostream>
#include <cstdlib>

using namespace std;

struct waga_t
{
	unsigned int l;
	unsigned int m;	
	unsigned int value;
};

const static int MAX_ELEMENTS 	= 20000;

waga_t	waga[MAX_ELEMENTS];



int waga_sort(const void* a, const void* b) 
{
	return ((waga_t*)a)->value - ((waga_t*)b)->value;
}

// one huge quick sort
void waga0(unsigned int n)
{
	for (int i = 0; i < n; i++) {
		cin >> waga[i].l;
		cin >> waga[i].m;
		waga[i].value = (waga[i].l << (20 - waga[i].m)) + waga[i].l;
	}
	qsort(&waga, n, sizeof(waga_t), waga_sort);

	for (int j = 0; j < n; j++) {
		cout << waga[j].l << " " << waga[j].m << endl;
	}
}

int main() 
{
	unsigned int number;

	cin >> number;
	
	waga0(number);

	return 0;
}
