#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

unsigned char sieve[31623]; // sqrt(10e9)
unsigned char primes[1000001]; // sqrt(10e9)


void prime_prepareSieveOfEratosthenes(unsigned char sieve[], unsigned int n)
{
	unsigned int i, j;
	unsigned int l = (unsigned int) sqrt(n);

	sieve[0] = sieve[1] = 0;
	i = 2;
	for (j = 2 * i; j <= l; j += i) sieve[j] = 0;

	for (i = 3; i <= l; i+= 2) {
		if (sieve[i]) {
			for (j = 2 * i; j <= l; j += i) sieve[j] = 0;
		}
	}
}

void prime_sieveOfEratosthenes(unsigned char sieve[], unsigned char primes[],
		unsigned int m, unsigned int n)
{
	unsigned int i, j;
	unsigned int limit = (unsigned int) sqrt(n);

	i = 2;
	for (j = max(2 * i, (m % i) ? m + i - m % i : m); j <= n; j += i) {
		primes[j - m] = 0;
	}

	i = 3;
	while (i <= limit) {
		if (sieve[i]) {
			for (j = max(2 * i, (m % i) ? m + i - m % i : m); j <= n; j += i) {
				primes[j - m] = 0;
			}
		}
		i+=2;
	}
}



void primeSearch(int m, int n)
{
	int i, l;

	memset(primes, 1, sizeof(primes));

	m = max(m, 2);
	prime_sieveOfEratosthenes(sieve, primes, m, n);

	l = n - m;

	for (i = 0; i <= l; i++) {
		if (primes[i]) {
			printf("%d\n", i + m);
		}
	}
	
}


const unsigned int maxT = 10;

int main()
{
	int t, i;
	int m[maxT];
	int n[maxT];
	int maxN = 0;

	memset(sieve, 1, sizeof(sieve));
	scanf("%d", &t);

	for (i = 0; i < t; i++) {
		scanf("%d %d", &m[i], &n[i]);
		maxN = max(maxN, n[i]);
	}

	prime_prepareSieveOfEratosthenes(sieve, maxN);

	for (i = 0; i < t; i++) {
		if (i) puts("");
		primeSearch(m[i], n[i]);
	}

	return 0;
}
