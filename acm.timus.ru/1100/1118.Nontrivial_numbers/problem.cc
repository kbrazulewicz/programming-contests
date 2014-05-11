/* @JUDGE_ID: 16232QS 1118 C++ */

#include <cmath>
#include <iostream>
#include <list>
using namespace std;

static const size_t MAX_N = 1000000;

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
 


double calculateTriviality(int n)
{
	int sumOfProperDivisors = 1;
	int maxWorthyDivisor = sqrt((double)n);

	if (maxWorthyDivisor * maxWorthyDivisor == n) {
		sumOfProperDivisors += maxWorthyDivisor;
	}

	for (int i = 2; i < maxWorthyDivisor; i++) {
		if (n % i == 0) {
			sumOfProperDivisors += i;
			sumOfProperDivisors += n / i;
		}
	}

	return (double) sumOfProperDivisors / n;
}

int main()
{
	int i, j;
	double minTriviality = MAX_N;
	int nonTrivialNumber = 0;

	cin >> i >> j;

	if (i == 1) {
		nonTrivialNumber = 1;
	}

	{
		list<unsigned int> primes;
		eratosthenesSieveValueLimit(primes, j);

		for (list<unsigned int>::const_reverse_iterator n = primes.rbegin(); nonTrivialNumber == 0 && *n >= i; n++) {
			if (*n >= i && *n <= j) {
				nonTrivialNumber = *n;
			}
		}
	}

	if (nonTrivialNumber == 0) {
		for (int n = i; n <= j; n++) {
			double t = calculateTriviality(n);
			if (t < minTriviality) {
				minTriviality = t;
				nonTrivialNumber = n;
			}
		}
	}

	cout << nonTrivialNumber << endl;

	return 0;
}
