#include <iostream>
#include <string>
using namespace std;

template<typename T>
T calculateSumOfDigits(T a, unsigned int base = 10) {
	T x = 0;

	while (a != 0) {
		x += a % base;
		a /= base;
	}

	return x;
}

int process(unsigned long long n, int b)
{
	while (n >= b) {
		n = calculateSumOfDigits<unsigned long long>(n, b);
	}

	return n;
}

int main()
{
	unsigned int l;
	unsigned long long n;
	unsigned int b;
	char resultTranslation[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	cin >> l;

	for (int i = 0; i < l; i++) {
		cin >> n >> b;
		unsigned long long sn = ((n + 1) * n) / 2;
		cout << resultTranslation[process(sn, b)] << endl;
	}

	return 0;
}
