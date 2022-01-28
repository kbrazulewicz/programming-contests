#include <algorithm>
#include <climits>
#include <cstdio>
using namespace std;

#include <message.h>
#include "poszukiwania.h"

#undef DEBUG

#define EVEN(X) (X % 2 == 0)
#define ODD(X) (X % 2 != 0)

#define FOR(E, I) for(auto E = I.begin(); E != I.end(); E++)

const int MAX_KMP_PREFIX_LEN = 20000000;
int kmpPrefix[MAX_KMP_PREFIX_LEN];


int searchKMP(int nodeId, int numberOfNodes)
{
	int signalLength = SignalLength();
	int seqLength = SeqLength();

	// KMP prefix
	{
		int pos = 2;
		int cnd = 0;

		kmpPrefix[0] = -1;
		kmpPrefix[1] = 0;
		while (pos < signalLength && pos < MAX_KMP_PREFIX_LEN)
		{
			if (SignalAt(pos) == SignalAt(cnd + 1))
			{
				kmpPrefix[pos++] = ++cnd;
			}
			else if (cnd > 0)
			{
				cnd = kmpPrefix[cnd];
			}
			else
			{
				kmpPrefix[pos++] = 0;
			}
		}
#ifdef DEBUG
		if (nodeId == 0)
		{
			for (int i = 0; i < signalLength && i < MAX_KMP_PREFIX_LEN; i++)
			{
				printf("kmpPrefix[%d] = %d\n", i, kmpPrefix[i]);
			}
		}
#endif
	}

	// KMP search
	int numberOfMatches = 0;
	int mBeg = ((long) nodeId * (seqLength - signalLength)) / numberOfNodes;
	int mEnd = ((long) (nodeId + 1) * (seqLength - signalLength)) / numberOfNodes;

#ifdef DEBUG
	printf("Node %d, [%d, %d]\n", nodeId, mBeg + 1, mEnd + 1);
#endif

	for (int i = 0, m = mBeg; m < mEnd;)
	{
		if (SignalAt(i + 1) == SeqAt(m + i + 1) && i < signalLength - 1)
		{
#ifdef DEBUG
			printf("Node %d, signal[%d] == seq[%d]\n", nodeId, i + 1, m + i + 1);
#endif
			i++;
		}
		else
		{
			if (i == signalLength - 1)
			{
				numberOfMatches++;
#ifdef DEBUG
				printf("Node %d, match at position %d\n", nodeId, m + 1);
#endif
			}

			i = min(i, MAX_KMP_PREFIX_LEN);

			if (kmpPrefix[i] > -1)
			{
				m = m + i - kmpPrefix[i];
				i = kmpPrefix[i];
			}
			else
			{
				i = 0;
				m++;
			}
		}
	}

	return numberOfMatches;
}


int searchNaive(int nodeId, int numberOfNodes)
{
	int signalLength = SignalLength();
	int seqLength = SeqLength();
	
	int numberOfMatches = 0;

	for (int m = 1 + nodeId; m <= 1 + seqLength - signalLength; m += numberOfNodes)
	{
		for (int s = 1; s <= signalLength; s++)
		{
			if (SeqAt(m + s - 1) != SignalAt(s)) break;
			if (s == signalLength) 
			{
				numberOfMatches++;
#ifdef DEBUG
				printf("node %d match at position %d\n", nodeId, m);
#endif
			}
		}
	}

	return numberOfMatches;
}


int main()
{
	int nodeId = MyNodeId();
	int numberOfNodes = NumberOfNodes();

	int numberOfMatches = searchKMP(nodeId, numberOfNodes);
	if (nodeId != 0)
	{
		PutLL(0, numberOfMatches);
		Send(0);
	}
	else
	{
		for (int i = 1; i < numberOfNodes; i++)
		{
			int senderNodeId = Receive(-1);
			numberOfMatches += GetLL(senderNodeId);
		}

		printf("%d\n", numberOfMatches);
	}

	return 0;
}
