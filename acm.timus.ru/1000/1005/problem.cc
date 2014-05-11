/* @JUDGE_ID: 16232QS 1005 C++ */

#include <iostream>

#include <algorithm>
#include <iterator>
#include <numeric>
#include <set>
#include <vector>

using namespace std;

int main()
{
	int numberOfStones;
	vector<int> stones;

	cin >> numberOfStones;
	stones.reserve(numberOfStones);
	copy(istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(stones));

	set<int> weightDifference;
	weightDifference.insert(accumulate(stones.begin(), stones.end(), 0));

	for (vector<int>::const_iterator iStone = stones.begin(); iStone != stones.end(); iStone++) {
		for (set<int>::const_iterator iDiff = weightDifference.lower_bound(2 * *iStone); iDiff != weightDifference.end(); iDiff++) {
			weightDifference.insert(*iDiff - 2 * *iStone);
		}
	}


	cout << *weightDifference.begin() << endl;

	return 0;
}
