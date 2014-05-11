#include <cstdio>
#include <cstdlib>
#include <math.h>
using namespace std;

inline int getinteol()
{
	static char i[32];
	fgets(i, sizeof(i), stdin);

	return atoi(i);
}

inline void putinteol(int n)
{
	static char o[32];
	char *oi = o + sizeof(o);

	*(--oi) = 0;

	if (n) {
		while (n) {
			*(--oi) = '0' + n % 10;
			n /= 10;
		}
	} else {
		*(--oi) = '0';
	}

	puts(oi);
}

int main()
{
	int c, n, r;
	double sqrt8 = sqrt(8);
	c = getinteol();

	while (c--) {
		n = getinteol();

		if (n < 3) {
			r = ((int) (sqrt(8 * n - 7) - 1)) >> 1;
		} else {
			r = ((int) (sqrt8 * sqrt(n) - 1)) >> 1;
		}
		putinteol(r);
	}
	
	return 0;
}
