#include <algorithm>
#include <cstdio>
using namespace std;

// Binary density
// arxiv.org/PS_cache/arxiv/pdf/0910/0910.3503v1.pdf
 

static const int MAX_N = 1000000;

int rank[MAX_N + 1];

int skipMisMatch(int n, int k)
{
	int l = n / (k + 1);
	for (int l = n / (k + 1); l >= 1; l--)
	{
		int a = 1, b = l * (k + 1);

		while (b <= n)
		{
			int err = abs(l - (rank[b] - rank[a - 1]));

			if (err == 0) {
				return b - a + 1;
			} else {
				a += err; b += err;
			}
		}
	}

	return 0;
}


int main()
{
	int n, k = 0;

	scanf("%d%d\n", &n, &k);

	for (int i = 1; i <= n; i++)
	{
		rank[i] = rank[i - 1];
		if (getchar() == 'R') rank[i]++;
	}

	printf("%d\n", skipMisMatch(n, k));

	return 0;
}
