#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

static const size_t MAX_N = 1000;

int a[MAX_N];

int main()
{
	int n, k, s;

	scanf("%d%d%d", &n, &k, &s);

	for (int i = 0; i < n; scanf("%d", &a[i++]));

	sort(a, a + n, greater<int>());

	for (int i = 0, r = 0; i < n; i++) {
		r += a[i];
		if (r >= k * s) {
			printf("%d\n", i + 1);
			break;
		}
	}

	return 0;
}
