/* @JUDGE_ID: 16232QS 1683 C++ */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
using namespace std;

int main()
{
	int n;
	list<int> f;

	cin >> n;

	while (n != 1) {
		f.push_back(n / 2);
		n = (n + 1) / 2;
	}

	cout << f.size() << endl;
	copy(f.begin(), f.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	return 0;
}
