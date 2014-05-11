#include <stdio.h>

int c2(int x)
{
	int r;
	for (r = 0; x; x >>= 1) r += x;
	return r;
}

int main()
{
	int d, n, k;

	scanf("%d", &d);

	while (d--) {
		scanf("%d%d", &n, &k);
		puts(k <= n && (c2(k) + c2(n - k) >= c2(n)) ? "N" : "P");
	}
	return 0;
}
