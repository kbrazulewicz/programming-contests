#include <iostream>
#include <vector>
using namespace std;


void permutate(const vector<int>& aElements)
{
}


int main()
{
	int p, e;
	vector<int> elem;
	vector<int> position;

	cin >> p;
	elem.reserve(p);
	position.reserve(p);

	for (int i = 0; i < p; i++) {
		cin >> e;
		elem.push_back(e);
		position.push_back(i);
		
	}

	sort(elem.begin(), elem.end());

	int positionIndex = p - 1;

	if (position[positionIndex] != p - 1) {
		position[positionIndex]++;
	}


	return 0;
}
