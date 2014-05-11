#include <ctype.h>
#include <stdio.h>

#define MAX_LEN 100

char gVowel[] = "10001000100000100000100010";

int main()
{
	int c, voicedWordCount = 0;
	char word[MAX_LEN + 1 + 1];

	scanf("%d\n", &c);
	while (c--) {
		int vowelCount = 0, conosantCount = 0;
		char* letter = fgets(word, sizeof(word), stdin);

		while (*letter != 0 && *letter != '\n') {
			*letter = tolower(*letter);
			if (gVowel[*letter - 'a'] == '1') {
				vowelCount++;
			} else {
				conosantCount++;
			}
			letter++;
		}

		if (vowelCount > conosantCount && conosantCount > 0) {
			voicedWordCount++;
		}
	}
	printf("%d\n", voicedWordCount);

	return 0;
}
