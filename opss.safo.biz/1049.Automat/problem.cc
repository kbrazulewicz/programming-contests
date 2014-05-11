#include <algorithm>
#include <cstdio>
#include <functional>
using namespace std;

const int MAX_C = 100;
const int MAX_N = 1000;
const int MAX_K = 100;

int nominal[MAX_K];
int change[MAX_N + 1];

int main()
{
	int c, n, k, x;

	scanf("%d", &c);

	while (c--) {

		scanf("%d%d", &n, &k);

		for(int i = 0; i < k; scanf("%d", nominal + i++));

		k = remove_if(nominal, nominal + k, bind2nd(greater<int>(), n)) - nominal;
		sort(nominal, nominal + k, greater<int>());

		memset(change, 0, sizeof(change));

		for (int i = 0; i < k; i++) {
			int coin = nominal[i];
			change[coin] = 1;

			if (coin == n) break;

			for (int j = coin, k = coin + j; k <= n; j++, k++) {
				if (change[j]) {
					if (change[k]) {
						change[k] = min(change[k], change[j] + 1);
					} else {
						change[k] = change[j] + 1;
					}
				}
			}
		}

		printf("%d\n", change[n]);
	}
	return 0;
}
