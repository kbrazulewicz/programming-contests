#include <iostream>
#include <string>
using namespace std;

static const int MAX_N = 1000;

char w[100][MAX_N + 1];

int calcHardness(char* word, int length)
{
	int hardness = 1;
	for (int i = 1; i < length; i++) {
		if (word[i] != word[i - 1]) hardness++;
	}

	return hardness;
}

int calculate(int n, int k)
{
	int minHardness = calcHardness(w[0], n);
	return minHardness;
}

int main()
{
	int n, k;

	cin >> n;
	cin >> k;
	cin >> w[0];

	cout << calculate(n, k) << endl;

	return 0;
}
