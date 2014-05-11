#include <algorithm>
#include <cstdio>
#include <cstring>
#include <math.h>

using namespace std;

static const int MAX_X = 100000;
static const int MAX_X_PRIMES = 9592;

unsigned int  gPrimes[MAX_X_PRIMES];
unsigned int  gPrimesFound;

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


int primeSplit(unsigned int aPrime[], unsigned int aPolynomial[], unsigned int aValue) 
{
	int i = 0;

	while (aValue != 1) {
		if (aValue % aPrime[i] == 0) {
			aPolynomial[i]++;
			aValue /= aPrime[i];
		} else i++;
	}

	return aPrime[i];
}

unsigned int p[MAX_X_PRIMES], b[MAX_X_PRIMES];

int pantofelek()
{
	int n, r, multiplier, maxPrime = 1, bacteriaCount = 1;
	char symbol;

	memset(p, 0, sizeof(p));
	memset(b, 0, sizeof(b));

	scanf("%d\n", &n);
	while (n--) {
		scanf("%c %d\n", &symbol, &multiplier);
		if (multiplier > 1) {
			if (symbol == 'p') {
				r = primeSplit(gPrimes, p, multiplier);
			} else {
				r = primeSplit(gPrimes, b, multiplier);
			}
			maxPrime = max(maxPrime, r);
		}
	}

	for (int i = 0; gPrimes[i] <= maxPrime; i++) {
		if (b[i] > p[i]) {
			for (int j = p[i]; j < b[i]; j++) {
				bacteriaCount *= gPrimes[i];
			}
		} else if (p[i] > b[i]) {
			return -1;
		}
	}

	return bacteriaCount;
}

int main()
{
	int d;

	gPrimesFound = eratosthenesSieveValueLimit(gPrimes, MAX_X);

	scanf("%d", &d);
	while (d--) printf("%d\n", pantofelek());

	return 0;
}
