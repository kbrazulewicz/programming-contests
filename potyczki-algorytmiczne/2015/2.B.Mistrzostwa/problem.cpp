#include <cstdio>
#include <deque>
#include <list>
#include <set>
using namespace std;

#undef DEBUG

#define FOR(E, I) for(auto E = I.begin(); E != I.end(); E++)

const int MAX_N = 200000;
const int MAX_M = 200000;

struct City;

typedef struct City 
{
	int printableIndex;
	bool visited;
	set<City*> connections;
};

City city[MAX_N];


bool sortListOfIntegerDesc(const list<int>& first, const list<int>& second)
{
	return first.size() > second.size();
}

int main()
{
	int n, m, d;

	scanf("%d%d%d", &n, &m, &d);

	for (int i = 0; i < m; i++)
	{
		int a, b;

		scanf("%d%d", &a, &b);
		city[a - 1].connections.insert(city + b - 1);
		city[b - 1].connections.insert(city + a - 1);
	}

	set<City*> candidates;
	deque<City*> q;
	for (int i = 0; i < n; i++)
	{
		city[i].printableIndex = i + 1;
		candidates.insert(candidates.end(), city + i);
		q.push_back(city + i);
	}

	while (!q.empty())
	{
		City* candidate = q.front();
		if (candidate->connections.size() < d)
		{
			FOR(c, candidate->connections)
			{
				(*c)->connections.erase(candidate);
				if ((*c)->connections.size() < d)
				{
					q.push_back(*c);
				}
			}
			candidate->connections.clear();
			candidates.erase(candidate);
		}
		q.pop_front();
	}

#ifdef DEBUG
	printf("Candidate filtering completed, cities left: %d\n", candidates.size());
#endif

	list<list<int>> groups;

	FOR(i, candidates)
	{
		City* firstCity = *i;
		if (firstCity->visited) break;

		firstCity->visited = true;
		q.push_back(firstCity);

		list<int> group;

		while(!q.empty())
		{
			City* city = q.front();
			FOR(c, city->connections)
			{
				if (!(*c)->visited)
				{
					(*c)->visited = true;
					q.push_back(*c);
				}
			}
			group.push_back(city->printableIndex);
			q.pop_front();
		}

		groups.push_back(group);

#ifdef DEBUG
		printf("Group #%d : %d cities\n", groups.size(), group.size());
#endif
	}

	groups.sort(sortListOfIntegerDesc);

	if (!groups.empty())
	{
		list<int> largestGroup = groups.front();
		largestGroup.sort();

		printf("%d\n", largestGroup.size());
		FOR(c, largestGroup)
		{
			printf("%d ", *c);
		}
		printf("\n");
	}
	else
	{
		puts("NIE");
	}


	return 0;
}
