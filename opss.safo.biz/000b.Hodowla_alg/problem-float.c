#include <math.h>
#include <stdio.h>

#define MAX_D 200000
#define MAX_LENGTH 15
#define MAX_PRINTABLE_LENGTH 10

double dPowerOf10[20] = {
	1e0,  1e1,  1e2,  1e3,  1e4,  1e5,  1e6,  1e7,  1e8,  1e9,
	1e10, 1e11, 1e12, 1e13, 1e14, 1e15, 1e16, 1e17, 1e18, 1e19,
};

typedef struct {
	double val;
	unsigned int off;
} GenerationData;

GenerationData gPopulation[MAX_D + 1];
int gPopulationLastCalculated;

void calcPopulation(int aGeneration)
{
	for (int i = gPopulationLastCalculated + 1; i <= aGeneration; i++) {
		gPopulation[i].val = 4 * gPopulation[i - 1].val - 
			gPopulation[i - 2].val / dPowerOf10[gPopulation[i - 1].off - gPopulation[i - 2].off];
		gPopulation[i].off   = gPopulation[i - 1].off;

		double length = floor(log(gPopulation[i].val) / log(10));
		if (length > MAX_LENGTH) {
			gPopulation[i].val /= 10;
			gPopulation[i].off   += 1;
		}
	}
	gPopulationLastCalculated = aGeneration;
}

void printPopulation(int aGeneration)
{
	double value  = gPopulation[aGeneration].val;
	int length = (int) (log(value) / log(10)) + 1;

	if (length > MAX_PRINTABLE_LENGTH) {
		value /= dPowerOf10[length - MAX_PRINTABLE_LENGTH];
	}

	length += gPopulation[aGeneration].off;

	printf("%d %.0f\n", length, floor(value));
}

int main()
{
	int n, d;

	gPopulation[0].val =  1;
	gPopulation[0].off   =  0;
	gPopulation[1].val =  3;
	gPopulation[1].off   =  0;
	gPopulation[2].val = 11;
	gPopulation[2].off   =  0;
	gPopulationLastCalculated = 2;

	scanf("%d", &n);
	while (n--) {
		scanf("%d", &d);
		calcPopulation(d);
		printPopulation(d);
	}

	return 0;
}
