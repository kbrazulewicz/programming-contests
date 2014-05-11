#include <cstdio>
#include <cstring>

#include <iostream>

using namespace std;

#define MAX_LENGTH 1000000

char inputBuffer[MAX_LENGTH + 1];
char* inputBufferPtr = inputBuffer;
char* inputBufferEnd = inputBuffer;
char outputBuffer[MAX_LENGTH * 16];
char* outputBufferPtr = outputBuffer;


void checkForOnlyR()
{
	char* firstS = strchr(inputBufferPtr, 'S');
	if (firstS == NULL) firstS = inputBufferEnd;

	int numR = firstS - inputBufferPtr;
	inputBufferPtr = firstS;

	numR %= 4;
	if (!numR) return;

	switch (numR) {
		case 1:
			outputBufferPtr += sprintf(outputBufferPtr, "RRR"); break;
		case 2:
			outputBufferPtr += sprintf(outputBufferPtr, "RR"); break;
		case 3:
			outputBufferPtr += sprintf(outputBufferPtr, "R"); break;
	}
}

void checkForOnlyS()
{
	char* firstR = strchr(inputBufferPtr, 'R');
	if (firstR == NULL) firstR = inputBufferEnd;

	int numS = firstR - inputBufferPtr;
	inputBufferPtr = firstR;

	if (!numS) return;

	outputBufferPtr += sprintf(outputBufferPtr, "RS");
	numS--;
	while (numS--) {
		outputBufferPtr += sprintf(outputBufferPtr, "RSS");
	}
}


bool discardNonMeaningfullBeginning()
{
	char* firstS = strchr(inputBufferPtr, 'S');

	// no 'S' at all :)
	if (firstS == NULL) return false;
	int numR = firstS - inputBufferPtr;

	// no 'R' at the beginning
	if (numR == 0) return false;

	if (numR % 1) {
		// odd - discard all 'R' from beginning and first series of 'S'
		char* firstR = strchr(firstS, 'R');
		inputBufferPtr = firstR != NULL ? firstR : inputBufferEnd;
	} else {
		// even - discard all 'R' from beginning
		inputBufferPtr = firstS;
	}
	return true;
}



bool discardNonMeaningfullEnd()
{
	char* lastS = strrchr(inputBufferPtr, 'S');

	if (lastS == NULL || !(*(lastS + 1))) return false;

	*(lastS + 1) = 0;
	return true;
}

bool discard4R()
{
	char *fourR = strstr(inputBufferPtr, "RRRR");

	if (fourR == NULL) return false;
	memcpy(fourR, fourR + 4, inputBufferEnd - inputBufferPtr - 4);
	inputBufferEnd -= 4;
	return true;
}



int main()
{
	int numMoves;

	scanf("%d\n", &numMoves);
	gets(inputBuffer);
	inputBufferEnd = inputBuffer + numMoves;

	while (discardNonMeaningfullBeginning());
	while (discard4R());

	while (inputBufferPtr != inputBufferEnd) {
		checkForOnlyS();
		checkForOnlyR();
	}

	puts(outputBuffer);
	cout << strlen(outputBuffer) << endl;

	return 0;
}
