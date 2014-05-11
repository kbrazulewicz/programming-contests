/* @JUDGE_ID: 16232QS 1080 C++ */

#include <iostream>
#include <iterator>
#include <list>
#include <set>
#include <vector>
using namespace std;

static const int MAX_COUNTRIES = 98;
static const int COLOR_UNDEF = -1;
static const int COLOR_RED   =  0;
static const int COLOR_BLUE  =  1;

set<int> neighbours[MAX_COUNTRIES];
vector<int> colors;
list<int> queue;

int main()
{
	int numberOfCountries;

	cin >> numberOfCountries;
	colors.insert(colors.end(), numberOfCountries, COLOR_UNDEF);

	for (int i = 0; i < numberOfCountries; i++) {
		int neighbour;

		cin >> neighbour;
		while (neighbour != 0) {
			neighbour--;
			neighbours[i].insert(neighbour);
			neighbours[neighbour].insert(i);

			cin >> neighbour;
		}
	}

	colors[0] = COLOR_RED;
	queue.push_back(0);

	while (!queue.empty()) {
		int country = queue.front(); queue.pop_front();
		int color = colors[country];
		int newColor = color == COLOR_RED ? COLOR_BLUE : COLOR_RED;

		for (set<int>::const_iterator i = neighbours[country].begin(); i != neighbours[country].end(); i++) {
			int neighbour = *i;

			if (colors[neighbour] == COLOR_UNDEF) {
				queue.push_back(neighbour);
				colors[neighbour] = newColor;
			} else if (colors[neighbour] == color) {
				cout << -1 << endl;
				return 0;
			}
		}
	}

	copy(colors.begin(), colors.end(), ostream_iterator<int>(cout, ""));

	return 0;
}
