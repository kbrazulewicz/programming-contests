/* @JUDGE_ID: 16232QS 1680 C++ */

#include <iostream>
#include <set>
#include <string>
using namespace std;

struct string_icase_cmp
{
  bool operator()(const string& s1, const string& s2) const
  {
	  //return strcasecmp(s1.c_str(), s2.c_str()) < 0;
	  return _stricmp(s1.c_str(), s2.c_str()) < 0;
  }
};

char input[80];

int main()
{
	int y, n, q;
	set<string, string_icase_cmp> univ;

	cin >> y >> n >> q;
	cin.getline(input, sizeof(input));

	for (int i = 0; i < n; i++) {
		cin.getline(input, sizeof(input));

		int s = strlen(input);

		char *e = strstr(input, " #");
		if (e == NULL) {
			e = input + s;
		}

		string uni(input, e - input);

		if (univ.count(uni) == 0) {
			if (univ.size() == q) {
				cout << input << endl;
				break;
			} else {
				univ.insert(uni);
			}	
		}
	}

	return 0;
}
