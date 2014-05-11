/* @JUDGE_ID: 16232QS 1644 C++ */

#include <iostream>
#include <string>
using namespace std;

int main()
{
	int n, x;
	int h = 2, s = 10;
	string response;

	cin >> n;

	while (n--) {
		cin >> x >> response;

		if (response == "hungry") {
			h = max(h, x);
		} else {
			s = min(s, x);
		}
	}

	if (s > h) {
		cout << s << endl;
	} else {
		cout << "Inconsistent" << endl;
	}

	return 0;
}
