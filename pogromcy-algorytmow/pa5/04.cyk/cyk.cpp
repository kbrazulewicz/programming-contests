#include <iostream>
#include <set>
#include <vector>

using namespace std;

#undef _DEBUG

typedef pair<unsigned long long, int> CyclicNumberDefinition;
typedef vector<CyclicNumberDefinition> CyclicNumberDefinitionVector;

int main()
{
	unsigned long long n;

	cin >> n;

	CyclicNumberDefinitionVector cyclicNumbers;
	cyclicNumbers.push_back(make_pair(1LL, 1));
	cyclicNumbers.push_back(make_pair(2LL, 1));
	cyclicNumbers.push_back(make_pair(3LL, 1));
	cyclicNumbers.push_back(make_pair(4LL, 1));
	cyclicNumbers.push_back(make_pair(5LL, 1));
	cyclicNumbers.push_back(make_pair(6LL, 1));
	cyclicNumbers.push_back(make_pair(7LL, 1));
	cyclicNumbers.push_back(make_pair(8LL, 1));
	cyclicNumbers.push_back(make_pair(9LL, 1));
	cyclicNumbers.push_back(make_pair(142857LL, 6));
	cyclicNumbers.push_back(make_pair(588235294117647LL, 16));
	cyclicNumbers.push_back(make_pair(52631578947368421LL, 18));

	set<unsigned long long> cyclicFamilies;

	for (CyclicNumberDefinitionVector::const_iterator i = cyclicNumbers.begin(); i < cyclicNumbers.end(); i++) {
		for (int j = 1; j <= i->second; j++) {
			unsigned long long family = i->first * j;
			cyclicFamilies.insert(family);
#ifdef _DEBUG
			cout << i->first << " * " << j << " = " << family << endl;
#endif
		}
	}

	set<unsigned long long>::const_iterator iFound = cyclicFamilies.lower_bound(n);

	if (iFound == cyclicFamilies.end()) {
		cout << "BRAK" << endl;
	} else {
		cout << *iFound << endl;
	}

	return 0;
}
