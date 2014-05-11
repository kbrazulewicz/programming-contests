#include <iostream>
using namespace std;

int main()
{
	unsigned int n, m, p, r;

	cin >> n >> m >> p;

	r = (((1 + m) * m) / 2) * (((1 + n) * n) / 2);

	for (unsigned int i = 1; i <= n && (2 * (i + 1) < p); i++)
	{
		for (unsigned int j = 1; j <= m && (2 * (i + j) < p); j++)
		{
			r -= (n + 1 - i) * (m + 1 - j);
		}
	}

	cout << r << endl;

	return 0;
}
