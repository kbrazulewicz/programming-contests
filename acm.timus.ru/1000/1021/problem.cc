/* @JUDGE_ID: 16232QS 1021 C++ */

#include <iostream>
#include <set>

using namespace std;

unsigned char numbers[0x10000];

int main()
{
	const int sacredNumber = 10000;
	int n, index;
	
	memset(numbers, 0, sizeof(numbers));

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> index;
		numbers[index + 0x8000] = 1;
	}

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> index;
		if (numbers[sacredNumber + 0x8000 - index] == 1) {
			cout << "YES" << endl;
			return 0;
		}
	}

	cout << "NO" << endl;
	return 0;
}
