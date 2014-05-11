#include <stdio.h>
#include <string.h>

#define MAX_N 1000
#define ARRAY2D(a,w,x,y) a[y * w + x]

char board[MAX_N * MAX_N];
char visited[MAX_N * MAX_N];
char buffer[MAX_N + 2];

typedef struct {
	int x;
	int y;
} point_t;

int resolve(int n)
{
	point_t posDot = {0, 0};
	point_t pos = {0, 0};
	int len = 1, lenDot = 1;
	char c = 'p';

	memset(visited, 0, n * n);

	do {
		ARRAY2D(visited, n, pos.x, pos.y) = 1;

		c = ARRAY2D(board, n, pos.x, pos.y);

//		printf("[%d; %d] [%c]\n", pos.x, pos.y, c);

		switch (c) {
			case 'l': pos.x--; len++; break;
			case 'g': pos.y++; len++; break;
			case 'p': pos.x++; len++; break;
			case 'd': pos.y--; len++; break;
			case 'k': break;
			case '.': posDot = pos; lenDot = len; break;
		}

		if (c != 'k' && (pos.x < 0 || pos.x >= n || pos.y < 0 || pos.y >= n || ARRAY2D(visited, n, pos.x, pos.y) || c == '.')) {
			// retract to the last dot (or we are at the dot)
			pos = posDot;
			len = lenDot;

			// make another decision
			char d = ARRAY2D(board, n, pos.x, pos.y);
			switch (d) {
				case '.': d = 'l'; break;
				case 'l': d = 'g'; break;
				case 'g': d = 'p'; break;
				case 'p': d = 'd'; break;
				case 'd': exit(-1); break;
			}
			ARRAY2D(board, n, pos.x, pos.y) = d;
//			printf("[%d; %d] [%c] - redecided\n", pos.x, pos.y, d);
		}

	} while (c != 'k');

	return len;
}

void printResolution(n)
{
	point_t pos = {0, 0};
	char c;

	do {
		printf("%d %d\n", pos.x + 1, pos.y + 1);

		c = ARRAY2D(board, n, pos.x, pos.y);
		switch (c) {
			case 'l': pos.x--; break;
			case 'g': pos.y++; break;
			case 'p': pos.x++; break;
			case 'd': pos.y--; break;
			case 'k': break;
		}

	} while (c != 'k');
}


void displayMap(int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%c", ARRAY2D(board, n, j, i));
		}
		printf("\n");
	}
}


int main()
{
	int c, n;

	scanf("%d\n", &c);

	while (c--) {
		scanf("%d\n", &n);
		int i = n;
		while (i--) {
			fgets(buffer, n + 2, stdin);
			memcpy(board + i * n, buffer, n);
		}

		int l = resolve(n);
		printf("%d\n", l);
		printResolution(n);
	}

	return 0;
}
