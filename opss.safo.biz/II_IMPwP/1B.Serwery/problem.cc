#include <iostream>
#include <string>
using namespace std;


int main()
{
	unsigned int c, n, a;

	scanf("%u", &c);
	for (int i = 0; i < c; i++) {
		unsigned long long result = 0LL;
		unsigned int maxA = 0;
		scanf("%u", &n);
		for (int j = 0; j < n; j++) {
			scanf("%u", &a);
			result += a;
			maxA = max(maxA, a);
		}
		result -= maxA;
		printf("%llu\n", result);
	}
	return 0;
}
