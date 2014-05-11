#include <iostream>
using namespace std;

int main()
{
	unsigned int k;
	unsigned long p;
	unsigned long powerOf2 = 1;
	unsigned long r = 1L;

	cin >> k;
	for (int i = 0; i <= k; i++) {
		cin >> p;
		r += p * powerOf2;
		powerOf2 *= 2;
	}

	cout << r << endl;

	return 0;
}
