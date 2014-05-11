/* @JUDGE_ID: 16232QS 1688 C++ */

#include <iostream>
#include <string>
using namespace std;

int main()
{
	int m, s, i;
	unsigned long long n;
	unsigned long long t = 0L;

	cin >> n >> m;
	n *= 3;

	for (i = 1; i <= m; i++)
	{
		int s;

		cin >> s;
		t += s;

		if (t > n) {
			break;
		}
	}

	if (t > n) {
		cout << "Free after " << i << " times." << endl;
	} else {
		cout << "Team.GOV!" << endl;
	}
	return 0;
}
