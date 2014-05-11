//
// Krystian Brazulewicz
// krystian.brazulewicz@iq.pl
//
#include <iostream.h>
#include <string.h>

#define __DEBUG_NOT


const static unsigned int MAX_COMPETITORS = 1000;

// ~2MB
// winners[a] - list of competitors who win against a
unsigned short winners[MAX_COMPETITORS][MAX_COMPETITORS];
unsigned short winnersCnt[MAX_COMPETITORS];
unsigned short winnersAct[MAX_COMPETITORS];
// ~2MB
// loosers[a] - list of competitors who loose against a
unsigned short loosers[MAX_COMPETITORS][MAX_COMPETITORS];
unsigned short loosersCnt[MAX_COMPETITORS];
unsigned short loosersAct[MAX_COMPETITORS];

unsigned short vertexQueue[MAX_COMPETITORS];
unsigned short *vertexQueuePtr = vertexQueue;

char visited[MAX_COMPETITORS];



int main() 
{
	unsigned int numberOfCompetitors;
	unsigned int competitor;
	unsigned int i, j;

	// initialization
	memset(winnersCnt, 0, sizeof(winnersCnt));
	memset(winnersAct, 0, sizeof(winnersAct));
	memset(loosersCnt, 0, sizeof(loosersCnt));
	memset(loosersAct, 0, sizeof(loosersAct));
	memset(visited, 0, sizeof(visited));


	// read in all data
	cin >> numberOfCompetitors;	
	for (i = 0; i < numberOfCompetitors; i++) {
		cin >> j;
		while (j) {
			// competitor wins with i
			cin >> competitor;
			competitor--;
			loosers[competitor][loosersCnt[competitor]++] = i;
			winners[i][winnersCnt[i]++] = competitor;
			j--;
		}
	}

	

	// process data
	unsigned short currentVertex;
	unsigned short nextWinner, nextLooser;
	int loopVertex		= -1;
	int suspectedVertex = -1;

	*vertexQueuePtr = 0;
	vertexQueuePtr++;

#ifdef __DEBUG
		cout << "Starting vertex: " << 1 << endl;
#endif


	while (suspectedVertex == -1) {
		currentVertex = *(vertexQueuePtr - 1);
		visited[currentVertex] = 1;

#ifdef __DEBUG
		cout << "Current vertex: " << (currentVertex + 1) << endl;
#endif
	
		// was it the last link to winner ?
		if (winnersAct[currentVertex] == winnersCnt[currentVertex]) {
			// not looped
			if (loopVertex == -1) {
#ifdef __DEBUG
				cout << "Not looped: " << currentVertex + 1 << endl;
#endif
				suspectedVertex = currentVertex;
			}
			// looped
			else {
				// got back where I was looped
				if (currentVertex == loopVertex) {
#ifdef __DEBUG
					cout << "Looped: " << currentVertex + 1 << endl;
#endif
					suspectedVertex = currentVertex;
				}
				// go back
				else {
					visited[currentVertex] = 0;
					vertexQueuePtr--;
				}
			}
		}
		// another winner on the list
		else {
			nextWinner = winners[currentVertex][winnersAct[currentVertex]++];

			if (!visited[nextWinner]) {
				*(vertexQueuePtr++) = nextWinner;
				// rewind winners table
				winnersAct[nextWinner] = 0;
				loopVertex = -1;
			}
			else {
				loopVertex = nextWinner;
#ifdef __DEBUG
				cout << "Looping at: " << loopVertex + 1 << endl;
#endif
			}
		}
	}

#ifdef __DEBUG
	cout << "Suspected vertex: " << suspectedVertex + 1 << endl;
#endif

	unsigned short potentialWinners = 0;
	unsigned short vertexCoverage = 0;

	// check if DSF starting from suspectedVertex and going in 'loosing' direction will cover all vertexes

	// queue reinitialization
	vertexQueuePtr = vertexQueue;
	*vertexQueuePtr = suspectedVertex;
	vertexQueuePtr++;

	// clean all visited	
	memset(visited, 0, sizeof(visited));
	memset(loosersAct, 0, sizeof(loosersAct));
	visited[suspectedVertex] = 1;



	while (vertexQueuePtr != vertexQueue) {
		currentVertex = *(vertexQueuePtr - 1);
		visited[currentVertex] = 1;

		// was it the last link to winner ?
		if (loosersAct[currentVertex] == loosersCnt[currentVertex]) {
			vertexQueuePtr--;
		}

		// another winner on the list
		else {
			nextLooser = loosers[currentVertex][loosersAct[currentVertex]++];

			if (!visited[nextLooser]) {
				*(vertexQueuePtr++) = nextLooser;
				// rewind winners table
				loosersAct[nextLooser] = 0;
			}
		}
	}

	for (i = 0; i < numberOfCompetitors; vertexCoverage += visited[i++]);

	// OK - hypothetical winner seems to be pretty real
	if (vertexCoverage == numberOfCompetitors) {

		// DSF starting from suspectedVertex and going in 'winning' direction 
		// will cover all vertexes capable of winning the tournament

		// queue reinitialization
		vertexQueuePtr = vertexQueue;
		*vertexQueuePtr = suspectedVertex;
		vertexQueuePtr++;

		// clean all visited	
		memset(visited, 0, sizeof(visited));
		memset(winnersAct, 0, sizeof(winnersAct));
		visited[suspectedVertex] = 1;

		while (vertexQueuePtr != vertexQueue) {
			currentVertex = *(vertexQueuePtr - 1);
			visited[currentVertex] = 1;

			// was it the last link to winner ?
			if (winnersAct[currentVertex] == winnersCnt[currentVertex]) {
				vertexQueuePtr--;
			}

			// another winner on the list
			else {
				nextWinner = winners[currentVertex][winnersAct[currentVertex]++];

				if (!visited[nextWinner]) {
					*(vertexQueuePtr++) = nextWinner;
				}
			}
		}

		// print number of potential winners
		for (i = 0; i < numberOfCompetitors; potentialWinners += visited[i++]);
	}

	cout << potentialWinners << endl;

	return 0;
}
