#include <iostream>
#include <set>
#include <string>
using namespace std;

const int MAX_N  = 100;
const int MAX_W  = 1000;
const int MAX_WD = 1000;
const int MAX_D  = MAX_W * MAX_WD;

int w[MAX_N]; // weight
int d[MAX_N]; // durability

char s[MAX_D]; // strategy

bool winningStrategyExists()
{
	int n, wd, maxD;
	int minAccDurIndex = 0;

	// read data (already sorted)
	scanf("%d", &n);
	for (int i = 0; i < n; i++) { scanf("%d", w + i); }
	scanf("%d", &wd);

	// calculate durability
	for (int i = 0; i < n; i++) { d[i] = w[i] * (wd - 1); }
	maxD = d[n - 1];

	// initialize strategy
	memset(s, 0, sizeof(s));

	int looser = 0;
	while (looser <= maxD) {
		if (s[looser] == 0) {
			while (looser > d[minAccDurIndex]) minAccDurIndex++;
			if (looser == d[minAccDurIndex]) return true;

			s[looser] = -1;
			for (int i = minAccDurIndex; i < n; i++) {
				if (d[i] >= looser) {
					int winner = looser + w[i];
					if (s[winner] == 0 && winner < MAX_D) {
						s[winner] = 1;
					}
				}
			}
		}
		looser++;
	}
	return false;
}

int main()
{
	int c;
	scanf("%d", &c);
	while (c--) {
		printf("%s\n", winningStrategyExists() ? "tak" : "nie");
	}
	return 0;
}
