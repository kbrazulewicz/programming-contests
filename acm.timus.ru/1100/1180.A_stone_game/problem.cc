/* @JUDGE_ID: 16232QS 1180 C++ */

#include <cstdio>
using namespace std;

static const int MAX_LEN = 250 + 1;

char input[MAX_LEN + 1];

int main()
{
	scanf("%s", input);

	int c = 0;
	for (int i = 0; input[i] != '\0'; i++) 
	{
		c = (c * 10 + input[i] - '0') % 3;
	}

	if (c == 0) {
		printf("%d\n", 2);
	} else {
		printf("%d\n%d\n", 1, c);
	}

	return 0;
}
