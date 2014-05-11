/* @JUDGE_ID: 16232QS 1044 C++ */

#include <iostream>
#include <map>

using namespace std;


int calculateSum(int aNumber)
{
	int sum = 0;
	while (aNumber != 0) {
		sum += aNumber % 10;
		aNumber /= 10;
	}
	return sum;
}


int main()
{
	int numberOfDigits;
	int numberRange;
	typedef map<int, int> magicNumbersMap;
	magicNumbersMap magicNumbers;
	int magicNumbersCount = 0;

	cin >> numberOfDigits;
	numberOfDigits /= 2;

	numberRange = 1;
	for (int i = 0; i < numberOfDigits; i++) numberRange *= 10;

	for (int i = 0; i < numberRange; i++) {
		magicNumbers[calculateSum(i)]++;
	}

	for (magicNumbersMap::const_iterator i = magicNumbers.begin(); i != magicNumbers.end(); i++) {
		magicNumbersCount += i->second * i->second;
	}

	cout << magicNumbersCount << endl;
	
	return 0;
}
