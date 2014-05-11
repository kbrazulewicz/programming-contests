#include <stdio.h>

#define MAX_N 200

typedef struct node {
	unsigned int l;
	unsigned int r;
	unsigned int s;

	struct node* prev;
	struct node* next;
} node_t;

/**
 */
void scanfLineToUnsignedIntArray(unsigned int aBuffer[], size_t aBufferLen)
{
	size_t index = 0;
	int in;
	unsigned char read_digit = 0, read_white = 0;

	while ((in = getchar()) != EOF) {
		if ('0' <= in && in <= '9') {
			if (read_white) {
				if (++index >= aBufferLen) {
					break;
				}
			}
			if (!read_digit) {
				aBuffer[index] = 0;
			}
			aBuffer[index] *= 10;
			aBuffer[index] += in - '0';

			read_white = 0;
			read_digit = 1;
		} else if (in == ' ' || in == '\t') {
			read_white = 1;
			read_digit = 0;
		} else if (in == '\n') {
			break;
		}
	}
} 


node_t  sums[MAX_N];
node_t* sumsBegin;
unsigned int input[MAX_N];

#define DOUBLE_LINKED_LIST_INIT(__a, __s, __n) \
{ \
	__s = __a; \
	__a[0].prev = NULL; __a[__n - 1].next = NULL; \
	for (int i = 1; i < __n; i++) { \
		__a[i - 1].next = &__a[i]; \
		__a[i].prev = &__a[i - 1]; \
	} \
}

#define DOUBLE_LINKED_LIST_DELETE_NODE(__node, __s) \
{ \
	if (__node->prev != NULL) __node->prev->next = __node->next; \
	else __s = __node->next; \
	if (__node->next != NULL) __node->next->prev = __node->prev; \
}

void resolve(int n)
{
	unsigned int concatenationCost = 0;
	unsigned int bracketsNeeded = 0;

	DOUBLE_LINKED_LIST_INIT(sums, sumsBegin, n - 1);

	for (int i = 0; i < n - 1; i++) {
		sums[i].l = input[i];
		sums[i].r = input[i + 1];
		sums[i].s = sums[i].l + sums[i].r;
	}

	while (sumsBegin->next != NULL) 
	{
		node_t* minSum = sumsBegin;
		node_t* curSum = sumsBegin->next;

		while (curSum != NULL) {
			if (curSum->s < minSum->s) {
				minSum = curSum;
			}
			curSum = curSum->next;
		}

		concatenationCost += minSum->s;
		if (minSum->prev != NULL) {
			minSum->prev->r = minSum->s;
			minSum->prev->s = minSum->prev->l + minSum->prev->r;
			bracketsNeeded++;
		}
		if (minSum->next != NULL) {
			minSum->next->l = minSum->s;
			minSum->next->s = minSum->next->l + minSum->next->r;
		}

		DOUBLE_LINKED_LIST_DELETE_NODE(minSum, sumsBegin);
	}

	concatenationCost += sumsBegin->s;

	printf("%u %u\n", concatenationCost, bracketsNeeded);
}


int main()
{
	int d, n;

	scanf("%d", &d);
	while (d--) {
		scanf("%d\n", &n);
		scanfLineToUnsignedIntArray(input, n);
		resolve(n);
	}
	return 0;
}
