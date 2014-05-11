#include <cctype>
#include <cstdio>
#include <cstring>

#include <deque>
#include <set>
#include <stack>
#include <vector>
using namespace std;

static const int MAX_N = 10000;
static const int MAX_EXP_LEN = 256;

enum OP {
	OP_MUL,
	OP_PLUS,
	OP_MINUS
};

int evaluate(const char**);
int evaluateBrackets(const char**);
int evaluateInteger(const char**);

char gExpression[MAX_N][MAX_EXP_LEN + 1 + 1];
unsigned int gExpressionValue[MAX_N];
char gExpressionCalculated[MAX_N];
set<int> gExpressionDependencies[MAX_N];


int evaluateBrackets(const char** aExpressionPtr)
{
	(*aExpressionPtr)++;
	return evaluate(aExpressionPtr);
}

int evaluateInteger(const char** aExpressionPtr)
{
	int value = 0;
	while (isdigit(**aExpressionPtr)) {
		value *= 10;
		value += **aExpressionPtr - '0';
		(*aExpressionPtr)++;
	}
	return value;
}

void evaluateStack(vector<OP>& aOps, vector<int>& aVal, bool aEnforce)
{
	if (aOps.empty()) return;

	if (aEnforce) {
		int a = aVal.front(); aVal.erase(aVal.begin());
		int b;
		OP op;

		while (!aVal.empty()) {
			b = aVal.front(); aVal.erase(aVal.begin());
			op = aOps.front(); aOps.erase(aOps.begin());
			if (op == OP_MUL) {
				a *= b;
			} else if (op == OP_PLUS) {
				a += b;
			} else if (op == OP_MINUS) {
				a -= b;
			}
		}
		aVal.push_back(a);
	} else {
		if (aOps.size() == aVal.size()) return;

		OP op = aOps.back();
		if (op == OP_MUL) {
			aOps.pop_back();
			int b = aVal.back(); aVal.pop_back();
			int a = aVal.back(); aVal.pop_back();
			aVal.push_back(a * b);
		}
	}
}

int evaluate(const char** aExpressionPtr)
{
	int mul = 1;
	vector<OP> ops;
	vector<int> val;

	while (**aExpressionPtr) {
		if (isdigit(**aExpressionPtr)) {
			val.push_back(mul * evaluateInteger(aExpressionPtr));
			mul = 1;
		} else if (**aExpressionPtr == '(') {
			val.push_back(mul * evaluateBrackets(aExpressionPtr));
			mul = 1;
		} else if (**aExpressionPtr == '*') {
			ops.push_back(OP_MUL);
			(*aExpressionPtr)++;
		} else if (**aExpressionPtr == '+') {
			ops.push_back(OP_PLUS);
			(*aExpressionPtr)++;
		} else if (**aExpressionPtr == '-') {
			if (val.empty()) {
				mul = -1;
			} else {
				ops.push_back(OP_MINUS);
			}
			(*aExpressionPtr)++;
		} else if (**aExpressionPtr == 'w') {
			(*aExpressionPtr)++;
			int tmp = evaluateInteger(aExpressionPtr) - 1;
			val.push_back(mul * gExpressionValue[tmp]);
			mul = 1;
		} else if (**aExpressionPtr == ')') {
			(*aExpressionPtr)++;
			break;
		} else {
			(*aExpressionPtr)++;
		}
		evaluateStack(ops, val, false);
	}

	evaluateStack(ops, val, true);
	return val.back();
}


int calculate(const char* aExpression)
{
	return evaluate(&aExpression);
}

int main()
{
	int n, q;
	scanf("%d\n", &q);

	deque<int> expressionOrder;
	stack<int> expressionQueue;

	while (q--) {
		scanf("%d\n", &n);
		for (int i = 0; i < n; i++) {
			fgets(gExpression[i], sizeof(gExpression[i]), stdin);
			char* ptr = strchr(gExpression[i], '\n');
			if (ptr != NULL) *ptr = 0;
			
			gExpressionDependencies[i].clear();
			ptr = strchr(gExpression[i], 'w');
			while (ptr != NULL) {
				ptr++;
				int dependsOn = atoi(ptr) - 1;
				gExpressionDependencies[i].insert(dependsOn);
				ptr = strchr(ptr, 'w');
			}
			if (gExpressionDependencies[i].empty()) {
				expressionOrder.push_front(i);
			} else {
				expressionOrder.push_back(i);
			}
		}

		memset(gExpressionCalculated, 0, sizeof(gExpressionCalculated));

		while (!expressionOrder.empty()) {
			int expIndex = expressionOrder.front(); expressionOrder.pop_front();

			if (!gExpressionCalculated[expIndex]) {
				expressionQueue.push(expIndex);

				while (!expressionQueue.empty()) {

					expIndex = expressionQueue.top();

					set<int>& expDependencies = gExpressionDependencies[expIndex];
					set<int>::const_iterator i = expDependencies.begin();
					bool canCalculate = true;
					while (i != expDependencies.end()) {
						if (!gExpressionCalculated[*i]) {
							expressionQueue.push(*i);
							canCalculate = false;
						}
						i++;
					}
					if (canCalculate) {
						gExpressionValue[expIndex] = calculate(gExpression[expIndex]);
						gExpressionCalculated[expIndex] = 1;
						expressionQueue.pop();
					}
				}

			}
		}

		for (int i = 0; i < n; i++) {
			printf("%d\n", gExpressionValue[i]);
		}
	}
	return 0;
}
