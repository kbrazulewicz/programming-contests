/* @JUDGE_ID: 16232QS 1026 C++ */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> database;

int main()
{
	int n, k, v;
	string tmp;

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> v;
		database.push_back(v);
	}
	cin >> tmp;

	sort(database.begin(), database.end());

	cin >> k;

	for (int i = 0; i < k; i++) {
		cin >> v;
		cout << database[v - 1] << endl;
	}
		
	return 0;
}
