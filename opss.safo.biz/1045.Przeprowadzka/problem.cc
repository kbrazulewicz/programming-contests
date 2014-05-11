#include <iostream>
#include <string>
using namespace std;

const int MAX_K = 100;
const int MAX_N = 10000;
const int MAX_X = 1000;

int x[MAX_N];

int main()
{
	int n, k, sumaX = 0, minPack;

	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d", x + i);
		sumaX += x[i];
	}

	minPack = sumaX / k;
	if (sumaX % k) minPack++;

	printf("N [%d] K[%d]\n", n, k);
	printf("SUM [%d] MIN-PACK[%d]\n", sumaX, minPack);

	return 0;
}
