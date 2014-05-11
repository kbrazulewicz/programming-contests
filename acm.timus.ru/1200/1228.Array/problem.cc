/* @JUDGE_ID: 16232QS 1228 C++ */

#include <iostream>
using namespace std;

int main()
{
	int n, s, d;

	scanf("%d%d", &n, &s);

	for (int i = 0; i < n; i++) {
		scanf("%d", &d);
		printf("%s%d", i > 0 ? " " : "", s / d - 1);
		s = d;
	}

	printf("\n");

	return 0;
}
