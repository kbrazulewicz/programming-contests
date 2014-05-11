/* @JUDGE_ID: 16232QS 1114 C++ */

#include <iostream>
using namespace std;

int main()
{
	int n, a, b;

	cin >> n >> a >> b;

	unsigned long long c_an = 1;
	unsigned long long c_bn = 1;

	for (unsigned long long i = 1; i <= a; i++) 
	{
		c_an *= (n + a - i + 1);
		c_an /= i;
	}

	for (unsigned long long i = 1; i <= b; i++) 
	{
		c_bn *= (n + b - i + 1);
		c_bn /= i;
	}

	cout << c_an * c_bn << endl;

	return 0;
}
