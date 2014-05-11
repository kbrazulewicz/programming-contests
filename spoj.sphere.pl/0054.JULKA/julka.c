#include <stdio.h>

#define MAX_LENGTH 101

const int bigint_precision = MAX_LENGTH;

void bigint_assign(char* aOutput, const char *aInput)
{
	memset(aOutput, '0', bigint_precision);
	strcpy(aOutput + bigint_precision - strlen(aInput), aInput);
}

void bigint_div2(char* aOutput, const char *aInput)
{
	int c = 0;
	while (*aInput) {
		*aOutput = ((*aInput - '0' + 10 * c) >> 1) + '0';
		c = (*aInput - '0') & 1;

		aInput++;
		aOutput++;
	}
	*aOutput = 0;
}

/**
 * r = a + b
 */
void bigint_add(char* r, const char *a, const char *b)
{
	int i;
	int c = 0;

	for (i = bigint_precision - 1; i >= 0; i--) {
		r[i] = a[i] + b[i] + c - '0';
		if (r[i] > '9') {
			r[i] -= 10;
			c = 1;
		} else c = 0;
	}
}

/**
 * r = a - b
 */
void bigint_sub(char* r, const char *a, const char *b)
{
	int i;
	int c = 0;

	for (i = bigint_precision - 1; i >= 0; i--) {
		r[i] = a[i] - b[i] - c + '0';
		if (r[i] < '0') {
			r[i] += 10;
			c = 1;
		} else c = 0;
	}
}


const char* bigint_noLeadingZeros(const char* aInput)
{
	while (*aInput == '0') aInput++;

	return *aInput ? aInput : aInput - 1;
}


char gTotal[MAX_LENGTH + 1];
char gDifference[MAX_LENGTH + 1];
char gRegister[MAX_LENGTH + 1];

char gKlaudia[MAX_LENGTH + 1];
char gNatalia[MAX_LENGTH + 1];

int main()
{
	static char input[MAX_LENGTH + 1];
	int i;

	for (i = 0; i < 10; i++) {
		scanf("%s", input);
		bigint_assign(gTotal, input);
		scanf("%s", input);
		bigint_assign(gDifference, input);

		bigint_add(gRegister, gTotal, gDifference);
		bigint_div2(gKlaudia, gRegister);
		bigint_sub(gNatalia, gKlaudia, gDifference);

		puts(bigint_noLeadingZeros(gKlaudia));
		puts(bigint_noLeadingZeros(gNatalia));
	}
	return 0;
}
