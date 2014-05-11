#include <iostream>
#include <string>
using namespace std;

static const int MAX_N = 1000;

int input[MAX_N];

int main()
{
	int n;
	int numberOfSwaps = 0;
	cin >> n;

	for (int i = 0; i < n; i++) {
		cin >> input[i];
	}

	int i = 0;
	while (i < n - 1) {
		if (input[i] > input[i + 1]) {
			swap(input[i], input[i + 1]); numberOfSwaps++;
			i = i ? i - 1 : i;
		} else i++;
	}

	cout << numberOfSwaps << endl;
			
	return 0;
}
