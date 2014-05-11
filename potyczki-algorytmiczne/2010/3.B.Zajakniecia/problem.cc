#include <algorithm>
#include <cstdio>
#include <deque>
#include <iostream>
#include <iterator>
using namespace std;

static const int MAX_N = 1000;

char input[MAX_N + 1];

int lcs[MAX_N + 1][MAX_N + 1];

int longestCommonSubstringLength(const char* a, int aLen, const char* b, int bLen)
{
	for (int i = 0; i <= aLen; lcs[i++][0] = 0);
	for (int i = 0; i <= bLen; lcs[0][i++] = 0);

	for (int i = 0; i < aLen; i++) {
		for (int j = 0; j < bLen; j++) {
			if (a[i] == b[j]) {
				lcs[i + 1][j + 1] = 1 + lcs[i][j];
			} else {
				lcs[i + 1][j + 1] = max(lcs[i + 1][j], lcs[i][j + 1]);
			}
		}
	}

	return lcs[aLen][bLen];
}


int main()
{
	int n;

	scanf("%d\n", &n);
	fgets(input, n + 1, stdin);

	int maxLength = 0;
	int headLength = 1;

	while (headLength < (n - maxLength)) 
	{
		maxLength = max(maxLength, longestCommonSubstringLength(input, headLength, input + headLength, n - headLength));
		headLength++;
	}

	printf("%d\n", n - 2 * maxLength);

	return 0;
}
