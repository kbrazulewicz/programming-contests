/* @JUDGE_ID: 16232QS 1585 C++ */

#include <iostream>
#include <string>
using namespace std;

int main()
{
	int n;
	string kind, penguin;
	int e = 0, l = 0, m = 0;

	cin >> n;
	while (n--) {
		cin >> kind >> penguin;
		if (kind == "Emperor") e++;
		else if (kind == "Little") l++;
		else if (kind == "Macaroni") m++;
	}

	int maxP = max(max(e, l), m);

	if (maxP == e) {
		cout << "Emperor Penguin" << endl;
	} else if (maxP == l) {
		cout << "Little Penguin" << endl;
	} else if (maxP == m) {
		cout << "Macaroni Penguin" << endl;
	}

	return 0;
}
