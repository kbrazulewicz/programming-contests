/* @JUDGE_ID: 16232QS 1048 C */

#include <stdio.h>


void printPart(int numberOfDigits, const char* digit) 
{
	int i;
	for (i = 0; i < numberOfDigits; i++) {
		printf(digit);
	}
}

int main()
{
	int numberLength;
	int digitA, digitB;
	int sum = 0, tmpSum = 0;
	int carryCounter = 0;
	int i;

	scanf("%d", &numberLength);

	for (i = 0; i <= numberLength; i++) {

		if (i != numberLength) {
			scanf("%d %d", &digitA, &digitB);
		} else {
			digitA = digitB = 0;
		}

		tmpSum = digitA + digitB;

		if (tmpSum == 9 && i != 0) {
			carryCounter++;
		} else {
			sum += tmpSum / 10;
			if (i != 0) {
				printf("%d", sum % 10);
			}

			printPart(carryCounter, tmpSum >= 10 ? "0" : "9");
			carryCounter = 0;

			sum = tmpSum % 10;
		}
	}

	return 0;
}
