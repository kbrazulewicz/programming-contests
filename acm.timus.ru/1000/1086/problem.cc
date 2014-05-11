/* @JUDGE_ID: 16232QS 1086 C++ */

#include <iostream>
#include <math.h>

using namespace std;

unsigned int primes[15000] = 
{
	1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
	31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
	73, 79, 83, 89, 97
};


int main()
{
	int primesToFind;
	int maxOrderFound = 25; // orders are from 0
	int primeOrder;

	cin >> primesToFind;
	for (int i = 0; i < primesToFind; i++) {
		cin >> primeOrder;

		while (primeOrder > maxOrderFound) {

			bool isPrime = false;
			int candidate = primes[maxOrderFound] + 2;
			
			while (!isPrime) {
				int i = 1;
				unsigned int dividorLimit = (unsigned int) sqrt((double)candidate);
				while (primes[i] <= dividorLimit) {
					if (candidate % primes[i] == 0) break;
					else i++;
				}
				if (primes[i] > dividorLimit) {
					isPrime = true;
				} else {
					candidate += 2;
				}
			}
			primes[++maxOrderFound] = candidate;
		}

		cout << primes[primeOrder] << endl;
	}
	return 0;
}
