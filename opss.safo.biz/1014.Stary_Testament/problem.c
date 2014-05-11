#include <stdio.h>
#include <string.h>

#define MAX_ALPHABET_LEN (126 - 33 + 1)
#define MAX_LINE_LEN 32

int main()
{
	char a[MAX_ALPHABET_LEN + 2], t[256], in[MAX_LINE_LEN + 2], *b, *e;
	int n;

	fgets(a, sizeof(a), stdin);

	b = a;
	e = a + strlen(a) - 1;
	*(e--) = 0;

	while (b <= e) {
		t[(int)*b] = *e;
		t[(int)*e] = *b;
		b++; e--;
	}
	t['\n'] = 0;

	scanf("%d\n", &n);

	while (n--) {
		fgets(in, sizeof(in), stdin);
		b = in;
		do {
			*b = t[(int)*b];
		} while (*(++b));
		puts(in);
	}

	return 0;
}
