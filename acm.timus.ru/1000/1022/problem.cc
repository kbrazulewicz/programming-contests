/* @JUDGE_ID: 16232QS 1022 C++ */

#include <iostream>
#include <iterator>
#include <list>
#include <set>
using namespace std;

static const int MAX_MARTIANS = 100;

set<int> parents[MAX_MARTIANS];
set<int> children[MAX_MARTIANS];

list<int> queue;
list<int> order;

int main()
{
	int martiansCount;

	cin >> martiansCount;
	for (int i = 0; i < martiansCount; i++) {
		int childIndex;
		do {
			cin >> childIndex;
			if (childIndex != 0) {
				children[i].insert(childIndex - 1);
				parents[childIndex - 1].insert(i);
			}
		} while (childIndex != 0);
	}

	// search for ultimate parents
	for (int i = 0; i < martiansCount; i++) {
		if (parents[i].empty()) {
			queue.push_back(i);
		}
	}

	while (order.size() != (unsigned int) martiansCount) {
		int martian = queue.front();
		queue.pop_front();

		for (set<int>::const_iterator i = children[martian].begin(); i != children[martian].end(); i++) {
			parents[*i].erase(martian);
			if (parents[*i].empty()) {
				queue.push_back(*i);
			}
		}
		children[martian].clear();

		order.push_back(martian + 1);
	}

	copy(order.begin(), order.end(), ostream_iterator<int>(cout, " "));

	return 0;
}
