/* @JUDGE_ID: 16232QS 1349 C++ */

#include <iostream>
#include <string>
using namespace std;

int main()
{
	int n;

	cin >> n;

	switch (n) {
		case 1:
			cout << 1 << " " << 2 << " " << 3 << endl;
			break;
		case 2:
			cout << 3 << " " << 4 << " " << 5 << endl;
			break;
		default:
			cout << -1 << endl;
	}
	
	return 0;
}
