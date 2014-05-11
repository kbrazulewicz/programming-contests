/* @JUDGE_ID: 16232QS 1193 C++ */

#include <algorithm>
#include <cstdio>
using namespace std;

static const int MAX_N = 100;

typedef struct {
	int t1;
	int t2;
	int t3;
} student_t;

bool operator < (const student_t& a, const student_t& b)
{
	return a.t1 < b.t1;
}

student_t students[MAX_N + 1];

int main()
{
	int n;

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &students[i].t1, &students[i].t2, &students[i].t3);
	}

	sort(students, students + n);

	int examEnd = 0, shift = 0;

	for (int i = 0; i < n; i++) {
		examEnd = max(examEnd, students[i].t1) + students[i].t2;
		shift = max(shift, examEnd - students[i].t3);
	}

	printf("%d\n", shift);

	return 0;
}
