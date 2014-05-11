#include <stdio.h>

#define MAX_N 1000000

char input[MAX_N + 1];
char output[2 * (MAX_N + 1)];
char *outputPtr = output;

int main()
{
	int n;

	fgets(input, sizeof(input), stdin);
	n = atoi(input);

	fgets(input, sizeof(input), stdin);
	input[n] = 0;

#ifndef NO_OUTPUT
	printf("%*s=", n, input);
#endif

	char *wordStart   = input;
	char *wordEnd     = wordStart + 1;
	char *currPtr     = wordStart;
	char *compareTo   = wordStart;

	int loopCounter = 0;
	*(outputPtr++) = *currPtr;
	do {
		loopCounter++;
		currPtr++;

		if (*currPtr > *compareTo) {
			do {
				*(outputPtr++) = *(wordEnd++);
			} while (wordEnd <= currPtr);

			compareTo = wordStart;
		} else if (*currPtr < *compareTo) {
			*(outputPtr++) = '+';

			int wordLength = wordEnd - wordStart;
			int wordCount  = (currPtr - wordEnd) / wordLength;
			int i;

			for (i = 0; i < wordCount; i++) {
				char* wordPtr = wordStart;
				for (wordPtr = wordStart; wordPtr < wordEnd; *(outputPtr++) = *(wordPtr++));
				*(outputPtr++) = '+';
			}
			
			wordStart  += (wordCount + 1) * wordLength;
			wordEnd     = wordStart + 1;
			currPtr     = wordStart;
			compareTo   = wordStart;

			*(outputPtr++) = *currPtr;
		} else {
			if (wordEnd == (wordStart + 1) && *currPtr > *wordStart) {
				wordEnd = currPtr + 1;
			}
			compareTo++;
		}
	} while (*currPtr);

	*(outputPtr - 2) = 0;
#ifndef NO_OUTPUT
	puts(output);
#endif

#ifdef _DEBUG
	printf("completed after [%d] iterations\n", loopCounter);
#endif

	return 0;
}
