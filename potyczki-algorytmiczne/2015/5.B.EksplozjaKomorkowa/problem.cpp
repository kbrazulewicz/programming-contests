#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
#include <list>
#include <set>
using namespace std;

#undef DEBUG

#define EVEN(X) (X % 2 == 0)
#define ODD(X) (X % 2 != 0)

#define FOR(E, I) for(auto E = I.begin(); E != I.end(); E++)

const int MAX_N = 500;
const int MAX_M = 1000;
const int MAX_L_SUM = 1000;

short hLen[MAX_N + 1];
short maxHLen = 0;
short s[MAX_M];

typedef struct Match
{
	short length;
	bool complete;
	int generation;
	list<short> h;

#ifdef DEBUG
	void debug()
	{
		printf("  generation %hd, match ", generation);
		FOR(hIter, h) printf("%hd ", *hIter);
		printf("\n");
	}
#endif
};

// hCandidate[<position>][<value>] == set of H(i) that matches
list<short> hCandidates[MAX_L_SUM + 1][MAX_N + 1];

void findMatches(
		list<short>& candidates, short offset, short matchLength, short sLength, 
		const Match& initialMatch, deque<Match>& matches)
{
	for (auto c = candidates.begin(); c != candidates.end();)
	{
#ifdef DEBUG_DEBUG
		printf("findMatches: candidate %hd, length %hd, offset %hd, matchLength %hd, initialMatch.length %hd, sLength %hd\n",
				*c, hLen[*c], offset, matchLength, initialMatch.length, sLength);

#endif
		if (matchLength + initialMatch.length == sLength || hLen[*c] == offset + matchLength)
		{
			Match m = initialMatch;
			m.length += matchLength;
			m.h.push_back(*c);
			if (matchLength + initialMatch.length == sLength)
			{
				m.complete = true;
			}

			matches.push_back(m);
			c = candidates.erase(c);
		}
		else c++;
	}
}

list<short> intersectCandidates(list<short> candidates1, list<short> candidates2)
{
	list<short> candidates_intersection;

	set_intersection(candidates1.begin(), candidates1.end(),
			candidates2.begin(), candidates2.end(), 
			back_inserter(candidates_intersection));

	return candidates_intersection;
}

void findNextCell(const Match& match, short s[], short sLength, short lOffset, deque<Match>& result)
{
	list<short> candidates;

	for (short si = match.length, matchLength = 1; si < sLength; si++, matchLength++)
	{
		if (matchLength == 1)
		{
			candidates = hCandidates[lOffset + matchLength][s[si]];
		}
		else
		{
			candidates = intersectCandidates(candidates, hCandidates[lOffset + matchLength][s[si]]);
		}
		findMatches(candidates, lOffset, matchLength, sLength, match, result);

#ifdef DEBUG_DEBUG
		printf("Candidates at offset == %hd, sequence %hd, matchLength %hd, results %d\n", 
				lOffset, s[si], matchLength, result.size());
		FOR(cIter, candidates)
		{
			printf("  candidate %hd\n", *cIter);
		}
#endif

		if (candidates.empty()) break;
	}
}


void findStartingCell(short s[], short sLength, deque<Match>& partialMatches)
{
	// iterate over all possible h lengths
	for (short l = 0; l < maxHLen; l++)
	{
		findNextCell(Match(), s, sLength, l, partialMatches);
	}
}


list<Match> findGeneratingSequences(short s[], short sLength)
{
#ifdef DEBUG
	printf("findGeneratingSequences: ");
	for (int is = 0; is < sLength; printf("%hd ", s[is++]));
	printf("\n");
#endif
	deque<Match> partialMatches;
	list<Match> completeMatches;

	findStartingCell(s, sLength, partialMatches);

	while (!partialMatches.empty())
	{
		Match match = partialMatches.front();
		if (match.complete)
		{
			completeMatches.push_back(match);
		}
		else
		{
			findNextCell(match, s, sLength, 0, partialMatches);
		}
		partialMatches.pop_front();
	}

	return completeMatches;
}

int findGeneration(short sOriginal[], short sOriginalLength)
{
	set<list<short>> sequenceHistory;
	deque<Match> sequences;
	short s[MAX_M];
	short sLength;

	if (sOriginalLength == 1 && sOriginal[0] == 1) return 1;

	Match initialSequence;
	initialSequence.generation = 1;
	copy(sOriginal, sOriginal + sOriginalLength, back_inserter(initialSequence.h));
	sequences.push_back(initialSequence);
	sequenceHistory.insert(initialSequence.h);

	while (!sequences.empty())
	{
		Match sequence = sequences.front();

		sLength = 0;
		FOR(hIter, sequence.h)
		{
			s[sLength++] = *hIter;
		}

		list<Match> generatingSequences = findGeneratingSequences(s, sLength);
		FOR(sIter, generatingSequences)
		{
			sIter->generation = sequence.generation + 1;

			if (sIter->h.size() == 1 && sIter->h.front() == 1)
				return sIter->generation;

			if (sequenceHistory.find(sIter->h) != sequenceHistory.end())
			{
#ifdef DEBUG
				printf("Duplicate ");
				sIter->debug();
#endif
			}
			else
			{
				sequences.push_back(*sIter);
				sequenceHistory.insert(sIter->h);
#ifdef DEBUG
				printf("Sequence ");
				sIter->debug();
#endif
			}
		}

		sequences.pop_front();
	}

	return -1;
}


int main()
{
	short n, m;

	scanf("%hd%hd", &n, &m);
	for (short i = 1; i <= n; i++)
	{
		scanf("%hd", hLen + i);
		maxHLen = max(maxHLen, hLen[i]);
		for (short l_i = 1; l_i <= hLen[i]; l_i++)
		{
			short h_il;
			scanf("%hd", &h_il);
			hCandidates[l_i][h_il].push_back(i);
		}
	}
	for (int i = 0; i < m; scanf("%hd", s + i++));

	for (int i = 0; i <= maxHLen; i++)
	{
		for (int j = 0; j <= n; n++)
		{
			hCandidates[i][j].sort();
		}
	}	

	printf("%d\n", findGeneration(s, m));

	return 0;
}
