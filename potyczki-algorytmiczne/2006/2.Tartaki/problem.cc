#include <algorithm>
#include <cstdio>
using namespace std;

static const int MAX_N = 1000000;

char gInput[2 * MAX_N + 1];
int  gStack[MAX_N];


char* putInt(char* aBuffer, int aValue)
{
	static const int maxLength = 10;
	char digits[maxLength + 1];
	int index = sizeof(digits);

	digits[--index] = '\0';
	do {
		digits[--index] = '0' + (aValue % 10);
		aValue /= 10;
	} while (aValue);

	strcpy(aBuffer, digits + index);

	return aBuffer + maxLength - index;
}


int main()
{
	int n, g = 0, t = 0, i = 0, e;
	int stackTop = -1;
	char buffer[32];

	scanf("%d\n", &n);
	n *= 2;
	fgets(gInput, n + 1, stdin);

	while (i < n) {
		if (gInput[i] == 'g') {
			e = ++g;
		} else {
			e = --t;
		}

		if (stackTop < 0 || (e > 0 && gStack[stackTop] > 0) || (e < 0 && gStack[stackTop] < 0)) {
			gStack[++stackTop] = e;
		} else {

#if 1
			char *o = putInt(buffer, max(e, gStack[stackTop]));
			*(o++) = ' ';
			o = putInt(o, - min(e, gStack[stackTop]));
			puts(buffer);
#else
			printf("%d %d\n", max(e, gStack[stackTop]), - min(e, gStack[stackTop]));
#endif
			stackTop--;
		}

		i++;
	}

	return 0;
}
