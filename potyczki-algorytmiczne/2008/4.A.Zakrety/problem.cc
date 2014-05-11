#include <iostream>
#include <list>
using namespace std;

static const int MAX_N = 500000;

char input[MAX_N + 1];


// size: 1MB
unsigned short int bitval[MAX_N];
// size: 0.5MB
char bitlen[MAX_N];


// size: 1MB(empty)
list<int> dataBackend[0x20000];
list<int> *data[16 + 1] = {
	NULL,
	&dataBackend[0x0000],				// 1
	&dataBackend[0x0000 + 0x0002],		// 2
	&dataBackend[0x0002 + 0x0004],		// 3
	&dataBackend[0x0006 + 0x0008],		// 4
	&dataBackend[0x000E + 0x0010],		// 5
	&dataBackend[0x001E + 0x0020],		// 6
	&dataBackend[0x003E + 0x0040],		// 7
	&dataBackend[0x007E + 0x0080],		// 8
	&dataBackend[0x00FE + 0x0100],		// 9
	&dataBackend[0x01FE + 0x0200],		// 10
	&dataBackend[0x03FE + 0x0400],		// 11
	&dataBackend[0x07FE + 0x0800],		// 12
	&dataBackend[0x0FFE + 0x1000],		// 13
	&dataBackend[0x1FFE + 0x2000],		// 14
	&dataBackend[0x3FFE + 0x4000],		// 15
	&dataBackend[0x7FFE + 0x8000],		// 16
};


int main()
{
	int n;
	unsigned short int a;

	scanf("%d\n", &n);
	fgets(input, n + 1, stdin);

	// setup bitval, bitlen
	a = 0;
	for (int i = 0, ie = min(16, n); i < ie; i++) {
		a <<= 1;
		if (input[i] == 'P') a++;
	}
	for (int i = n; i < 16; i++) {
		a <<= 1;
	}

	for (int i = 0; i < n; i++) {
		int b = min(16, n - i);
		bitval[i] = a;
		bitlen[i] = b;

		do {
			data[b][a >> (16 - b)].push_back(i);
//			printf("position [%d] bitval [0x%0.4hX], bitlen [%hhd]\n", i, a >> (16 - b), b);
		} while (--b);
		
		a <<= 1;
		if (i + 16 < n && input[i + 16] == 'P') {
			a++;
		}
	}


	// solution search
	for (int i = 0; i < n; i++) {
		int bLen = bitlen[i];
		int bLenCumulated = 0;
		unsigned short int bVal = bitval[i] >> (16 - bLen);

		do {
//			printf("Analyze position [%d], bitval [0x%0.4hX], bitlen [%hhd]: substring count [%d]\n", 
//					i, bVal, bLen, data[bLen][bVal].size());

			while (bLen > 0 && data[bLen][bVal].size() == 1) {
				bLen--;
				bVal >>= 1;
			}

			if (bLen == 16) {
				list<int>::const_iterator jE = data[bLen][bVal].end();
				for (list<int>::const_iterator j = data[bLen][bVal].begin(); j != jE; j++) {
					if (i == *j) continue;
					if (n - *j < bLen) continue;

					int substringLength = 16;
					int ii =  i + 16;
					int jj = *j + 16;

					printf("Analyze position [%d] vs [%d]: bitval [0x%0.4hX : 0x%0.4hX], bitlen [%hhd : %hhd], current bLen [%d]\n", 
							ii, jj, bitval[ii], bitval[jj], bitlen[ii], bitlen[jj], bLen);

					while (ii < n && jj < n && bitlen[ii] == bitlen[jj] && bitval[ii] == bitval[jj]) {
							substringLength += 16;
							ii += 16;
							jj += 16;
					}

					if (ii < n && jj < n) {
						substringLength += 16;
						while (bitlen[ii] != bitlen[jj] || bitval[ii] != bitval[jj]) {
							substringLength--;
							ii--;
							jj--;
						}
					}

//					printf("Analyze position [%d] vs [%d]: common substring length [%d]\n", 
//							i, *j, substringLength);

					bLen = max(bLen, substringLength);
				}
				break;
			}
		} while (bLen == 16);
		printf("%d\n", bLen + bLenCumulated);
	}

	return 0;
}
