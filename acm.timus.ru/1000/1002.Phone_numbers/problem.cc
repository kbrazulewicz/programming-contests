/* @JUDGE_ID: 16232QS 1002 C++ */

#include <iostream>
#include <string>
using namespace std;

static const size_t MAX_INPUT_LENGTH = 100;
static const size_t MAX_WORD_LENGTH  = 50;
static const size_t MAX_DICT_LENGTH  = 50000;

typedef struct {
	char word[MAX_WORD_LENGTH + 1];
	char code[MAX_WORD_LENGTH + 1];
	size_t length;
} dictionary_t;

//                                   abcdefghijklmnopqrstuvwxyz
static const char *wordConversion = "22233344115566070778889990";

char input[MAX_INPUT_LENGTH + 1];

dictionary_t dictionary[MAX_DICT_LENGTH];

bool operator < (const dictionary_t& a, const dictionary_t& b) 
{
	int r = strncmp(a.code, b.code, min(a.length, b.length));
	if (r == 0) {
		r = b.length - a.length;
	}

	return r < 0;
}


void match(list<int>& words, size_t offset)
{
	if (input[offset] != '\0') {
	}
}


int main()
{
	int numOfWords;

	while (input[0] != '-') {
		scanf("%s", input);

		if (input[0] != '-') {
			scanf("%d", &numOfWords);

			for (int i = 0; i < numOfWords; i++) {
				scanf("%s", dictionary[i].word);

				int j = 0;
				while (dictionary[i].word[j] != '\0') {
					dictionary[i].code[j] = wordConversion[dictionary[i].word[j] - 'a'];
					j++;
				}
				dictionary[i].code[j] = '\0';
				dictionary[i].length = j;
			}

			sort(dictionary, dictionary + numOfWords);

			list<int> words;
			match(words, 0);

			if (words.empty()) {
				printf("No solution.\n");
			} else {
				
			}
		}
	}

	return 0;
}
