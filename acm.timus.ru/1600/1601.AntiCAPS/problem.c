/* @JUDGE_ID: 16232QS 1601 C */

#include <stdio.h>

int main()
{
	char inSentence = 0;
	int input;

	while ((input = getchar()) != EOF) {
		if (inSentence) {
			if (input >= 'A' && input <= 'Z') {
				input = input - 'A' + 'a';
			} else if (input == '.' || input == '!' || input == '?') {
				inSentence = 0;
			}
		} else {
			if (input >= 'A' && input <= 'Z') {
				inSentence = 1;
			} else if (input >= 'a' && input <= 'z') {
				input = input - 'a' + 'A';
				inSentence = 1;
			}
		}
		putchar(input);
	}
	return 0;
}
