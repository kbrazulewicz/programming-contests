/* @JUDGE_ID: 16232QS 1161 C++ */

#include <cmath>
#include <cstdio>
#include <queue>
using namespace std;

priority_queue<double> stripies;

int main()
{
	int n, w;

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &w);
		stripies.push(w);
	}

	while (stripies.size() != 1) {
		double a, b;
		a = stripies.top(); stripies.pop();
		b = stripies.top(); stripies.pop();

		stripies.push(2 * sqrt(a * b));
	}

	printf("%.2f\n", stripies.top());

	return 0;
}
