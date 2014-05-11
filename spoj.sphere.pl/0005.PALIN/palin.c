#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 1000000

char input[MAX_LENGTH + 2];

void findPalindrom()
{
	int length, l, r;
	int tooSmall = 1;

	length = strlen(input) - 1;
	if (input[length] < '0' || input[length] > '9')
		input[length] = '\0';
	l = 0;
	r = length - 1;

	while (l < r) {
		if (input[l] != input[r]) {
			tooSmall = (input[l] > input[r]) ?  0 : 1;
			input[r] = input[l];
		}
		l++; r--;
	}

	if (l > r) {
		l--; r++;
	}

	while (tooSmall && l >= 0) {
		if (input[l] == '9') {
			input[l] = '0';
		} else {
			input[l]++;
			tooSmall = 0;
		}
		input[r++] = input[l--];
	}

	if (tooSmall) {
		input[0] = input[length] = '1';
		input[length + 1] = '\0';
	}
}

int main()
{
	int t;
	scanf("%d\n", &t);

	while (t--) {
		fgets(input, sizeof(input), stdin);
		findPalindrom();
		puts(input);
	}
	return 0;
}
