#include <stdio.h>

/*
 * for a desired precision of n decimal digits
 * k = n * log2(10)
 * 
 * n = 32372;  k = 113316
 * n = 100000; k = 332192
 */

#define K_SIZE 113316

unsigned a = 1e4, b, c = K_SIZE, d, e, f[K_SIZE], g, h, i;
int main()
{
	for (;b = c, c -= 14; i = printf("%04d", e + d / a), e = d % a) {
		while ((g = --b * 2)) {
			d = h * b + a * (i ? f[b] : a / 5); 
			h = d / --g; 
			f[b] = d - g * h;
		}
	}

	return 0;
}
