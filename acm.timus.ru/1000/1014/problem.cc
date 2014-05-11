/* @JUDGE_ID: 16232QS 1014 C++ */

#include <iostream>
#include <iterator>
#include <set>

using namespace std;
multiset<int> q;

int main()
{
	unsigned int n;

	cin >> n;

	if (n == 0) {
		q.insert(10);
	} else if (n == 1) {
		q.insert(1);
	} else {
		while (n != 1) {
			for (int i = 9; i > 0; i--) {
				if (i == 1) {
					cout << "-1" << endl;
					return 0;
				} else {
					if (n % i == 0) {
						q.insert(i);
						n /= i;
						break;
					}
				}
			}
		}
	}

	copy(q.begin(), q.end(), ostream_iterator<int>(cout, ""));
	return 0;
}
