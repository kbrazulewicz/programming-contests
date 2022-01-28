#include <climits>
#include <cstdio>
#include <cstdlib>
#include <list>
#include <map>
using namespace std;

#undef DEBUG

#define EVEN(X) (X % 2 == 0)
#define ODD(X) (X % 2 != 0)

#define FOR(E, I) for(auto E = I.begin(); E != I.end(); E++)
#define RFOR(E, I) for(auto E = I.rbegin(); E != I.rend(); E++)

/**
 * Greatest Common Divisor Euclidean algorithm
 *
 * O(n) complexity (n is the number of digits in the input)
 *
 * needs:
 * #include <cstdlib>
 */
template<typename T> T greatestCommonDivisor(T a, T b)
{
	T tmp;
	while (b != 0) {
		tmp = a % b;
		a = b;
		b = tmp;
	}

	return abs(a);
}


/** 
 * Least Common Multiple algorithm
 */
template<typename T> T leastCommonMultiple(T a, T b)
{
	T gcd = greatestCommonDivisor(a, b);
	return (a / gcd) * b;
}


const int MAX_N = 1e6;
const int MAX_M = 1e6;

typedef struct Game;

typedef struct Player
{
	int money;
	int index;

	Game* firstGame;
} Player;


typedef struct Game
{
	Game* next;

	int score, cycleScore;
	int maxLossInACycle;
	bool visited;
} Game;

typedef struct Cycle
{
	list<Game*> games;
	int score = 0;
} Cycle;

Player players[MAX_N];
Game games[MAX_M];
list<Cycle> cycles;


void clearVisitedGames(int m)
{
	for (Game* g = games; g !=  games + m; (g++)->visited = false);
}

void connectGames(int n, int m)
{
	for (int i = 0; i < m; i++)
	{
		games[i].next = games + (i + n) % m;
#ifdef DEBUG
		printf("game %d next %d\n", i, (i + n) % m); 
#endif
	}
}

void connectPlayers(int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		players[i].firstGame = games + i  % m;
	}
}

void classifyGames(int m)
{
	clearVisitedGames(m);

	for (Game* g0 = games; g0 !=  games + m; g0++)
	{
		if (g0->visited) continue;

		Cycle cycle;
		Game* g = g0;
		while (true)
		{
			g->visited = true;

			cycle.games.push_back(g);
			cycle.score += g->score;

#ifdef DEBUG
			printf("game score %d, cycle score %d\n", g->score, cycle.score);
#endif

			if (g->next == g0) break;
			g = g->next;
		}

		FOR(g, cycle.games)
		{
			(*g)->cycleScore = cycle.score;
		}

		{
			int score = 0, minScore = 0;
			FOR(g, cycle.games)
			{
				score += (*g)->score;
				minScore = min(minScore, score);

				(*g)->maxLossInACycle = max(score - minScore - cycle.score, 0);
#ifdef DEBUG
				printf("F score %d, minScore %d, maxLossInACycle %d\n", score, minScore, (*g)->maxLossInACycle);
#endif
			}
		}
		{
			int score = 0, minScore = 0;
			RFOR(g, cycle.games)
			{
				score -= (*g)->score;
				minScore = min(minScore, score);

				(*g)->maxLossInACycle = max((*g)->maxLossInACycle, max(score - minScore, 0));
#ifdef DEBUG
				printf("B score %d, minScore %d, maxLossInACycle %d\n", score, minScore, (*g)->maxLossInACycle);
#endif
			}
		}

		cycles.push_back(cycle);
	}
}

int main()
{
	int n, m;

	// input data
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &players[i].money);
		players[i].index = i;
	}
	scanf("%d\n", &m);
	for (int i = 0; i < m; i++)
	{
		games[i].score = fgetc(stdin) == 'W' ? 1 : -1;
	}

	int cycleLength = leastCommonMultiple(n, m) / n;

	connectGames(n, m);
	connectPlayers(n, m);
	classifyGames(m);

#ifdef DEBUG
	FOR(c, cycles)
	{
		printf("Cycle score %d\n", c->score);
		FOR(g, c->games)
		{
			printf("game maxLossInACycle %d\n", (*g)->maxLossInACycle);
		}
	}
#endif

	// key is the number of cycles that are safe for the player
	multimap<int, Player*> candidates;
	for (Player* p = players; p !=  players + n; p++)
	{
		Game* g = p->firstGame;
		if (p->money <= g->maxLossInACycle)
		{
#ifdef DEBUG
			printf("candidate player %d, cycles %d\n", p->index, 0);
#endif
			candidates.insert(pair<int, Player*>(0, p));
		}
		else if (g->cycleScore < 0)
		{
			int moneyToLose = p->money - g->maxLossInACycle;
			int safeCycles = moneyToLose / abs(g->cycleScore) + (moneyToLose % abs(g->cycleScore) != 0 ? 1 : 0);
#ifdef DEBUG
			printf("candidate player %d, cycles %d\n", p->index, safeCycles);
#endif
			candidates.insert(pair<int, Player*>(safeCycles, p));
		}
	}
	
	if (!candidates.empty())
	{
		int minNumberOfSafeCycles = candidates.begin()->first;
		auto range = candidates.equal_range(minNumberOfSafeCycles);

		list<unsigned long long> result;

		for (auto c = range.first; c != range.second; c++)
		{
			Player* p = c->second;
			Game* g = p->firstGame;
			int money = p->money + minNumberOfSafeCycles * g->cycleScore;

			unsigned long long roundsPassed = minNumberOfSafeCycles * cycleLength * n;
#ifdef DEBUG
			printf("Checking candidate %d, safe cycles %d, rounds passed %d, money left %d\n", 
					p->index, minNumberOfSafeCycles, roundsPassed, money);
#endif

			while (money > 0)
			{
				money += g->score;

				if (money > 0)
				{
					roundsPassed += n;
					g = g->next;
				}
			}

			result.push_back(roundsPassed + p->index + 1);
		}

		result.sort();
		printf("%llu\n", result.front());
	}
	else
	{
		puts("-1");
	}

	return 0;
}
