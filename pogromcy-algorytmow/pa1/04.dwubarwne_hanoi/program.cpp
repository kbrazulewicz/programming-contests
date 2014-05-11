//
// Krystian Brazulewicz
// krystian.brazulewicz@iq.pl
//
// Hanoi standard problem solution:
// Number of moves needed for n-pieces can be expressed as binary number made of first n digits of:
// '111111111111111 (1)' string
//
// Hanoi 2-color towers solution:
// Number of moves needed for n-pieces can be expressed as binary number made of first n digits of:
// '101101101101101 (101)' string
//
// the only problem here is to represent it in a decimal format ....
// 
#include <iostream>
using namespace std;

const static unsigned int MAX_PIECES	= 1000;
const static unsigned int MAX_BINARY	= 1000 + 1;
const static unsigned int MAX_DECIMAL	=  500;

const static char *BINARY_PATTERN = 
"101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101"
"101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101"
"101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101"
"101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101"
"101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101"
"101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101"
"101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101"
"101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101"
"101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101"
"101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101101"
"1011011011";


char add1_V[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
char add1_C[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};

char mul2_V[10] = {0, 2, 4, 6, 8, 0, 2, 4, 6, 8};
char mul2_C[10] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1};


void add1(char *decimal)
{
	unsigned int i = 0;
	unsigned int c = 1, v = 0;

	// all digits
	while (decimal[i] >= 0 && c) {	
		v = decimal[i] + c;
		decimal[i] = add1_V[v];
		c = add1_C[v];

		i++;
	}
	// another digit
	if (c) {
		decimal[i++] = c;
		decimal[i] = -1;
	}
}

void mul2(char *decimal)
{
	unsigned int i = 0;
	unsigned int c = 0, v = 0;

	// all digits
	while (decimal[i] >= 0) {	
		v = decimal[i];
		decimal[i] = mul2_V[v] + c;
		c = mul2_C[v];

		i++;
	}
	// another digit
	if (c) {
		decimal[i++] = c;
		decimal[i] = -1;
	}
}


void hanoi2Color(int numberOfPieces, char *decimal) 
{
	// first byte - LSB
	static char dec[MAX_DECIMAL];
	unsigned int i, j;

	// initialization
	dec[0] = 0;
	dec[1] = -1;

	for (i = 0; i < numberOfPieces; i++) {
		mul2(dec);
		if (BINARY_PATTERN[i] == '1') {
			add1(dec);
		}
	}

	// transform for printing
	i = 0;
	while (dec[i] >= 0) i++;

	j = 0;
	while (i > 0) {
		decimal[j++] = dec[--i] + '0';
	}
	decimal[j] = 0;
}


int main() 
{
	unsigned int numberOfPieces;
	char numberofMoves[MAX_DECIMAL];

	cin >> numberOfPieces;
	hanoi2Color(numberOfPieces, numberofMoves);
	cout << numberofMoves << endl;
	return 0;
}
