#include <stdio.h>

#define MAX_WORD_LEN 100

static char gConversionTable[] = "22233344455566677778889999";

int main()
{
	int c;
	char phoneNumber[MAX_WORD_LEN + 1];

	scanf("%d", &c);
	for (int i = 0; i < c; i++) {
		scanf("%s", phoneNumber);
		for (int j = 0; phoneNumber[j] != 0; j++) {
			phoneNumber[j] = gConversionTable[phoneNumber[j] - 'A'];
		}
		printf("%s\n", phoneNumber);
	}
	return 0;
}
