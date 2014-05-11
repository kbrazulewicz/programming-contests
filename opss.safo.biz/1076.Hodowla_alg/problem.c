#include <math.h>
#include <stdio.h>
#include <string.h>

#define MAX_D 200000
#define MAX_PRINTABLE_LENGTH 10

#define MAX_FIELD_LEN 8
#define MAX_FIELD_VAL ((int)1e8)
#define MAX_FIELD_NUM 3

typedef struct {
	unsigned int parents[MAX_FIELD_NUM];
	unsigned int children[MAX_FIELD_NUM];
	unsigned int offset;

	unsigned char readyToPrint;
	char printableValue[6 + 1 + MAX_PRINTABLE_LENGTH + 1];
} GenerationData;

GenerationData gPopulation[MAX_D + 1];
int gPopulationLastCalculated;


char* sprintf_UnsignedInt(char* aBuffer, unsigned int aValue)
{
	if (aValue != 0) {
		int l = (log(aValue) / log(10)) + 1;

		for (int i = l - 1; i >= 0; i--) {
			aBuffer[i] = '0' + aValue % 10;
			aValue /= 10;
		}

		aBuffer += l;
	} else {
		*(aBuffer++) = '0';
	}


	return aBuffer;
}


void calcPopulation(int aGeneration)
{
	for (int i = gPopulationLastCalculated + 1; i <= aGeneration; i++) {
		int a = 0, cC = 0, cP = 0;
		GenerationData* currGen = gPopulation + i;
		GenerationData* prevGen = gPopulation + i - 1;
		for (int j = 0; j < MAX_FIELD_NUM; j++) {
			a = 4 * prevGen->children[j] - prevGen->parents[j] + cC;
			currGen->children[j] = (a >= 0) ? a % MAX_FIELD_VAL : MAX_FIELD_VAL + a;
			cC = (a >= 0) ? (a / MAX_FIELD_VAL) : -1;
			currGen->parents[j]  = prevGen->children[j];
		}
		currGen->offset   = prevGen->offset;

		if (cC) {
			for (int j = MAX_FIELD_NUM - 1; j >= 0; j--) {
				a = currGen->children[j] + MAX_FIELD_VAL * cC;
				currGen->children[j] = a / 10;
				cC = a % 10;

				a = currGen->parents[j] + MAX_FIELD_VAL * cP;
				currGen->parents[j] = a / 10;
				cP = a % 10;
			}
			currGen->offset++;
		}
	}
	if (aGeneration > gPopulationLastCalculated) {
		gPopulationLastCalculated = aGeneration;
	}

	GenerationData* generation = &gPopulation[aGeneration];

	if (generation->readyToPrint == 0) {
		char buffer[MAX_FIELD_NUM * MAX_FIELD_LEN + 1];
		char *bufferPtr = buffer + sizeof(buffer) - 1;

		*(bufferPtr--) = 0;
		for (int i = 0; i < MAX_FIELD_NUM; i++) {
			unsigned int a = generation->children[i];
			for (int j = 0; j < MAX_FIELD_LEN; j++) {
				*(bufferPtr--) = '0' + a % 10;
				a /= 10;
			}
		}

		bufferPtr = buffer;
		while (*bufferPtr == '0') bufferPtr++;

		int length = generation->offset + strlen(bufferPtr);
		char* x = sprintf_UnsignedInt(generation->printableValue, length);
		*(x++) = ' ';
		strncpy(x, bufferPtr, MAX_PRINTABLE_LENGTH);

		generation->readyToPrint = 1;
	}

	puts(generation->printableValue);
}


int main()
{
	int n, d;

	memset(gPopulation, 0, sizeof(gPopulation));
	
	gPopulation[0].children[0] =  1;
	gPopulation[1].children[0] =  3;
	gPopulation[1].parents[0]  =  1;
	gPopulation[2].children[0] = 11;
	gPopulation[2].parents[0]  =  3;
	gPopulationLastCalculated = 2;

	scanf("%d", &n);
	while (n--) {
		scanf("%d", &d);
		calcPopulation(d);
	}

	return 0;
}
