/**
 * Fibonacci sequence
 */
#include <iostream>
using namespace std;

static const int MAX_N = 45;
unsigned int flags[MAX_N + 1];

int main()
{
	int n;

	flags[1] = 2;
	flags[2] = 2;
	
	cin >> n;

	for (int i = 3; i <= n; i++) {
		flags[i] = flags[i - 1] + flags[i - 2];
	}

	cout << flags[n] << endl;
	
	return 0;
}
