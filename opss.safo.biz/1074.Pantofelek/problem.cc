#include <algorithm>
#include <cstdio>
#include <cstring>
#include <math.h>

using namespace std;

static const int MAX_X = 100000;
static const int MAX_X_PRIMES = 9592;

unsigned int gPrimes[MAX_X_PRIMES];
unsigned int gPrimesFound;

unsigned int gMyLargestPrimeIndex[MAX_X + 1];

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


void primePrepareIndex(unsigned int aPrime[], unsigned int aPrimeCount, unsigned int aPrimeIndex[], unsigned int aMaxValue)
{
	unsigned int iStart = 0, iLimit = 0;

	for (int p = 0; p < aPrimeCount && aPrime[p] <= aMaxValue; p++) {
		for (int i = aPrime[p]; i <= aMaxValue; i += aPrime[p]) {
			aPrimeIndex[i] = p;
		}
	}
}


int pb[MAX_X_PRIMES];

int pantofelek()
{
	int i, n, r, multiplier, maxPrimeIndex = 0, bacteriaCount = 1;
	char symbol;

	memset(pb, 0, sizeof(pb));

	scanf("%d\n", &n);
	while (n--) {
		scanf("%c %d\n", &symbol, &multiplier);
		if (multiplier > 1) {
			maxPrimeIndex = max(maxPrimeIndex, (int)gMyLargestPrimeIndex[multiplier]);

			while (multiplier != 1) {
				i = gMyLargestPrimeIndex[multiplier];
				if (symbol == 'p') {
					pb[i]--;
				} else {
					pb[i]++;
				}
				multiplier /= gPrimes[i];
			}
		}
	}

	for (int i = 0; i <= maxPrimeIndex; i++) {
		//printf("%d: %d %d\n", i, gPrimes[i], pb[i]);
		if (pb[i] > 0) {
			for (int j = 0; j < pb[i]; j++) {
				bacteriaCount *= gPrimes[i];
			}
		} else if (pb[i] < 0) {
			return -1;
		}
	}

	return bacteriaCount;
}

int main()
{
	int d;

	memset(gMyLargestPrimeIndex, 0, sizeof(gMyLargestPrimeIndex));

	gPrimesFound = eratosthenesSieveValueLimit(gPrimes, MAX_X);
	primePrepareIndex(gPrimes, gPrimesFound, gMyLargestPrimeIndex, MAX_X);

	scanf("%d", &d);
	while (d--) {
		printf("%d\n", pantofelek());
	}

	return 0;
}
