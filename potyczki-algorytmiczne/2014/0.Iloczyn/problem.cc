#include <iostream>
#include <set>
using namespace std;

#define DEBUG

#define EVEN(X) (X % 2 == 0)
#define ODD(X) (X % 2 != 0)

#define FOR(E, I) for(typeof(I.begin()) E = I.begin(); E != I.end(); E++)

const int fibonacci_1e9[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578, 5702887, 9227465, 14930352, 24157817, 39088169, 63245986, 102334155, 165580141, 267914296, 433494437, 701408733};

set<int> fibonacciSequence;

bool testForFibonacciProduct(int n)
{
	if (n == 0)
	{
		return true;
	}
	FOR(i, fibonacciSequence)
	{
		if (n % *i == 0)
		{
			if (fibonacciSequence.find(n / *i) != fibonacciSequence.end())
			{
				return true;
			}
		}
	}

	return false;
}

int main()
{	
	fibonacciSequence.insert(fibonacci_1e9 + 1, fibonacci_1e9 + (sizeof(fibonacci_1e9) / sizeof(fibonacci_1e9[0])));

	int t, n;
	cin >> t;

	while (t--)
	{
		cin >> n;
		cout << (testForFibonacciProduct(n) ? "TAK" : "NIE") << endl;
	}

	return 0;
}
