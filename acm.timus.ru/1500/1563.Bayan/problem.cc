/* @JUDGE_ID: 16232QS XXXX C++ */

#include <iostream>
#include <set>
#include <string>
using namespace std;

int main()
{
	int n, r = 0;
	string brand;
	set<string> visitedBrands;

	cin >> n;
	cin.ignore(1, '\n');

	while (n--) {
		getline(cin, brand);
		pair<set<string>::iterator, bool> x = visitedBrands.insert(brand);
		if (!x.second) r++;
	}

	cout << r << endl;

	return 0;
}
