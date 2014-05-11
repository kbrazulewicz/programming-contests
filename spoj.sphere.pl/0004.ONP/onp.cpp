#include <cstdio>

#include <map>
#include <stack>

using namespace std;

#define REP(i, n) for (i = 0; i < (n); ++i)

#define MAX_LENGTH 400

map<char, int> gOperatorPriority;

char expressionNOR[MAX_LENGTH + 2 + 1];
char expressionRPN[MAX_LENGTH + 2 + 1];

void initialize()
{
	gOperatorPriority.insert(make_pair('+', 1));
	gOperatorPriority.insert(make_pair('-', 2));
	gOperatorPriority.insert(make_pair('*', 3));
	gOperatorPriority.insert(make_pair('/', 4));
	gOperatorPriority.insert(make_pair('^', 5));
}


void convertExpression(const char* aInput, char* aOutput)
{
	bool endOfExpression = 0;
	int bracketLevel    = 0;
	stack< pair<char, int> > operatorStack;

	char *outBuffer = expressionRPN;

	do {
		char curr = *aInput++;
		switch (curr) {
			case '(':
				bracketLevel++;
				break;

			case ')':
				while (!operatorStack.empty() && 
						operatorStack.top().second == bracketLevel)
				{
					*outBuffer++ = operatorStack.top().first;
					operatorStack.pop();
				}
				--bracketLevel;
				break;

			case '+':
			case '-':
			case '*':
			case '/':
			case '^':
				while (!operatorStack.empty() && 
						operatorStack.top().second == bracketLevel && 
						gOperatorPriority[operatorStack.top().first] > gOperatorPriority[curr]) 
				{
					*outBuffer++ = operatorStack.top().first;
					operatorStack.pop();
				}
				operatorStack.push(make_pair(curr, bracketLevel));
				break;

			default:
				if (curr >= 'a' && curr <= 'z') {
					*outBuffer++ = curr;
				} else {
					endOfExpression = true;
				}
				break;
		}
	} while (!endOfExpression);

	while (!operatorStack.empty())
	{
		*outBuffer++ = operatorStack.top().first;
		operatorStack.pop();
	}
}

int main()
{
	int t, i;
	scanf("%d", &t);

	initialize();

	REP(i, t) {
		scanf("%s", expressionNOR);
		convertExpression(expressionNOR, expressionRPN);
		printf("%s\n", expressionRPN);
	}
	return 0;
}
