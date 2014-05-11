#include <iostream>
using namespace std;

long fibVal[40] = {
	0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

long fib(int n)
{
	for(int i = 2; i <= n; i++) {
		fibVal[i] = fibVal[i - 1] + fibVal[i - 2];
	}

	return fibVal[n];
}

int main()
{
	int n;

	cin >> n;
	cout << fib(n) << endl;
}
