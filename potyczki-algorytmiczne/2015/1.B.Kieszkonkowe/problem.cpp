#include <algorithm>
#include <climits>
#include <cstdio>
using namespace std;

#undef DEBUG

#define EVEN(X) (X % 2 == 0)
#define ODD(X) (X % 2 != 0)

#define FOR(E, I) for(auto E = I.begin(); E != I.end(); E++)

int main()
{
	unsigned int n, denomination, numberOfOddDenominations = 0, minOddDenomination = UINT_MAX;
	unsigned long totalSum = 0L;

	scanf("%d", &n);

	while (n--)
	{
		scanf("%d", &denomination);

		totalSum += denomination;
		if (ODD(denomination))
		{
			numberOfOddDenominations++;
			minOddDenomination = min(minOddDenomination, denomination);
		}
	}

	if (ODD(numberOfOddDenominations))
	{
		totalSum -= minOddDenomination;
	}

	if (totalSum > 0)
	{
		printf("%ld\n", totalSum);
	}
	else
	{
		puts("NIESTETY");
	}

	return 0;
}
