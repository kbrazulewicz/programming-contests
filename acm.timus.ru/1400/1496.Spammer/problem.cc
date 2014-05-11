/* @JUDGE_ID: 16232QS 1496 C++ */

#include <iostream>
#include <set>
#include <string>
using namespace std;

int main()
{
	int n;
	string team;

	set<string> recognizedTeams;
	set<string> spammer;

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> team;

		pair<set<string>::iterator, bool> r = recognizedTeams.insert(team);
		if (!r.second) {
			spammer.insert(team);
		}
	}

	for (set<string>::const_iterator i = spammer.begin(); i != spammer.end(); i++)
	{
		cout << *i << endl;
	}

	return 0;
}
