#include <algorithm>
#include <cstdio>
using namespace std;

int main()
{
	long long n, t, r = 0;
	long long a1, a2, runningSum;

	scanf("%Ld %Ld %Ld", &n, &t, &a1);
	runningSum = a1;

	if (n == 1) {
		r = (t / 2 + 1) * a1;
	} else {
		n--;
		while (n-- && t--) {
			scanf("%Ld", &a2);
			runningSum += a2;

			r = max(r, runningSum + (t + 1) / 2 * a1 + t / 2 * a2);
			a1 = a2;
		}
	}

	printf("%lld\n", r);

	return 0;
}
