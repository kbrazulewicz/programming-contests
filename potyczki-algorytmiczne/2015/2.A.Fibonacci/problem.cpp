#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdio>
using namespace std;

#undef DEBUG

#define EVEN(X) (X % 2 == 0)
#define ODD(X) (X % 2 != 0)

#define FOR(E, I) for(auto E = I.begin(); E != I.end(); E++)

const int MAX_N = 18;

unsigned long long powerOf10 [MAX_N + 1] = { 1, 1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8, 1e9, 1e10, 1e11, 1e12, 1e13, 1e14, 1e15, 1e16, 1e17, 1e18 };
unsigned long long fibonacciModulo10PeriodLength[MAX_N + 1] = {
	1, 
	60, // 10^1
	300, // 10^2
	1500, // 10^3
	15000, // 10^4
	150 * 1e3, // 10^5
	1500 * 1e3, // 10^6
	15000 * 1e3, // 10^7
	150 * 1e6, // 10^8
	1500 * 1e6, // 10^9
	15000 * 1e6, // 10^10
	150 * 1e9, // 10^11
	1500 * 1e9, // 10^12
	15000 * 1e9, // 10^13
	150 * 1e12, // 10^14
	1500 * 1e12, // 10^15
	15000 * 1e12, // 10^16
	150 * 1e15, // 10^17
	1500 * 1e15 // 10^18
};

void fibonacciFindZero(unsigned long long modulo)
{
	unsigned long long Fn_2 = 0;
	unsigned long long Fn_1 = 1;

	for (unsigned long long n = 2; n < ULLONG_MAX; n++)
	{
		unsigned long long Fn = (Fn_1 + Fn_2) % modulo;

		if (Fn == 0) 
		{
			printf("F(%llu) === 0 mod %llu, F(%llu) === %llu mod %llu\n", n, modulo, n + 1, Fn_1, modulo);

			unsigned long long a = Fn_1;
			unsigned long long orderOfA = 1;

			for (unsigned long long o = 1; o < ULLONG_MAX; o++)
			{
				orderOfA = (orderOfA * a) % modulo;
				if (orderOfA == 1)
				{
					printf("%llu ^ %llu === 1 mod %llu\n", a, o, modulo);
					printf("Period length for modulo %llu is %llu\n", modulo, n * o);
					break;
				}
			}

			return;
		}

		Fn_2 = Fn_1;
		Fn_1 = Fn;
	}
}

unsigned long long fibonacciWithThatSuffixExists(unsigned long long suffix, int length)
{
	unsigned long long modulo = powerOf10[length];
	unsigned long long minValue = powerOf10[length - 1];
	unsigned long long period = fibonacciModulo10PeriodLength[length];
	suffix = suffix % modulo;

#ifdef DEBUG
	printf("suffix %llu, length %d\n", suffix, length);
#endif

	if (suffix == 0 && length == 1) return 0;

	unsigned long long Fn_2 = 0;
	unsigned long long Fn_1 = 1;

	bool FnGreaterThanModulo = false;

	for (unsigned long long n = 2; n < period; n++)
	{
		unsigned long long Fn = Fn_1 + Fn_2;
		FnGreaterThanModulo = FnGreaterThanModulo || Fn >= minValue;
		Fn %= modulo;

		if (FnGreaterThanModulo && Fn == suffix)
		{
			return n;
		}

		Fn_2 = Fn_1;
		Fn_1 = Fn;
	}

	return ULLONG_MAX;
}


int main()
{
	/*
	fibonacciFindZero(10);
	fibonacciFindZero(100);
	fibonacciFindZero(1000);
	fibonacciFindZero(1000000);
	fibonacciFindZero(1000000000);
	*/

	int n = 0;
	unsigned long long suffix = 0;

	for (n = 0; n <= MAX_N; n++)
	{
		int d = fgetc(stdin);
		if (!isdigit(d)) break;

		suffix *= 10;
		suffix += d - '0';
	}


#ifdef DEBUG
	printf("input [%llu], length [%d], modulo [%llu]\n", suffix, n, powerOf10[n]);
#endif

	unsigned long long k;
	for (int l = 1; l <= n && k != ULLONG_MAX; l++)
	{
		k = fibonacciWithThatSuffixExists(suffix, l);
	}

	if (k != ULLONG_MAX)
	{
		printf("%llu\n", k);
	}
	else
	{
		puts("NIE");
	}

	return 0;
}
