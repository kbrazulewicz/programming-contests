#include <stdio.h>

int main() 
{
	int n, m;
	int k, o, d;
	int i;

	scanf("%d%d", &n, &m);
	
	for (i = 0; i < n; i++) {
		scanf("%d%d%d", &k, &o, &d);
		if (m < k) {
			puts("komin");
		} else if (m < o) {
			puts("okno");
		} else if (m < d) {
			puts("drzwi");
		} else {
			puts("brak");
		}
	}

	return 0;
}
