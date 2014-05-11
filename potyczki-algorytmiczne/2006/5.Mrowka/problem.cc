/**
 *
 * An = 3 * Bn-1 - 2 * An-2
 * Bn = 2 * Cn-1 + An-1 - 2 * Dn-2
 * Cn = 2 * Bn-1 + Dn-1 - 2 * Cn-2
 * Dn = 3 * Cn-1 - 2 * Dn-2
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

char eg[8][8][4] = {
	{ "BED", "CFX", "XXX", "CHX", "FHX", "XXX", "XXX", "XXX" },
	{ "DEX", "ACF", "DGX", "XXX", "XXX", "EGX", "XXX", "XXX" },
	{ "XXX", "AFX", "BDG", "AHX", "XXX", "XXX", "FHX", "XXX" },
	{ "BEX", "XXX", "BGX", "ACH", "XXX", "XXX", "XXX", "EGX" },
	{ "BDX", "XXX", "XXX", "XXX", "AFH", "BGX", "XXX", "DGX" },
	{ "XXX", "ACX", "XXX", "XXX", "AHX", "BCG", "CHX", "XXX" },
	{ "XXX", "XXX", "BDX", "XXX", "XXX", "BEX", "CFH", "DEX" },
	{ "XXX", "XXX", "XXX", "ACX", "AFX", "XXX", "CFX", "DEG" },
};

void stupidGen(char v1, char v2, int k)
{
	int l = 1;
	vector<string> a, b;

	a.push_back(string(1, v1) + eg[v1 - 'A'][v1 - 'A'][0]);
	a.push_back(string(1, v1) + eg[v1 - 'A'][v1 - 'A'][1]);
	a.push_back(string(1, v1) + eg[v1 - 'A'][v1 - 'A'][2]);

	for (l = 1; l < k; l++) {
		b.clear();
		for (int i = 0; i < a.size(); i ++) {
			string stem = a[i];
			b.push_back(stem + eg[stem[l - 1] - 'A'][stem[l] - 'A'][0]);
			b.push_back(stem + eg[stem[l - 1] - 'A'][stem[l] - 'A'][1]);
		}
		a = b;
	}

	int c = 0;
	for (int i = 0; i < a.size(); i ++) {
		if (a[i][k] == v2) {
			cout << a[i] << endl;
			c++;
		}
	}

	cout << "element count [" << c << "]" << endl;
}

int main()
{
	char v1, v2;
	int k, p;

	scanf("%c %c %d %d", &v1, &v2, &k, &p);

	stupidGen(v1, v2, k);
	
	return 0;
}
