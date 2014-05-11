#include <iostream>
#include <string>
using namespace std;

bool binary_is_divisibleBy3(std::string& aNumber)
{
	int evenOnes = 0, oddOnes = 0;
	int length = aNumber.length();
	bool indexEven = true;

	for (int i = length - 1; i >= 0; i--) {
		if (aNumber[i] == '1') {
			indexEven ? evenOnes++ : oddOnes++;
		}

		indexEven = ! indexEven;
	}

	return (abs(evenOnes - oddOnes) % 3 == 0);

}

int main()
{
	int c;
	string b;

	cin >> c;

	while (c--) {
		cin >> b;
		cout << (binary_is_divisibleBy3(b) ? 0 : 1) << endl;
	}

	return 0;
}
