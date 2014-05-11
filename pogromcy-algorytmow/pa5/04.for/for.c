#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100
#define MAX_M 100

#define LOGIC_1 '1'
#define LOGIC_0 '0'
#define LOGIC_N '.'

char logicClause[MAX_M][MAX_N];
// TODO: remove
char commonBits[MAX_M][MAX_M];

int nullBits[MAX_N];
int commonNullBits[MAX_M][MAX_M];
int isConflicting[MAX_M][MAX_M];

unsigned char alwaysFalse[MAX_M];


int isTrue(char aValue[], int n, int m)
{
	int i, j;

	for (i = 0; i < m; i++) {
		if (!alwaysFalse[i]) {
			j = 0;
			while (j < n && (logicClause[i][j] == aValue[j] || logicClause[i][j] == LOGIC_N)) j++;

			if (j == n) return 1;
		}
	}

	return 0;
}


int incValue(char aValue[], int n)
{
	int i, c = 1;
	for (i = 0; i < n; i++) {
		if (aValue[i] == LOGIC_0) {
			aValue[i] = LOGIC_1;
			c = 0;
		} else {
			aValue[i] = LOGIC_0;
			c = 1;
		}

		if (c == 0) return 0;
	}

	// overflow
	return 1;
}


void calcCommonBits(int n, int m)
{
	int i, j, k;
	for (i = 0; i < m; i++) {
		for (j = 0; j < m; j++) {
			int commonBitCount = 0;
			for (k = 0; k < n; k++) {
				if (logicClause[i][k] == LOGIC_N && logicClause[j][k] == LOGIC_N) {
					commonNullBits[i][j]++;
				}

				if (logicClause[i][k] != LOGIC_N && logicClause[j][k] != LOGIC_N) {
					if (logicClause[i][k] == logicClause[j][k]) {
						// printf("calcCommonBits: clauses [%d] and [%d], bit [%d] common\n", i, j, k);
						commonBitCount++;
					} else {
						// printf("calcCommonBits: clauses [%d] and [%d], bit [%d] conflicting\n", i, j, k);
						commonBitCount = -1;
						break;
					}
				}
			}
			printf("calcCommonBits: clauses [%d] and [%d], commonNullBits [%d]\n", i + 1, j + 1, commonNullBits[i][j]);

			commonBits[i][j] = commonBitCount == 0 ? '0' : commonBitCount > 0 ? '+' : 'X';
			isConflicting[i][j] = commonBitCount < 0 ? 1 : 0;
		}
	}
}


void calculateSAT(int n, int m)
{
	int i, j;
	int goodTries[MAX_N];

	memset(goodTries, 0, sizeof(goodTries));
	
	for (i = 0; i < m; i++) {
		goodTries[commonNullBits[i][i]]++;
		for (j = i + 1; j < m; j++) {
			if (!isConflicting[i][j]) {
				goodTries[commonNullBits[i][j]]--;
			}
		}

		printf("calculateSAT: clause [%02d]; goodTries", i + 1);
		for (j = 0; j < n; j++) {
			printf(" %d", goodTries[j]);
		}
		printf("\n");
	}
}





void printArray(const char* aArray, int width, int cols, int rows)
{
	int i;

	for (i = 0; i < rows; i++) {
		printf("%.*s\n", cols, aArray + i * width);
	}
}

void printFormula(int n, int m)
{
	printf("formula:\n");
	printArray((const char*)logicClause, MAX_N, n, m);
	printf("---\n");
}

void printCommonBits(int m)
{
	printf("commonBits:\n");
	printArray((const char*)commonBits, MAX_M, m, m);
	printf("---\n");
}


int main()
{
	int n, m;
	int i, j;

	char value[MAX_N];

	scanf("%d %d", &n, &m);

	if (n > 63) {
		printf("This will not work\n");
		return 1;
	}

	memset(logicClause, LOGIC_N, sizeof(logicClause));
	memset(commonBits, LOGIC_N, sizeof(commonBits));

	int logicClauseOffset = 0;
	for (i = 0; i < m; i++) {
		int l, x, v;
		scanf("%d", &l);

		int conflict = 0;

		for (j = 0; j < l; j++) {
			scanf("%d", &x);

			v = x > 0 ? LOGIC_1 : LOGIC_0;
			x = abs(x) - 1;

			if (logicClause[logicClauseOffset][x] != LOGIC_N && logicClause[logicClauseOffset][x] != v) {
				conflict = 1;
			} else {
				logicClause[logicClauseOffset][x] = v;
			}
		}

		if (conflict == 0) {
			logicClauseOffset++;
		} else {
			memset(logicClause[logicClauseOffset], LOGIC_N, MAX_N * logicClause[0][0]);
		}
	}

	m = logicClauseOffset;


	printFormula(n, m);

	calcCommonBits(n, m);
	printCommonBits(m);

	memset(value, LOGIC_0, sizeof(value));
	unsigned long long goodTries = 0LL;
	unsigned long long allTries  = 1;
	unsigned long long tryCount  = 0LL;

	allTries <<= (n > 31 ? 31 : n);
	allTries <<= (n > 31 ? n - 31 : 0);
	
	printf("main: %llu iterations\n", allTries);

	do {
		if (isTrue(value, n, m)) goodTries++;

		tryCount++;

		if (tryCount % 10000000 == 0) {
			printf("try #%llu\n", tryCount);
		}
	} while (!incValue(value, n));

	printf("good: %llu; all: %llu\n", goodTries, allTries);

	calculateSAT(n, m);
	
	return 0;
}
