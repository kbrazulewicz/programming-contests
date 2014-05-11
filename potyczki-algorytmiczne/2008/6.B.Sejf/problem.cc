#include <iostream>
#include <stdarg.h>
using namespace std;

#undef DEBUG

static const int MAX_N = 1000000;
static const int MAX_M = 1000000;

unsigned char passphrase[MAX_M + 2];
unsigned int shift[MAX_N];


void scanfLineToIntArray(unsigned int aBuffer[], int aBufferLen)
{
	int index = 0;
	int in;
	char read_digit = 0;
	char read_white = 0;

	while ((in = getchar()) != EOF) {
		if ('0' <= in && in <= '9') {
			if (read_white) {
				index++;
				if (index >= aBufferLen) {
					break;
				}
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

/** 
 * Same suffix at offset as at nlen, but the preceding character differs
 * (if that position is still within needle)
 */
static int suffix_match(const unsigned char *needle, size_t nlen, size_t offset, size_t suffixlen) 
{
	if (offset > suffixlen)
		return needle[offset - suffixlen - 1] != needle[nlen - suffixlen - 1] &&
			memcmp(needle + nlen - suffixlen, needle + offset - suffixlen, suffixlen) == 0;
	else
		return memcmp(needle + nlen - suffixlen, needle, offset) == 0;
}

/** 
 * Returns a pointer to the first occurrence of "needle"
 * within "haystack", or NULL if not found.
 */
const unsigned char* string_search_BoyerMoore(
		const unsigned char* haystack, size_t hlen, 
		const unsigned char* needle,   size_t nlen)
{
#ifdef DEBUG
	printf("string_search_BoyerMoore: entry hlen [%d], nlen [%u]\n", hlen, nlen);
#endif

	if (nlen > hlen || nlen <= 0 || haystack == NULL || needle == NULL) 
		return NULL;

	size_t *skip = new size_t[nlen];
	ssize_t occ[UCHAR_MAX + 1];

	// Preprocess #1: init occ[]

	// Initialize the table to default value
	for (size_t i = 0; i < UCHAR_MAX + 1; ++i)
		occ[i] = -1;

	// Then populate it with the analysis of the needle
	// But ignoring the last letter 
	for (size_t i = 0; i < nlen - 1; ++i)
		occ[needle[i]] = i;

#ifdef DEBUG
	printf("string_search_BoyerMoore: initialization 1 finished\n");

	for (size_t i = 0; i < UCHAR_MAX + 1; ++i) {
		if (occ[i] < nlen) {
			printf("string_search_BoyerMoore: occ[%c] = [%u]\n", (char)i, occ[i]);
		}
	}
#endif


	// Preprocess #2: init skip[]
	{
		int f = 0, g = 0;
		size_t *suff = (size_t*) calloc(nlen, sizeof(size_t));

		suff[nlen - 1] = nlen;
		g = nlen - 1;
		for (int i = nlen - 2; i >= 0; --i) {
			if (i > g && suff[i + nlen - 1 - f] < i - g)
				suff[i] = suff[i + nlen - 1 - f];
			else {
				if (i < g) 
					g = i;
				f = i;
				while (g >= 0 && needle[g] == needle[g + nlen - 1 - f])
					--g;
				suff[i] = f - g;
			}
		}

#ifdef DEBUG_2
		printf("string_search_BoyerMoore: initialization 2 suff array finished\n");

		for (size_t i = 0; i < nlen; ++i) {
			printf("string_search_BoyerMoore: suff[%u] = [%u]\n", i, suff[i]);
		}
#endif

		for (size_t i = 0; i < nlen; ++i)
			skip[i] = nlen;

		int j = 0;
		for (int i = nlen - 1; i >= 0; --i) {
			if (suff[i] == i + 1) {
				for (; j < nlen - 1 - i; ++j) {
					if (skip[j] == nlen) {
						skip[j] = nlen - 1 - i;
					}
				}
			}
		}

		for (size_t i = 0; i < nlen - 1; ++i)
			skip[nlen - 1 - suff[i]] = nlen - 1 - i;

		free(suff);
	}


#ifdef DEBUG
	printf("string_search_BoyerMoore: initialization 2 finished\n");
#endif

	// search
	int hpos = 0, npos = 0;
	while (hpos <= hlen - nlen) {
#ifdef DEBUG
		printf("string_search_BoyerMoore: search A npos [%d], hpos [%d]\n", npos, hpos);
#endif
		for (npos = nlen - 1; npos >= 0 && needle[npos] == haystack[npos + hpos]; --npos);
		if (npos < 0) {
			delete[] skip;
			return haystack + hpos;
		} else {
#ifdef DEBUG
			printf("string_search_BoyerMoore: search B npos [%d], hpos [%d], skip[] = [%u], occ[] = [%u]\n", 
					npos, hpos, skip[npos], (size_t) (npos - occ[haystack[npos + hpos]]));
#endif
			if (occ[haystack[npos + hpos]] > npos) {
				hpos += skip[npos];
			} else {
				hpos += max(skip[npos], (size_t) (npos - occ[haystack[npos + hpos]]));
			}
		}
#ifdef DEBUG
		printf("string_search_BoyerMoore: search C npos [%d], hpos [%d], skip[npos] = [%u]\n", npos, hpos, skip[npos]);
#endif
	}

	delete[] skip;
	return NULL;
}


int main()
{
	int n, m;
	size_t p, r, rr;

	scanf("%d %d\n", &n, &m);
	fgets((char*)passphrase, sizeof(passphrase), stdin);
	scanfLineToIntArray(shift, n);

#ifdef DEBUG
	printf("Data read: n[%d], m[%d]\n", n, m);
#endif

	// check for passphrase period
	const unsigned char* needle = string_search_BoyerMoore(passphrase + 1, m - 1, passphrase, m / 2);
	if (needle == NULL) {
		p = m;
#ifdef DEBUG
		printf("Passphrase [%.*s] is not looping\n", m, passphrase);
#endif
	} else {
		p = needle - passphrase;
#ifdef DEBUG
		printf("Passphrase [%.*s] is looping at position [%d]\n", m, passphrase, p);
#endif
	}

	r = UINT_MAX;

	for (size_t j = 0; j < p; j++) {
		rr = 0;
		// calculate cumulative shift
		for (size_t i = 0; i < n; i++) {
			size_t ii = (shift[i] + j) % p;
			rr += min(ii, p - ii);
		}

#ifdef DEBUG
		printf("Result for shift[%u] is [%u]\n", j, rr);
#endif

		r = min(r, rr);
	}

	printf("%d\n", r);

	return 0;
}
