/* @JUDGE_ID: 16232QS 1123 C++ */

#include <iostream>
#include <string>
using namespace std;

static const int MAXL = 2001;

char input[MAXL + 1];

int main()
{
	scanf("%s", input);
	size_t size = strlen(input);

	bool firstDifference = true;
	for (int i = size / 2 - 1; i >= 0; i--) {
		size_t l = i, r = size - 1 - i;
		if (firstDifference) {
			if (input[l] > input[r]) {
				input[r] = input[l];
				firstDifference = false;
			} else if (input[l] < input[r]) {
				int l1 = (size - 1) / 2, r1 = size / 2;
				int c = 1;
				while (c != 0) {
					if (input[l1] == '9') {
						input[l1] = '0';
						c = 1;
					} else {
						input[l1]++;
						c = 0;
					}
					input[r1] = input[l1];
					l1--; r1++;
				}
				input[r] = input[l];
				firstDifference = false;
			}
		} else {
			input[r] = input[l];
		}
	}

	puts(input);

	return 0;
}
