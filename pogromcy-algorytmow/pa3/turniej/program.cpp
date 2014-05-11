#include <stdio.h>
#include <set>

using namespace std;

set<int> queue;
int matchesLost[100001];
set<int> matchesWon[100001];

int main()
{
	int playerNumber, matchNumber;
	int looser, winner;

	scanf("%d %d", &playerNumber, &matchNumber);
	memset(matchesLost, 0, (matchNumber + 1) * sizeof(matchesLost[0]));

	for (int i = 0; i < matchNumber; i++) {
		scanf("%d %d", &winner, &looser);
		matchesLost[looser]++;
		matchesWon[winner].insert(looser);
	}

	for (int i = 1; i <= playerNumber; i++) {
		if (!matchesLost[i]) queue.insert(i);
	}


	int player;

	while (playerNumber) {
		player = *(queue.begin());
		printf("%d\n", player);
		playerNumber--;

		queue.erase(queue.begin());

		set<int>::iterator wonIt = matchesWon[player].begin();
		while (wonIt != matchesWon[player].end()) {
			matchesLost[*wonIt]--;
			if (!matchesLost[*wonIt]) queue.insert(*wonIt);
			wonIt++;
		}
	}

	return 0;
}
