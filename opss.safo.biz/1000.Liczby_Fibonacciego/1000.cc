#include <iostream>
using namespace std;

const static int maxN = 45;

unsigned int fibonacciValues[maxN + 1];


void fibonacci_precalculate(unsigned int aValues[], unsigned int aSize)
{
	if (aSize == 0) return;
	aValues[0] = 1;
	if (aSize == 1) return;
	aValues[1] = 1;

	for (unsigned int i = 2; i <= aSize; i++)
	{
		aValues[i] = aValues[i - 1] + aValues[i - 2];
	}
}

int main()
{
	int d, n;
	fibonacci_precalculate(fibonacciValues, maxN);

	cin >> d;
	while (d--) {
		cin >> n;
		cout << fibonacciValues[n] << endl;
	}
		
	return 0;
}
