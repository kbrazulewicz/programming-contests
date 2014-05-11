/* @JUDGE_ID: 16232QS 1196 C++ */

#include <cstdio>
#include <set>
using namespace std;

int main()
{
	int n, m;

	set<int> professorsList;

	scanf("%d", &n);
	for(int i = 0, x; i < n; i++) {
		scanf("%d", &x);
		professorsList.insert(x);
	}


	int result = 0;

	scanf("%d", &m);
	for(int i = 0, x; i < m; i++) {
		scanf("%d", &x);
		result += professorsList.count(x);
	}

	printf("%d\n", result);

	return 0;
}
