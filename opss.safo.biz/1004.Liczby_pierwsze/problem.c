#include <math.h>
#include <memory.h>
#include <stdio.h>

unsigned char sieve[165000];
unsigned int primes[15000];


void eratosthenesSieveInit(unsigned char aSieve[], unsigned int aSize)
{
	memset(aSieve, 1, aSize);
	aSieve[0] = 0;
}

/**
 *
 */
int eratosthenesSieveCalc(unsigned char aSieve[], unsigned int aSieveSize, 
		unsigned int aPrimes[], unsigned int aPrimeNubmerLimit)
{
	unsigned int currentValue = 2;
	unsigned int primesFound = 0;
	unsigned int sieveValueLimit = aSieveSize * 2;
	unsigned int sieveValueSqrt = sqrt(sieveValueLimit) + 1;
	unsigned int i;

	aPrimes[primesFound++] = currentValue;
	currentValue = 3;

	while (primesFound < aPrimeNubmerLimit && currentValue < sieveValueSqrt) {
		if (aSieve[currentValue >> 1]) {
			aPrimes[primesFound++] = currentValue;
			for (i = (currentValue * currentValue) >> 1; i < aSieveSize; i += currentValue) {
				aSieve[i] = 0;
			}
		}
		currentValue += 2;
	}

	while (primesFound < aPrimeNubmerLimit && currentValue < sieveValueLimit) {
		if (aSieve[currentValue >> 1]) {
			aPrimes[primesFound++] = currentValue;
		}
		currentValue += 2;
	}

	return primesFound;
}

int main()
{
	int primesNo;
	int c, n;
	eratosthenesSieveInit(sieve, sizeof(sieve));
	primesNo = eratosthenesSieveCalc(sieve, sizeof(sieve) / sizeof(sieve[0]), 
			primes, sizeof(primes) / sizeof(primes[0]));

	scanf("%d", &c);
	while (c--) {
		scanf("%d", &n);
		printf("%d\n", primes[n - 1]);
	}

	return 0;
}
