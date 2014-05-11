#include <algorithm>
#include <cstdio>
#include <map>
using namespace std;

static const int MAX_N = 100;
static const int MAX_Z = 1e9;

map<int, int> zagadka;


int reduce(int aValue) {
	int v[10], vi;
	

	if (aValue <= 1) {
		return aValue;
	} else if (aValue < 20) {
		if (aValue % 2 == 0) {
			return aValue / 2;
		} else {
			return aValue;
		}
	}

	int t = aValue;
	vi = 0;
	do {
		v[vi++] = t % 10;
		t /= 10;
	} while (t);
	vi--;

	if (v[vi] - v[0] > 1) return aValue;

	return aValue;
}





int main()
{
	int n, z, zs, zr;

	zagadka.insert(make_pair(0,0));

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &z);

		zs = z;
		do {
			zr = reduce(zs);
		} while (zr != zs);
		printf("%d\n", zr == z ? -1 : zr);
	}

	return 0;
}
