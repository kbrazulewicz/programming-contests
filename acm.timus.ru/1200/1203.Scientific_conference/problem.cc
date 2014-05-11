/* @JUDGE_ID: 16232QS 1203 C++ */

#include <algorithm>
#include <iostream>
using namespace std;

static const int MAX_N = (int) 1e5;

typedef struct {
	int s;
	int e;
} report_t;

bool operator < (const report_t& a, const report_t& b)
{
	return a.e < b.e;
}

report_t report[MAX_N];

int main() {
	int n, r = 0, e = 0; 
	
	scanf("%d",&n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &report[i].s, &report[i].e);
	}

	sort(report, report + n);

	for (int i = 0; i < n; i++) {
		if (report[i].s > e) {
			r++;
			e = report[i].e;
		}
	}
	printf("%d\n", r);

	return 0;
} 
