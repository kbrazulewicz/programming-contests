/* @JUDGE_ID: 16232QS 1581 C++ */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
using namespace std;

static const int MAX_N = 1000;

int output[2 * MAX_N];

int main()
{
	int n, a, b;
	int o = 0, length = 1;

	cin >> n >> a;

	n--;
	while (n--) {
		cin >> b;

		if (b == a) {
			length++;
		} else {
			output[o++] = length;
			output[o++] = a;
			length = 1;
			a = b;
		}
	}

	output[o++] = length;
	output[o++] = a;

	copy(output, output + o, ostream_iterator<int>(cout, " "));
	cout << endl;

	return 0;
}
