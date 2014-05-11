#include <iostream>
#include <iterator>
#include <map>
#include <vector>

#include <math.h>
using namespace std;


static const unsigned int MAX_A = 10000;

static unsigned int gPrimes[1229];


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
}

void findDividers(int aValue, unsigned int aPrimes[], map<unsigned int, unsigned int>& aDividers)
{
	int iLimit = floor(sqrt((double)aValue));
	int i = 0;
	unsigned int prime = aPrimes[i++];

	while (prime <= iLimit) {
		if (aValue % prime == 0) {
			aDividers[prime]++;
			aValue /= prime;
		} else {
			prime = aPrimes[i++];
		}
	}

	if (aValue != 1) {
		aDividers[aValue]++;
	}
}

int main()
{
	int a;

	eratosthenesSieveValueLimit(gPrimes, MAX_A);

	map<unsigned int, unsigned int> dividers;

	for (int i = 0; i < 10; i++) {
		cin >> a;
		findDividers(a, gPrimes, dividers);
	}

	unsigned int result = 1;
	for (map<unsigned int, unsigned int>::const_iterator i = dividers.begin(); i != dividers.end(); i++) {
		result *= i->second + 1;
		result %= 10;
	}

	cout << result << endl;

	return 0;
}
