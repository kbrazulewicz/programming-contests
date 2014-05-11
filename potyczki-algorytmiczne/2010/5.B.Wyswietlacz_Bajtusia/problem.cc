#include <algorithm>
#include <cstdio>
#include <functional>
#include <vector>
using namespace std;

#undef DEBUG

static const int MAX_L = 100000;

char input[MAX_L + 1];

class ConversionProperties
{
	public:
		unsigned char input;
		unsigned char output;
		unsigned char cost;

		ConversionProperties(unsigned char input, unsigned char output, unsigned char cost)
		{
			this->input  = input;
			this->output = output;
			this->cost   = cost;
		}
};

vector<ConversionProperties> conversionOrder;


void precalculateCost()
{
	// order is important
	conversionOrder.push_back(ConversionProperties(3, 9, 1));
	conversionOrder.push_back(ConversionProperties(5, 9, 1));
	conversionOrder.push_back(ConversionProperties(8, 9, 1));
	conversionOrder.push_back(ConversionProperties(0, 9, 2));
	conversionOrder.push_back(ConversionProperties(4, 9, 2));
	conversionOrder.push_back(ConversionProperties(6, 9, 2));
	conversionOrder.push_back(ConversionProperties(2, 9, 3));
	conversionOrder.push_back(ConversionProperties(7, 9, 3));
	conversionOrder.push_back(ConversionProperties(1, 9, 4));
	conversionOrder.push_back(ConversionProperties(0, 8, 1));
	conversionOrder.push_back(ConversionProperties(6, 8, 1));
	conversionOrder.push_back(ConversionProperties(2, 8, 2));
	conversionOrder.push_back(ConversionProperties(1, 7, 1));
}


char* kalkulator(int n, int l, char* a)
{
	int digitsOriginal[10] = {0,0,0,0,0,0,0,0,0,0};
	int digits[10]   = {0,0,0,0,0,0,0,0,0,0};

	// calculate number of particular digits
	for (int i = 0; i < l; digitsOriginal[a[i++] - '0']++);
	copy(digitsOriginal, digitsOriginal + 10, digits);

#ifdef DEBUG
	printf("N [%d]\n", n);
	for (int i = 9; i >= 0; i--) {
		if (digits[i] > 0) {
			printf("DIGITS [%d] [%d]\n", i, digits[i]);
		}
	}
#endif	

	for (vector<ConversionProperties>::const_iterator i = conversionOrder.begin(); i != conversionOrder.end(); i++)
	{
		int numberToConvert = min(n / i->cost, digits[i->input]);
		if (numberToConvert > 0) {
			digits[i->input]  -= numberToConvert;
			digits[i->output] += numberToConvert;
			l -= numberToConvert;
			n -= numberToConvert * i->cost;

#ifdef DEBUG
			printf("N [%d], CONV [%d]->[%d] for [%d]\n", n, i->input, i->output, i->cost);

			for (int i = 9; i >= 0; i--) {
				if (digits[i] > 0) {
					printf("DIGITS [%d] [%d]\n", i, digits[i]);
				}
			}
#endif	
		}

		if (i->input == 8 && i->output == 9) {
			// end of cost 1 for 9
		} else if (i->input == 6 && i->output == 9) {
			// end of cost 2 for 9
			if (n == 1 && digits[0] > 0 && digitsOriginal[8] > 0) {
				digits[0]--;
				digits[8]++;
				n--;
#ifdef DEBUG
				printf("N [%d], CONV [%d]->[%d] for [%d]\n", n, 80, 98, 1);
#endif
			}
			if (n == 1 && digits[4] > 0 && digitsOriginal[8] > 0) {
				digits[4]--;
				digits[8]++;
				n--;
#ifdef DEBUG
				printf("N [%d], CONV [%d]->[%d] for [%d]\n", n, 84, 98, 1);
#endif
			}
			if (n == 1 && digits[4] > 0 && digitsOriginal[5] > 0) {
				digits[4]--;
				digits[5]++;
				n--;
#ifdef DEBUG
				printf("N [%d], CONV [%d]->[%d] for [%d]\n", n, 54, 95, 1);
#endif
			}
		} else if (i->input == 7 && i->output == 9) {
			// end of cost 3 for 9
			if (n == 2 && digits[2] > 0 && digitsOriginal[8] > 0) {
				digits[2]--;
				digits[8]++;
				n -= 2;
#ifdef DEBUG
				printf("N [%d], CONV [%d]->[%d] for [%d]\n", n, 82, 98, 2);
#endif
			}
			if (n == 2 && digits[7] > 0 && digitsOriginal[8] > 0) {
				digits[7]--;
				digits[8]++;
				n -= 2;
#ifdef DEBUG
				printf("N [%d], CONV [%d]->[%d] for [%d]\n", n, 87, 98, 2);
#endif
			}
			if (n == 1 && digits[0] > 0) {
				digits[0]--;
				digits[8]++;
				n--;
#ifdef DEBUG
				printf("N [%d], CONV [%d]->[%d] for [%d]\n", n, 0, 8, 1);
#endif
			}
			if (n == 1 && digits[6] > 0) {
				digits[6]--;
				digits[8]++;
				n--;
#ifdef DEBUG
				printf("N [%d], CONV [%d]->[%d] for [%d]\n", n, 6, 8, 1);
#endif
			}
			if (n == 1 && digits[1] > 0) {
				digits[1]--;
				digits[7]++;
				n--;
#ifdef DEBUG
				printf("N [%d], CONV [%d]->[%d] for [%d]\n", n, 1, 7, 1);
#endif
			}
			if (n == 1 && digits[2] > 0 && digitsOriginal[6] != digits[6]) {
				digits[2]--;
				digits[6]++;
				n--;
#ifdef DEBUG
				printf("N [%d], CONV [%d]->[%d] for [%d]\n", n, 62, 96, 1);
#endif
			}
			if (n == 1 && digits[2] > 0 && digitsOriginal[4] != digits[4]) {
				digits[2]--;
				digits[4]++;
				n--;
#ifdef DEBUG
				printf("N [%d], CONV [%d]->[%d] for [%d]\n", n, 42, 94, 1);
#endif
			}
		} else if (i->input == 1 && i->output == 9) {
			// end of cost 4 for 9
			if (n == 3 && digits[1] > 0 && digitsOriginal[8] > 0) {
				digits[1]--;
				digits[8]++;
				n -= 3;
#ifdef DEBUG
				printf("N [%d], CONV [%d]->[%d] for [%d]\n", n, 81, 98, 3);
#endif
			}
		}
	}

#ifdef DEBUG
	printf("N [%d]\n", n);
	for (int i = 9; i >= 0; i--) {
		if (digits[i] > 0) {
			printf("DIGITS [%d] [%d]\n", i, digits[i]);
		}
	}
#endif	

	char* output = a;
	for (int i = 9; i >= 0; i--) {
		for (int j = 1; j <= digits[i]; j++) {
			*(output++) = i + '0';
		}
	}

	return a;
}


int main()
{
	precalculateCost();

	int k;

	scanf("%d", &k);

	for (int i = 1; i <= k; i++)
	{
		int n, l;
		scanf("%d %d %s", &n, &l, input);
		puts(kalkulator(n, l, input));
	}

	return 0;
}
