#include <stdio.h>
#include <string.h>

#define MAX_D 200000
#define MAX_LENGTH 15
#define MAX_PRINTABLE_LENGTH 10

#define MAX_FIELD_LEN 4
#define MAX_FIELD_VAL ((int)1e4)
#define MAX_FIELD_NUM 5

double dPowerOf10[20] = {
	1e0,  1e1,  1e2,  1e3,  1e4,  1e5,  1e6,  1e7,  1e8,  1e9,
	1e10, 1e11, 1e12, 1e13, 1e14, 1e15, 1e16, 1e17, 1e18, 1e19,
};

typedef struct {
	unsigned int parents[MAX_FIELD_NUM];
	unsigned int children[MAX_FIELD_NUM];
	unsigned int offset;
} GenerationData;

GenerationData gPopulation[MAX_D + 1];
int gPopulationLastCalculated;

void calcPopulation(int aGeneration)
{
	for (int i = gPopulationLastCalculated + 1; i <= aGeneration; i++) {
		int a = 0, cC = 0, cP = 0;
		for (int j = 0; j < MAX_FIELD_NUM; j++) {
			a = 4 * gPopulation[i - 1].children[j] - gPopulation[i - 1].parents[j] + cC;
			gPopulation[i].children[j] = (a >= 0) ? a % MAX_FIELD_VAL : MAX_FIELD_VAL + a;
			cC = (a >= 0) ? (a / MAX_FIELD_VAL) : -1;
			gPopulation[i].parents[j]  = gPopulation[i - 1].children[j];

#if 0
			printf("C[%d][%d] [%d]\n", i, j, gPopulation[i].children[j]);
			printf("P[%d][%d] [%d]\n", i, j, gPopulation[i].parents[j]);
			printf("a[%d] [%d]; c[%d] [%d]\n", j, a, j, cC);
#endif
		}
		gPopulation[i].offset   = gPopulation[i - 1].offset;
#if 0
			printf("C[%d][%d] [%d]\n", i, 4, gPopulation[i].children[4]);
			printf("P[%d][%d] [%d]\n", i, 4, gPopulation[i].parents[4]);
			printf("a[%d] [%d]; c[%d] [%d]\n", 4, a, 4, cC);
#endif


		if (cC) {
			for (int j = MAX_FIELD_NUM - 1; j >= 0; j--) {
				a = gPopulation[i].children[j] + MAX_FIELD_VAL * cC;
				gPopulation[i].children[j] = a / 10;
				cC = a % 10;

				a = gPopulation[i].parents[j] + MAX_FIELD_VAL * cP;
				gPopulation[i].parents[j] = a / 10;
				cP = a % 10;
			}
			gPopulation[i].offset++;
		}
	}
	gPopulationLastCalculated = aGeneration;
}


void printPopulation(int aGeneration)
{
	char buffer[MAX_FIELD_NUM * MAX_FIELD_LEN + 1];
	char *bufferPtr = buffer;

	for (int i = MAX_FIELD_NUM - 1; i >= 0; i--) {
		bufferPtr += sprintf(bufferPtr, "%0.*d", MAX_FIELD_LEN, gPopulation[aGeneration].children[i]);
	}

	bufferPtr = buffer;
	while (*bufferPtr == '0') bufferPtr++;

	int length = strlen(bufferPtr);
	printf("%d %.*s\n", gPopulation[aGeneration].offset + length, MAX_PRINTABLE_LENGTH, bufferPtr);
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
		printPopulation(d);
	}

	return 0;
}
