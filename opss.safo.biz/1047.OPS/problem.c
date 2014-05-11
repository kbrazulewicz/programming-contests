#include <stdio.h>
#include <stdlib.h>

#define MAX_SYMBOL 500000

int stack[MAX_SYMBOL];

void ops()
{
	char input [16];
	int l1, l2;
	int *pStack = stack;

	do {
		scanf("%s", input);

		switch (input[0]) {
			case 'O':
				l1 = *(--pStack);
				l2 = *(--pStack);
				*pStack++ = l2 - l1;
				break;
			case 'P':
				l1 = *(--pStack);
				l2 = *(--pStack);
				*pStack++ = l2 * l1;
				break;
			case 'S':
				l1 = *(--pStack);
				l2 = *(--pStack);
				*pStack++ = l2 + l1;
				break;
			case '.':
				while (pStack > stack) {
					printf("%d ", *(--pStack));
				}
				break;
			default:
				*pStack++ = atoi(input);
		}
	} while (*input != '.');
	putchar('\n');
}

int main()
{
	int c;
	scanf("%d", &c);
	while (c--) {
		ops();
	}
	return 0;
}
