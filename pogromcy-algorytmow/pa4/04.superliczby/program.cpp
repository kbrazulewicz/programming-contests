#include <cstdio>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <queue>
#include <vector>

#define N_MAX (100000 + 1)
typedef std::set<int, std::greater<int> > level_t;

// levels[x]   = all nodes on level x
level_t levels[N_MAX];
// levelMin[x] = minimal node number on level x
int levelMin[N_MAX];

// parents[k] = parents of k-node
level_t parents[N_MAX];
// visited[k] = k-node visited
bool visited[N_MAX];

int superNumbers[N_MAX];
int superNumbersOffset;

char outputBuffer[N_MAX * 7];
char inputBuffer[N_MAX * 7];


using namespace std;

int qSortIntComparator(const void* a, const void* b)
{
	return *((const int*)a) - *((const int*)b);
}

int main()
{
	int permutationLength;
	int element;
	int level;
	int maxLevel = 0;
	char* buffer = inputBuffer;

	scanf("%d\n", &permutationLength);
	gets(inputBuffer);
	
	for (int i = 0; i < permutationLength; i++) {
		element = strtol(buffer, &buffer, 10);
		for (level = maxLevel; level > 0; level--) {
			if (levelMin[level] < element) {
				level_t::iterator it = levels[level].upper_bound(element);
				level_t::iterator itE = levels[level].end();
					while (it != itE) {
						parents[element].insert(*it);
						it++;
					}
					levels[level + 1].insert(element);
					levelMin[level + 1] = levelMin[level + 1] ? min(levelMin[level + 1], element) : element;
					maxLevel = max(maxLevel, level + 1);
					break;
			}
		}
		if (!level) {
			levels[1].insert(element);
			levelMin[1] = levelMin[1] ? min(levelMin[1], element) : element;
			maxLevel = max(maxLevel, 1);
		}
	}

	{
		queue<int> bfs;
		const level_t& level = levels[maxLevel];
		level_t::const_iterator it  = level.begin();
		level_t::const_iterator itE = level.end();
		for (; it != itE; it++) {
			if (!visited[*it]) {
				bfs.push(*it);
				visited[*it] = true;
			}
		}

		while (!bfs.empty()) {
			int nodeId = bfs.front(); bfs.pop();
			superNumbers[superNumbersOffset++] = nodeId;
			level_t::const_iterator it  = parents[nodeId].begin();
			level_t::const_iterator itE = parents[nodeId].end();
			for (; it != itE; it++) {
				if (!visited[*it]) {
					bfs.push(*it);
					visited[*it] = true;
				}
			}
		}
	}

	qsort(superNumbers, superNumbersOffset, sizeof(int), qSortIntComparator);
	buffer = outputBuffer;
	buffer += sprintf(buffer, "%d\n", superNumbersOffset);
	for (int i = 0; i < superNumbersOffset; i++) {
		buffer += sprintf(buffer, "%d ", superNumbers[i]);
	}
	*(--buffer) = 0;

	puts(outputBuffer);
	
	return 0;
}
