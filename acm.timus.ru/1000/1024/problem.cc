/* @JUDGE_ID: 16232QS 1024 C++ */

#include <iostream>
#include <iterator>
#include <vector>
#include <utility>
using namespace std;

/**
 * Greatest Common Divisor Euclidean algorithm
 *
 * O(n) complexity (n is the number of digits in the input)
 */
int greatestCommonDivisor(int a, int b)
{
	int tmp;
	while (b != 0) {
		tmp = a % b;
		a = b;
		b = tmp;
	}

	return abs(a);
}


/** 
 * Least Common Multiple algorithm
 */
int leastCommonMultiple(int a, int b)
{
	int gcd = greatestCommonDivisor(a, b);
	return (a / gcd) * b;
}



vector< pair<int, bool> > permutation;
vector<int> cycleLengths;

int main()
{
	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		permutation.push_back(make_pair(t - 1, false));
	}

	for (int i = 0; i < n; i++) {
		if (!permutation[i].second) {
			int cycleLength = 1;
			int value = permutation[i].first;
			while (value != i) {
				cycleLength++;
				permutation[value].second = true;
				value = permutation[value].first;
			}
			cycleLengths.push_back(cycleLength);
		}
	}

	int order = 1;
	for (vector<int>::const_iterator i = cycleLengths.begin(); i != cycleLengths.end(); i++) {
		order = leastCommonMultiple(order, *i);
	}

	cout << order << endl;

	return 0;
}
