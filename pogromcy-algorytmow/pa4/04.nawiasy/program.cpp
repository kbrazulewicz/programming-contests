#include <cstdio>
#include <cstring>
#include <iostream>
#include <iterator>
#include <set>

using namespace std;

#define EXPRESSION_MAX 30000

// input string
char     bracketExpr[EXPRESSION_MAX + 1];
int      bracketExprChecksum;
set<int> bracketExprDirChange;

// cached output string
char output[1000000 * 4 + 1];

// conversion from '(' ')' into 1 and -1 (only 2 bytes used anyway)
char conv[128];

bool isExpressionCorrect(int aNumBracket)
{
	if (bracketExprChecksum != 0 || bracketExpr[0] != 1) return false;

	int sum = 0;
	set<int>::iterator it  = bracketExprDirChange.begin();
	set<int>::iterator itE = bracketExprDirChange.end();
	int lastVal   = 0;
	int bGradient = +1;
	while (it != itE) {
		sum += (*it - lastVal) * bGradient;
		if (sum < 0) return false;
		bGradient = -bGradient;
		lastVal = *it;
		it++;
	}
	return sum == 0;
}

int main()
{
	int lNaw, lOp, op;
	char* buffer = output;

	conv['('] =  1;
	conv[')'] = -1;

	scanf("%d%s%d", &lNaw, bracketExpr, &lOp);

	// input data
	for (int i = 0; i < lNaw; i++) {
		bracketExpr[i] = conv[bracketExpr[i]];
		bracketExprChecksum += bracketExpr[i];
		if (i > 0 && bracketExpr[i - 1] != bracketExpr[i]) {
			bracketExprDirChange.insert(i);
		}
	}
	bracketExprDirChange.insert(lNaw);

	while (lOp--) {
		scanf("%d", &op);
		if (op--) {
			if (!bracketExprDirChange.erase(op)) {
				bracketExprDirChange.insert(op);
			}
			if (op + 1 != lNaw) {
				if (!bracketExprDirChange.erase(op + 1)) {
					bracketExprDirChange.insert(op + 1);
				}
			}
			bracketExpr[op] = -bracketExpr[op];
			bracketExprChecksum += (2 * bracketExpr[op]);
		} else {
			strcpy(buffer, isExpressionCorrect(lNaw) ? "TAK\n" : "NIE\n");
			buffer += 4;
		}
	}

	// dirty trick to remove last \n (for puts function)
	*(--buffer) = 0;
	// puts is MUCH faster that printf (but it adds \n at the end of output)
	puts(output);

	return 0;
}
