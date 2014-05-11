/* @JUDGE_ID: 16232QS 1612 C */

#include <stdio.h>

#define MAX_SIZE 10000

char input[MAX_SIZE + 1];

int main()
{
	int tramCount = 0;
	int trolleybusCount = 0;

	char search1[]	= "tram";
	int  search1Len	= 4;
	char search2[]	= "trolleybus";
	int  search2Len	= 10;

	while (fgets(input, sizeof(input), stdin) != NULL) {
		char *haystack = input, *needle = NULL;

		while ((needle = strstr(haystack, search1)) != NULL) {
			char t = needle[search1Len];
			if (t == ' ' || t == '\n' || t == '.' || t == ',' || t == '-' || t == ':' || t == '!' || t == '?') {
				tramCount++;
			}
			haystack = needle + search1Len;
		}

		haystack = input, needle = NULL;
		while ((needle = strstr(haystack, search2)) != NULL) {
			char t = needle[search2Len];
			if (t == ' ' || t == '\n' || t == '.' || t == ',' || t == '-' || t == ':' || t == '!' || t == '?') {
				trolleybusCount++;
			}
			haystack = needle + search2Len;
		}
	}

	if (tramCount > trolleybusCount) {
		printf("Tram driver\n");
	} else if (tramCount < trolleybusCount) {
		printf("Trolleybus driver\n");
	} else {
		printf("Bus driver\n");
	}

	return 0;
}
