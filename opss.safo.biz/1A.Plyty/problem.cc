#include <iostream>
#include <string>
using namespace std;

#include <math.h>

unsigned long long calculate(int k, int a)
{
	int n = sqrt(k);

	unsigned long long r = a;

	return r * n;
}

int main()
{
	int c, k, a;

	cin >> c;

	while (c--) {
		cin >> k >> a;
		cout << calculate(k, a) << endl;
	}

	return 0;
}
