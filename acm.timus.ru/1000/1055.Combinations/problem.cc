#include <algorithm>
#include <cstdio>
#include <cstring>
#include <math.h>

using namespace std;

static const int MAX_X = 50000;
static const int MAX_X_PRIMES = 5133;

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
		for (i = 0, isPrime = 1, iLimit = floor(sqrt((double)primeCandidate)); aPrimes[i] <= iLimit; i++) {
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

int combination(int n, int m)
{
	int f, p, maxPrimeIndex = 0, result = 0;

	memset(pb, 0, sizeof(pb));

	for (int i = m + 1; i <= n; i++) {
		f = i;
		maxPrimeIndex = max(maxPrimeIndex, (int)gMyLargestPrimeIndex[f]);
		while (f != 1) {
			p = gMyLargestPrimeIndex[f];
			pb[p]++;
			f /= gPrimes[p];
		}
	}
	for (int i = 1; i <= n - m; i++) {
		f = i;
		maxPrimeIndex = max(maxPrimeIndex, (int)gMyLargestPrimeIndex[f]);
		while (f != 1) {
			p = gMyLargestPrimeIndex[f];
			pb[p]--;
			f /= gPrimes[p];
		}
	}

	for (int i = 0; i <= maxPrimeIndex; i++) {
		if (pb[i] > 0) {
			result++;
		}
	}

	return result;
}

int main()
{
	int n, m;

	memset(gMyLargestPrimeIndex, 0, sizeof(gMyLargestPrimeIndex));

	scanf("%d %d", &n, &m);

	gPrimesFound = eratosthenesSieveValueLimit(gPrimes, n);
	primePrepareIndex(gPrimes, gPrimesFound, gMyLargestPrimeIndex, n);

	printf("%d\n", combination(n, m));

	return 0;
}
