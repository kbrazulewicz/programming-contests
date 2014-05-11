/* @JUDGE_ID: 16232QS 1226 C++ */

#include <iostream>
#include <stack>
using namespace std;


int main()
{
	stack<char> word;

	while (!feof(stdin)) {
		int c = getc(stdin);

		if (isalpha(c)) {
			word.push((char) c);
		} else {
			while (!word.empty()) {
				cout << word.top();
				word.pop();
			}
			if (c != EOF) {
				cout << (char) c;
			}	
		}
	}

	return 0;
}
