//
// Krystian Brazulewicz 
// krystian.brazulewicz@iq.pl
// 
#include <iostream.h>
#include <string.h>

const static unsigned int MAX_RESTAURANT 		= 1000;
const static unsigned int MAX_ROAD				= 30000;
const static unsigned int MAX_CITY				= MAX_ROAD + 1;
const static unsigned int MAX_SINGLE_DISTANCE	= 1000;
const static unsigned int MAX_TOTAL_DISTANCE	= MAX_ROAD * MAX_SINGLE_DISTANCE;


struct road_t {
	unsigned int a; // from
	unsigned int b; // to
	unsigned int d; // distance

	unsigned int l; // next entry starting in a
};


unsigned int restaurant[MAX_RESTAURANT];
unsigned int distance[MAX_CITY + 1];
int connection[MAX_CITY];
int queued[MAX_CITY];
road_t road[MAX_ROAD * 2];

unsigned int queue[MAX_CITY * 2]; 
unsigned int *queuePtr = queue;



int main() 
{
	unsigned int numCity, numRestaurant, numRoad, i;
	
	// get 1st line
	cin >> numCity >> numRestaurant >> numRoad;
	
	// distance and connection initialization 
	// connection = -1
	// distance = very big value
	// queued = 0
	memset(connection + 1, 0xFF, numCity * sizeof(connection[0]));
	memset(distance + 1, 0xFF, numCity * sizeof(distance[0]));
	memset(queued + 1, 0x00, numCity * sizeof(queued[0]));

	// get restaurants
	for (i = 0; i < numRestaurant; i++) {
		cin >> restaurant[i];
		distance[restaurant[i]] = 0;
	}

	// get roads
	unsigned int a, b, d;
	for (i = 0; i < numRoad * 2; i+=2) {
		cin >> a >> b >> d;
	
		road[i + 1].b = road[i].a = a;
		road[i + 1].a = road[i].b = b;
		road[i + 1].d = road[i].d = d;
		
		road[i].l = connection[a];
		road[i + 1].l = connection[b];
		connection[a] = i;
		connection[b] = i + 1;
	}

	// now we're ready for the real shit -  graph traversing
	unsigned int *queueAct = queue;
	
	// copy restaurants to queue - traversing starts at restaurants.
	memcpy(queue, restaurant, numRestaurant * sizeof(queue[0]));
	queuePtr = queue + numRestaurant;

	unsigned int curDistance, tmpDistance, target;
	int link;

	while (queuePtr > queueAct) {
		link = connection[*queueAct];
		curDistance = distance[*queueAct];
		queued[*queueAct] = 0;

		// go through all cities starting in current city
		while (link >= 0) {
			target 		= road[link].b;
			tmpDistance = curDistance + road[link].d;
			link 		= road[link].l;

			if (distance[target] > tmpDistance) {
				distance[target] = tmpDistance;
				if (!queued[target]) {
					*(queuePtr++) = target;
					queued[target] = 1;
				}
			}
		}
		queueAct++;
	}

	// find max(min distance)
	unsigned int maxDistance = 0;
	for (i = 1; i < numCity + 1; i++) {
		if (maxDistance < distance[i]) maxDistance = distance[i];
	}

	// output - Hurraey ...
	cout << maxDistance << endl;
	
	return 0;
}
