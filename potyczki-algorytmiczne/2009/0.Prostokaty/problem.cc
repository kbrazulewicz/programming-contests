#include <iostream>
using namespace std;

int main()
{
	unsigned int n, i, r = 0;

	cin >> n;

	for (int i = 1; i * i <= n; i++) {
		r += n / i - i + 1;
	}

	cout << r << endl;

	return 0;
}
