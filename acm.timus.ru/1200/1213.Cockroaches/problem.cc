/* @JUDGE_ID: 16232QS 1213 C++ */

#include <iostream>
#include <set>
#include <string>
using namespace std;

int main()
{
	string exitCompartment;
	string input;

	set<string> compartments;

	cin >> exitCompartment;

	while (input != "#") {
		cin >> input;
		if (input != "#") {
			size_t pos = input.find('-');
			compartments.insert(input.substr(0, pos));
			compartments.insert(input.substr(pos + 1));
		}
	}

	size_t result = compartments.empty() ? 0 : compartments.size() - 1;
	
	cout << result << endl;

	return 0;
}
