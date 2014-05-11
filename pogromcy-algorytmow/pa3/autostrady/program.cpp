#include <stdio.h>
#include <string.h>
#include <map>
#include <set>

using namespace std;

multimap<int, int> cityConnections[100001];
multimap<int, int> queue;
char cityConnected[100001];

int main()
{
	int cityNumber, roadNumber;
	int from, to, cost;
	int maxCost = 0;

	scanf("%d %d", &cityNumber, &roadNumber);

	memset(cityConnected, 0, cityNumber + 1);

	for (int i = 0; i < roadNumber; i++) {
		scanf("%d %d %d", &from, &to, &cost);

		cityConnections[from].insert(pair<int, int>(cost, to));
		cityConnections[to].insert(pair<int, int>(cost, from));
	}


	int city = 1;
	queue.insert(pair<int, int>(0, city));

	while (cityNumber) {
		while (cityConnected[city]) {
			queue.erase(queue.begin());
			city = queue.begin()->second;
		}

		cityConnected[city] = 1;
		maxCost = max(maxCost, queue.begin()->first);

		if (--cityNumber) {
			queue.erase(queue.begin());
			queue.insert(cityConnections[city].begin(), cityConnections[city].end()); 

			city = queue.begin()->second;
		}
	}
	
	printf("%d\n", maxCost);
	return 0;
}
