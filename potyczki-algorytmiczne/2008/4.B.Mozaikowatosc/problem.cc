#include <iostream>
using namespace std;

void scanfLineToShortArray(unsigned short aBuffer[], int aBufferLen)
{
	int index = 0;
	int in;
	char read_digit = 0;
	char read_white = 0;

	while ((in = getchar()) != EOF) {
		if ('0' <= in && in <= '9') {
			if (read_white) {
				index++;
				if (index >= aBufferLen) {
					break;
				}
			}
			aBuffer[index] *= 10;
			aBuffer[index] += in - '0';

			read_white = 0;
			read_digit = 1;
		} else if (in == ' ' || in == '\t') {
			read_white = 1;
			read_digit = 0;
		} else if (in == '\n') {
			break;
		}
	}
}

void scanfLineToIntArray(unsigned int aBuffer[], int aBufferLen)
{
	int index = 0;
	int in;
	char read_digit = 0;
	char read_white = 0;

	while ((in = getchar()) != EOF) {
		if ('0' <= in && in <= '9') {
			if (read_white) {
				index++;
				if (index >= aBufferLen) {
					break;
				}
			}
			aBuffer[index] *= 10;
			aBuffer[index] += in - '0';

			read_white = 0;
			read_digit = 1;
		} else if (in == ' ' || in == '\t') {
			read_white = 1;
			read_digit = 0;
		} else if (in == '\n') {
			break;
		}
	}
}



static const int MAX_N = 300;
static const int MAX_L = 300;
static const int MAX_A = 100000;

unsigned int fags[MAX_N + 1][MAX_L + 1];
unsigned int fagsOpAnd[MAX_N + 1][MAX_L + 1];

int main()
{
	int n;

	// data input
	scanf("%d\n", &n);
	for (int i = 1; i <= n; i++) {
		scanfLineToIntArray(&fags[i][0], MAX_N + 1);
		sort(&(fags[i][1]), &(fags[i][1 + fags[i][0]]));
	}

	for (int i = 1; i <= n; i++) {
		int score = 0;

		// AND operation between fag#i and fag#1-n
		for (int j = 1; j <= n; j++) {
			if (i == j) continue;

			fagsOpAnd[j][0] = 0;

//			printf("fag[%d] AND fag[%d]\n", i, j);

			int ii = 1, jj = 1;
			while (ii <= fags[i][0] && jj <= fags[j][0]) {
//				printf("COMPARE: %d %d\n", fags[i][ii], fags[j][jj]);
				if (fags[i][ii] > fags[j][jj]) {
					jj++;
				} else if (fags[i][ii] < fags[j][jj]) {
					ii++;
				} else {
//					printf("AND: %d\n", fags[j][jj]);
					fagsOpAnd[j][++fagsOpAnd[j][0]] = fags[j][jj];
					ii++;
					jj++;
				}
			}
//			printf("fag[%d] AND fag[%d] is [%d] long\n", i, j, fagsOpAnd[j][0]);
		}


		for (int j = 1; j <= n; j++) {
			if (i == j) continue;
			for (int k = j + 1; k <= n; k++) {
				if (i == k) continue;

				int jj = 1, kk = 1;
				int iX = 0, jX = fagsOpAnd[j][0], kX = fagsOpAnd[k][0];
				while (jj <= jX && kk <= kX) {
					if (fagsOpAnd[j][jj] > fagsOpAnd[k][kk]) {
						kk++;
					} else if (fagsOpAnd[j][jj] < fagsOpAnd[k][kk]) {
						jj++;
					} else {
						iX++;
						jj++;
						kk++;
					}
				}

				jX -= iX;
				kX -= iX;

//				printf("fag[%d] | fag[%d] | fag[%d] : score [%d] long\n", i, j, k, jX * kX);

				score += jX * kX;
			}
		}

		printf("%d\n", score);
	}

	return 0;
}
