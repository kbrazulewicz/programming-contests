/* @JUDGE_ID: 16232QS 1306 C++ */

#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

int main()
{
	int n, a, m1, m2;
	priority_queue<unsigned int> q;

	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &a);
		
		if (i <= n / 2) {
			q.push(a);
		} else {
			if (a < q.top()) {
				q.pop();
				q.push(a);
			}	
		}
	}


	if (n % 2 == 0) {
		unsigned int r = q.top();
		q.pop();
		r += q.top();
		printf("%.1f\n", (double) r / 2);
	} else {
		printf("%.1f\n", (double) q.top());
	}


	return 0;
}
