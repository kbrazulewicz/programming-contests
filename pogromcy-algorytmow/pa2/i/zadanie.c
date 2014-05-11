#define DEBUG 0
#define MAX_BIN_LENGTH	512
#define MAX_DEC_LENGTH	160
#include <stdio.h>
#include <string.h>




unsigned char gDivide[20] = {0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9};
unsigned char gRemainder[10] = {0, 10, 0, 10, 0, 10, 0, 10, 0, 10};


void dec2bin(const char *dec, unsigned char *bin, int binLength)
{
	static char d[MAX_DEC_LENGTH];
	unsigned char *b;
	unsigned char remainder;
	int i, l, notZero;

	b = bin + binLength;
	l = strlen(dec);

	strcpy(d, dec);
	for (i = 0; i < l; d[i++] -= '0');

	do {
		remainder = 0;
		notZero = 0;
		for (i = 0; i < l; i++) {
			unsigned char v = d[i];

			d[i] = gDivide[v + remainder];
			remainder = gRemainder[v];
			if (d[i]) notZero = 1;
		}
		*(--b) = remainder ? 1 : 0;
	} while (notZero);

	while (b != bin) *(--b) = 0;

#if DEBUG
	printf("DEC: %s\n", dec);
	printf("BIN: ");
	for (i = 0; i < binLength; i++) {
		printf("%d", bin[i]);
	}
	printf("\n");
#endif
}


int main()
{
	unsigned char commonPart[MAX_BIN_LENGTH];
	int commonLength = 0;
	unsigned char convertBuffer[MAX_BIN_LENGTH];
	char inputBuffer[MAX_DEC_LENGTH];
	
	int vGeneration, vNumber;
	int i, j;

	scanf("%d %d\n", &vGeneration, &vNumber);

	scanf("%s\n", inputBuffer);
	dec2bin(inputBuffer, convertBuffer, vGeneration);
	commonLength = vGeneration;
	memcpy(commonPart, convertBuffer, commonLength);

	for (i = 1; i < vNumber; i++) {
		scanf("%s\n", inputBuffer);
		dec2bin(inputBuffer, convertBuffer, vGeneration);
		j = 0;
		while (j < commonLength && convertBuffer[j] == commonPart[j]) j++;
		commonLength = j;
	}
	
	printf("%d\n", commonLength);
	return 0;
}
