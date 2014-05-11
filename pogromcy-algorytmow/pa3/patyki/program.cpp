#include <stdio.h>
#include <set>
using namespace std;

int main()
{
	int totalStickNumber, stickNumber = 0;
	int stick;
	set<int> stickSet;
	set<int>::iterator stickSetPos;

	scanf("%d", &totalStickNumber);

	for (int i = 0; i < totalStickNumber; i++) {
		scanf("%d", &stick);
		stickNumber++;

		while ((stickSetPos = stickSet.find(stick)) != stickSet.end()) {
			stickSet.erase(stickSetPos);
			stickNumber--;
			stick *= 2;
		}
		stickSet.insert(stick);
	}

	printf("%d\n", stickNumber);
	return 0;
}
