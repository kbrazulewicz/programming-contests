//
// Krystian Brazulewicz
// krystian.brazulewicz@iq.pl
//
#include <iostream>
#include <string>

using namespace std;

const static unsigned int MAX_DECIMAL	= 501;
const static unsigned int MAX_BINARY	= 2001;


int div2Remainder[20] =
{
	0, 10, 0, 10, 0, 10, 0, 10, 0, 10,
	0, 10, 0, 10, 0, 10, 0, 10, 0, 10,
};


void dec2bin(const char dec[MAX_DECIMAL], char bin[MAX_BINARY])
{
	char decimal[MAX_DECIMAL];
	int  decimalLength;
	int i = 0;

	strcpy(decimal, dec);
	decimalLength = strlen(decimal);
	bin[0] = '\0';
	
	i = 0;
	while (decimal[i]) {
		decimal[i] = decimal[i] - '0';
		i++;
	}
	decimal[i] = -1;

	char *decPtr;
	int value;
	while (decimalLength) {
		decPtr = decimal;
		value = 0;

		while (*decPtr >= 0) {
			value += *decPtr;
			*decPtr = value >> 1;
			value = div2Remainder[value];
			decPtr++;
		}
		memmove(bin + 1, bin, strlen(bin) + 1);
		bin[0] = value ? '1' : '0';

		i = 0;
		while (!decimal[i]) i++;
		if (i) {
			decimalLength -= i;
			memmove(decimal, decimal + i, decimalLength + 1);
		}
	}
}


void optimize(char bin[MAX_BINARY])
{
	int p, l, i;

	p = l = strlen(bin) - 1;

	while (p) {
		// search for next '1'
		while (p >= 0 && bin[p] == '0') p--;
		if (p < 2) break;
		
		// search for next '0'
		l = p;
		while (l >= 0 && bin[l] == '1') l--;

		// transformation
		if (p - l > 1) {
			bin[p] = 'X';
			while (p > l) {
				bin[--p] = '0';
			} while (p > l);
		
			if (p >= 0) 
				bin[l] = '1';
			else {
				bin[0] = '0';
				memmove(bin + 1, bin, strlen(bin) + 1);
				bin[0] = '1';			
			}
		}
		else p = l - 1;
	}
}


int countNonZeros(const char *value)
{
	int count = 0;

	while (*value) {
		if (*value != '0') count++;
		value++;
	}

	return count;
}


int main()
{
	unsigned int maxDigits;
	string decimalNumber;
	char binaryNumber[MAX_BINARY];

	cin >> maxDigits >> decimalNumber;

	dec2bin(decimalNumber.c_str(), binaryNumber);
/*	
	cout << binaryNumber << endl;

	cout << "total digits [" << strlen(binaryNumber) << "], " 
		 << "non-zero digits [" << countNonZeros(binaryNumber) << "]" << endl;
*/
	optimize(binaryNumber);

/*	
	cout << binaryNumber << endl;

	cout << "total digits [" << strlen(binaryNumber) << "], " 
		 << "non-zero digits [" << countNonZeros(binaryNumber) << "]" << endl;
*/

	cout << countNonZeros(binaryNumber) << endl;
	
	return 0;
}
