#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

/**
 * http://mathworld.wolfram.com/PrimeCountingFunction.html
 *
 * x         pi(x)
 * 10^1          4
 * 10^2         25
 * 10^3        168
 * 10^4       1229
 * 10^5       9592
 * 10^6      78498
 * 10^7     664579
 * 10^8    5761455
 * 10^9   50847534
 * 10^10 455052511
 *
 * pi(x) < 1.25506 * x / ln(x)
 */
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

/**
 *
 */
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


void eratosthenesSieveValueLimit(list<unsigned int>& primes, unsigned int primeValueLimit)
{
	unsigned int primeCandidate;

	primes.push_back(2);

	for (primeCandidate = 3; primeCandidate <= primeValueLimit; primeCandidate += 2) {
		bool isPrime = true;
		int iLimit = floor(sqrt((double)primeCandidate));

		for (list<unsigned int>::const_iterator i = primes.begin(); isPrime && *i <= iLimit; i++) {
			if (primeCandidate % *i == 0) {
				isPrime = false;
			}
		}

		if (isPrime) {
			primes.push_back(primeCandidate);
		}
	}
} 
