#include <cstdio>
#include <string>
using namespace std;

#undef __DEBUG__

static const int MAX_H = 30;
static const int MAX_N = 50000;

static const unsigned int pow2[] = {
	1 << 0x00, 1 << 0x01, 1 << 0x02, 1 << 0x03, 1 << 0x04, 1 << 0x05, 1 << 0x06, 1 << 0x07,
	1 << 0x08, 1 << 0x09, 1 << 0x0A, 1 << 0x0B, 1 << 0x0C, 1 << 0x0D, 1 << 0x0E, 1 << 0x0F,
	1 << 0x10, 1 << 0x11, 1 << 0x12, 1 << 0x13, 1 << 0x14, 1 << 0x15, 1 << 0x16, 1 << 0x17,
	1 << 0x18, 1 << 0x19, 1 << 0x1A, 1 << 0x1B, 1 << 0x1C, 1 << 0x1D, 1 << 0x1E, 1 << 0x1F,
};

static const unsigned int mask0LH[] = {
	0xFFFFFFFF, 0xFFFFFFFE, 0xFFFFFFFC, 0xFFFFFFF8, 0xFFFFFFF0, 0xFFFFFFE0, 0xFFFFFFC0, 0xFFFFFF80,
	0xFFFFFF00, 0xFFFFFE00, 0xFFFFFC00, 0xFFFFF800, 0xFFFFF000, 0xFFFFE000, 0xFFFFC000, 0xFFFF8000,
	0xFFFF0000, 0xFFFE0000, 0xFFFC0000, 0xFFF80000, 0xFFF00000, 0xFFE00000, 0xFFC00000, 0xFF800000,
	0xFF000000, 0xFE000000, 0xFC000000, 0xF8000000, 0xF0000000, 0xE0000000, 0xC0000000, 0x80000000,
};
static const unsigned int mask1HL[] = {
	0x80000000, 0xC0000000, 0xE0000000, 0xF0000000, 0xF8000000, 0xFC000000, 0xFE000000, 0xFF000000,
	0xFF800000, 0xFFC00000, 0xFFE00000, 0xFFF00000, 0xFFF80000, 0xFFFC0000, 0xFFFE0000, 0xFFFF0000,
	0xFFFF8000, 0xFFFFC000, 0xFFFFE000, 0xFFFFF000, 0xFFFFF800, 0xFFFFFC00, 0xFFFFFE00, 0xFFFFFF00,
	0xFFFFFF80, 0xFFFFFFC0, 0xFFFFFFE0, 0xFFFFFFF0, 0xFFFFFFF8, 0xFFFFFFFC, 0xFFFFFFFE, 0xFFFFFFFF,
};

struct Node {
	unsigned int level;
	unsigned int value;

	bool isParent(const Node* aNode) const
	{
		return (this->level <= aNode->level) &&
			(this->value == (aNode->value & mask1HL[this->level - 1]));
	}
};

struct Node node[MAX_N];
struct Node* nodePtr[MAX_N];

int nodePtrCompare(const void* a, const void* b) 
{
	const struct Node* nodeA = *((struct Node**) a);
	const struct Node* nodeB = *((struct Node**) b);

	if (nodeA->value == nodeB->value) {
		if (nodeA->level > nodeB->level) return 1;
		if (nodeA->level < nodeB->level) return -1;
		return 0;
	} else {
		if (nodeA->value > nodeB->value) return 1;
		if (nodeA->value < nodeB->value) return -1;
		return 0;
	}
}


void enterNumber(Node* aNode)
{
	static char line[MAX_H + 3];
	char* c = line;

	aNode->level = 0;
	aNode->value = 0;

	fgets(line, sizeof(line), stdin);

	do {
		if (*c == 'b') {
			aNode->value |= pow2[aNode->level];
		}
		aNode->level++;
		c++;
	} while (*c == 'a' || *c == 'b');

	aNode->value <<= 32 - aNode->level;
}


int calculate(int aHeight, int aWordCount)
{
	int i, j;

	for (i = 0; i < aWordCount; i++) {
		nodePtr[i] = &node[i];
		enterNumber(nodePtr[i]);
	}

	qsort(&nodePtr, aWordCount, sizeof(nodePtr[0]), nodePtrCompare);

	int leafCount = pow2[aHeight + 1] - 1;
	for (i = 0, j = 0; i < aWordCount; i++) {
		if (i == 0 || !nodePtr[j]->isParent(nodePtr[i])) {
#ifdef __DEBUG__
			printf("%u %x cuts off %d\n", nodePtr[i]->level, nodePtr[i]->value,
					pow2[aHeight - nodePtr[i]->level + 1] - 1);
#endif
			leafCount -= pow2[aHeight - nodePtr[i]->level + 1] - 1;
			j = i;
		}
	}

	return leafCount;
}


int main()
{
	int c, h, n;

	scanf("%d", &c);
	while (c--) {
		scanf("%d%d\n", &h, &n);
		printf("%d\n", calculate(h, n));
	}
	return 0;
}
