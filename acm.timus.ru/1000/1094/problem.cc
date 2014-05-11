/* @JUDGE_ID: 16232QS 1094 C++ */

#include <iostream>
#include <set>
#include <string>
using namespace std;

static const int SCREEN_WIDTH = 80;

string input;
string output;

char allowedChars[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789:;-!?., "};
set<char> allowedCharset(allowedChars, allowedChars + sizeof(allowedChars));

int main()
{
	output.insert(output.end(), SCREEN_WIDTH, ' ');

	getline(cin, input);

	int index = 0;
	for (string::const_iterator i = input.begin(); i != input.end(); i++)
	{
		if (*i == '>') {
			index = (index + 1) % SCREEN_WIDTH;
		} else if (*i == '<') {
			if (index != 0) index--;
		} else if (allowedCharset.find(*i) != allowedCharset.end()) {
			output[index] = *i;
			index = (index + 1) % SCREEN_WIDTH;
		}
	}

	cout << output << endl;
	
	return 0;
}
