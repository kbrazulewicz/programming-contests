//
// Krystian Brazulewicz 
// krystian.brazulewicz@iq.pl
// 
#include <iostream.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const static unsigned int NUM_RESTAURANT 		= 1000;
const static unsigned int NUM_ROAD				= 30000;
const static unsigned int NUM_CITY				= 10000;
const static unsigned int MAX_DISTANCE			= 1000;

unsigned int restaurant[NUM_CITY];


long int getRnd(long int maxVal) {
	double rnd = random();
	rnd /= RAND_MAX;
	rnd *= maxVal;

	return (long int) rnd;
}


int main ()
{
	unsigned int i;

	srandom(time(NULL));

	cout << NUM_CITY << " " << NUM_RESTAURANT << " " << NUM_ROAD << endl;

	for (i = 0; i < NUM_CITY; restaurant[i++] = 0);

	// generate restaurants	
	for (i = 0; i < NUM_RESTAURANT; i++) {
		int iRnd = getRnd(NUM_CITY);

		if (!restaurant[iRnd]) {
			restaurant[iRnd] = 1;
		}
		else {
			while (restaurant[iRnd]) {
				iRnd++;
				iRnd %= NUM_CITY;
			}
			restaurant[iRnd] = 1;
		}
	}

	// output restaurants
	for (i = 0; i < NUM_CITY; i++) {
		if (restaurant[i]) {
			cout << i << endl;
		}
	}

	// output roads
	for (i = 0; i < NUM_ROAD; i++) {
		cout << getRnd(NUM_CITY) << " " << getRnd(NUM_CITY) << " " << getRnd(MAX_DISTANCE) << endl;
	}


}
