#include <stdio.h>

#define MAX_WORD_LENGTH 200
const char gConvNormal[]	= "abcdefghijklmnopqrstuvwxyz";
const char gConvJas[]		= "abcbefghiiklmnobqrstuvwxyz";

int findPalindrom(const char aInput[], const char aConvTable[])
{
	int i = 0;
	int found = 0;

	while (!found && aInput[i]) {
		if (i > 1 && aConvTable[aInput[i] - 'a'] == aConvTable[aInput[i - 2] - 'a']) {
			found = 1;
		} else if (i > 0 && aConvTable[aInput[i] - 'a'] == aConvTable[aInput[i - 1] - 'a']) {
			found = 1;
		}
		i++;
	}

	return found;
}


int main()
{
	static char inWord[MAX_WORD_LENGTH + 2 + 1];
	int n, resultNormal = 0, resultJas = 0;

	scanf("%d", &n);

	do {
		fgets(inWord, sizeof(inWord), stdin);
		if (findPalindrom(inWord, gConvNormal)) 
			resultNormal++;
		if (findPalindrom(inWord, gConvJas)) 
			resultJas++;
	} while (n--);

	printf("%d\n%d\n", resultNormal, resultJas);
	return 0;
}
