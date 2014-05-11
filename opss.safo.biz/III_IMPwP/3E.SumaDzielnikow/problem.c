#include <math.h>
#include <stdio.h>
#include <string.h>

#define MAX_N         1000000000
#define MAX_PRIME_VAL 31608
#define MAX_PRIME_CNT 3401

unsigned int primes[MAX_PRIME_CNT];

int eratosthenesSieveValueLimit(unsigned int aPrimes[], unsigned int aPrimeValueLimit)
{
	unsigned int primeCandidate;
	unsigned int primesFound = 0;

	aPrimes[primesFound++] = 2;

	for (primeCandidate = 3; primeCandidate <= aPrimeValueLimit; primeCandidate += 2) {
		int isPrime, i, iLimit;
		for (i = 0, isPrime = 1, iLimit = floor(sqrt(primeCandidate)); aPrimes[i] <= iLimit; i++) {
			if (primeCandidate % aPrimes[i] == 0) {
				isPrime = 0;
				break;
			}
		}
		if (isPrime) {
			aPrimes[primesFound++] = primeCandidate;
		}
	}

	return primesFound;
}


unsigned int product[MAX_PRIME_CNT];

// http://planetmath.org/encyclopedia/FormulaForSumOfDivisors.html
unsigned int resolve(int n, int m)
{
	unsigned int maxPrimeInProduct = 1;
	unsigned int sumOfDivisors = 1;
	memset(product, 0, sizeof(product));

	int nOrig = n;
	for (int i = 0; n != 1 && i < MAX_PRIME_CNT; i++) {
		while (n % primes[i] == 0) {
			n /= primes[i];
			product[i]++;
			maxPrimeInProduct = primes[i];
		}
		if (product[i]) {
			unsigned long long x = primes[i];
			for (int j = 0; j < product[i]; j++) {
				x *= primes[i];
			}
			x -= 1;
			x /= (primes[i] - 1);
			x *= sumOfDivisors;

			sumOfDivisors = (x % m);
		}
	}
	if (maxPrimeInProduct == 1) {
		sumOfDivisors += (nOrig % m);
	} else if (n != 1) {
		sumOfDivisors *= (n + 1) % m;
	}

	return sumOfDivisors %= m;
}


int main()
{
	int c, m, n;

	eratosthenesSieveValueLimit(primes, MAX_PRIME_VAL);

	scanf("%d%d", &c, &m);
	while (c--) {
		scanf("%d", &n);
		printf("%d\n", resolve(n, m));
	}

	return 0;
}
