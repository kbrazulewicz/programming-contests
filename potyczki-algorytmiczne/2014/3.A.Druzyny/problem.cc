#include <cstdio>
#include <map>
using namespace std;

#undef DEBUG

struct preferences_t
{
	int c, d;
};

struct state_t
{
	int c, d;

	int backtrack;
	int teamSize;
	int teamCount;

	bool visited;
};

const int MAX_N = 1e6;

preferences_t prefs[MAX_N];

state_t tree[MAX_N];

int main()
{
	int n;

	scanf("%d", &n);
	for(int i = 0; i < n; scanf("%d%d", &prefs[i].c, &prefs[i].d), i++);

	map<int, long long> results;
	int t = 0;
	tree[0].c = prefs[0].c;
	tree[0].d = prefs[0].d;
	tree[0].backtrack = -1;
	tree[0].teamSize = 1;
	tree[0].teamCount = 1;
	tree[0].visited = false;

	do 
	{
		if (tree[t].teamSize > tree[t].d || tree[t].c > tree[t].d)
		{
			t = tree[t].backtrack;
			continue;
		}

#ifdef DEBUG_DEBUG
		printf("tree[%d]: c [%d], d [%d], backtrack [%d], teamSize [%d], teamCount [%d], visited [%c]\n",
			   t, tree[t].c, tree[t].d, tree[t].backtrack, tree[t].teamSize, tree[t].teamCount, tree[t].visited ? 'Y' : 'N');
#endif

		bool hasMultipleOptions = !tree[t].visited && tree[t].teamSize >= tree[t].c && tree[t].teamSize < tree[t].d;

		if (!tree[t].visited && tree[t].teamSize >= tree[t].c)
		{
			tree[t].visited = true;
#ifdef DEBUG_DEBUG
			printf("tree[%d]: TEAM ASSEMBLED [%d]\n", t, tree[t].teamCount);
#endif
			// team can be assembled now
			if (t + 1 < n)
			{
				// and we still have some students to go
				t++;
				tree[t].c = prefs[t].c;
				tree[t].d = prefs[t].d;
				tree[t].backtrack = hasMultipleOptions ? t - 1 : tree[t - 1].backtrack;
				tree[t].teamSize = 1;
				tree[t].teamCount = tree[t - 1].teamCount + 1;
				tree[t].visited = false;
			}
			else
			{
				// no more students
#ifdef DEBUG_DEBUG
				printf("tree[%d]: SOLUTION [%d]\n", t, tree[t].teamCount);
#endif
				results[tree[t].teamCount]++;
#ifdef DEBUG
				printf("tree[%d]: BACKTRACKING TO [%d]\n", t, tree[t].backtrack);
#endif
				t = tree[t].backtrack;
			}
		}
		else
		{
			// team is too small
			if (t + 1 < n)
			{
				// but we still have some students to go
				t++;
				tree[t].c = max(tree[t - 1].c, prefs[t].c);
				tree[t].d = min(tree[t - 1].d, prefs[t].d);
				tree[t].backtrack = hasMultipleOptions ? t - 1 : tree[t - 1].backtrack;
				tree[t].teamSize = tree[t - 1].teamSize + 1;
				tree[t].teamCount = tree[t - 1].teamCount;
				tree[t].visited = false;
			}
			else
			{
				// no more students
#ifdef DEBUG
				printf("tree[%d]: BACKTRACKING TO [%d]\n", t, tree[t].backtrack);
#endif
				t = tree[t].backtrack;
			}
		}
	} while (t >= 0);

	if (results.empty())
	{
		puts("NIE");
	}
	else
	{
		long long modulo = 1e9 + 7;
		printf("%d %d\n", results.rbegin()->first, results.rbegin()->second % modulo);
	}

	return 0;
}
