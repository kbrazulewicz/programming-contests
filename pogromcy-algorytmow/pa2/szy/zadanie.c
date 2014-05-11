#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 0

#if DEBUG
#define PRINTF(x) printf x
#else
#define PRINTF(x)
#endif

#define MIN(a,b) a < b ? a : b;
#define MAX(a,b) a > b ? a : b;

#define MAX_KEYS	40
#define MAX_BITS	(sizeof(int) << 3)

typedef struct {
	unsigned int value;
	int index;
} Key_t;

Key_t gKeys[MAX_KEYS];
int gKeysNo;
unsigned int gEncoded;

void dec2bin(unsigned int value, int width, char* result)
{
	memset(result, '0', width);
	result[width] = '\0';

	while (value && width) {
		result[--width] = (value % 2) + '0';
		value >>= 1;
	}
}

int keySortAsc(const void* a, const void* b)
{
	return ((const Key_t*)a)->value - ((const Key_t*)b)->value;
}

int keySortDesc(const void* a, const void* b)
{
	return ((const Key_t*)b)->value - ((const Key_t*)a)->value;
}


void greedy(char *result)
{
	Key_t keys[MAX_KEYS];
	unsigned int spaceLeft;
	int i;

	memcpy(keys, gKeys, sizeof(gKeys));
	qsort(keys, gKeysNo, sizeof(keys[0]), keySortDesc);

	memset(result, '1', gKeysNo);
	result[gKeysNo] = 0;

	spaceLeft = gEncoded;

	for (i = 0; i < gKeysNo; i++) {
		if (spaceLeft > keys[i].value) {
			spaceLeft -= keys[i].value;
		} else {
			result[keys[i].index] = '0';
		}
	}
}

void diophant(char *result)
{
	Key_t keys[MAX_KEYS];
	Key_t sums[MAX_KEYS];
	unsigned int sum;
	int i, k, r, s;
	int stackR[MAX_KEYS*20], stackSum[MAX_KEYS*20], stackT[MAX_KEYS*20][MAX_KEYS + 2];
	int trace[MAX_KEYS + 1];
	unsigned int x;

	memcpy(keys, gKeys, sizeof(gKeys));
	qsort(keys, gKeysNo, sizeof(keys[0]), keySortAsc);

	memset(result, '0', gKeysNo);
	result[gKeysNo] = 0;

	/* set sums array */
	sums[0].value = keys[0].value;
	for (i = 1; i < gKeysNo; i++) {
		sums[i].value = sums[i - 1].value + keys[i].value;
		stackT[i][0] = 0;
	}

	stackSum[0] = gEncoded;
	stackR[0]	= gKeysNo - 1;
	s = 1;
	x = 0;

	while (s) {
		s--;
		sum = stackSum[s];
		r	= stackR[s];
		PRINTF(("Stack trace of size %d\n", stackT[s][0]));
		memcpy(trace, stackT[s], sizeof(trace));
		PRINTF(("Local trace of size %d\n", trace[0]));

		PRINTF(("%d: Trace: %d\n", s, *trace));

		if (!(x++ % 4096)) PRINTF(("%d  \r", s));

		for (k = 0; sums[k].value < sum; k++);
		if (sums[k].value == sum) {
			for (i = 0; i <= k; i++) {
					trace[++(*trace)] = keys[i].index;
					PRINTF(("Key: %d\n", keys[i].value));
			}
			break;
		}
		for (;keys[r].value > sum; r--);
		if (keys[r].value == sum) {
			trace[++(*trace)] = keys[r].index;
			PRINTF(("Key: v %d, i %d\n", keys[r].value, keys[r].index));
			break;
		}
		for (i = k; i <= r && (keys[0].value <= sum - keys[i].value); i++) {
			stackSum[s] = sum - keys[i].value;
			stackR[s]	= i - 1;
			PRINTF(("Src trace of size %d\n", trace[0]));
			memcpy(stackT[s], trace, sizeof(trace));
			PRINTF(("Dst trace of size %d\n", stackT[s][0]));
			stackT[s][++stackT[s][0]] = keys[i].index;
			PRINTF(("Dst trace of size %d\n", stackT[s][0]));
			s++;
		}
	}

	for (i = 1; i <= trace[0]; i++) {
		PRINTF(("Key: i %d\n", trace[i]));
		result[trace[i]] = '1';
	}
}



int main()
{
	int inputNr, encoded;
	char decoded[MAX_BITS + 1];
	int i;

	scanf("%d%d", &inputNr, &gKeysNo);
	for (i = 0; i < gKeysNo; i++) {
		scanf("%u", &gKeys[i].value);
		gKeys[i].index = i;
	}

	scanf("%ud", &gEncoded);

	/*greedy(decoded);*/
	diophant(decoded);

	encoded = 0;
	for (i = 0; i < gKeysNo; i++) {
		if (decoded[i] == '1') {
			encoded += gKeys[i].value;
		}
	}
	if (encoded == gEncoded) {
		printf("%d bits encryption broken: %s %d\n", gKeysNo, decoded, gEncoded);
	} else {
		dec2bin(gEncoded, gKeysNo, decoded);
		printf("expected: %s %d\n", decoded, gEncoded);
		dec2bin(encoded, gKeysNo, decoded);
		printf("got:      %s %d\n", decoded, encoded);
	}
	
	return 0;
}
