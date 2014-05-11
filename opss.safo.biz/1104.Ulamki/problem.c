#include <stdio.h>
#include <stdlib.h>

/**
 * Greatest Common Divisor Euclidean algorithm
 *
 * O(n) complexity (n is the number of digits in the input)
 *
 * needs:
 * #include <stdlib.h>
 */
int greatestCommonDivisor(int a, int b)
{
	int tmp;
	while (b != 0) {
		tmp = a % b;
		a = b;
		b = tmp;
	}

	return abs(a);
}


typedef struct {
	int a;
	int b;
	int c;
} fraction_t;

const char* fraction_scanf(fraction_t *o, const char *input) 
{
	const char *ptr;

	o->a = 0;
	o->b = 0;
	o->c = 1;

    o->a = strtol(input, &ptr, 10);
	if (*ptr != '\0') {
		o->b = strtol(ptr + 1, &ptr, 10);
		if (*ptr == '\0') {
			o->c = o->b;
			o->b = o->a;
			o->a = 0;
		} else {
			o->c = strtol(ptr + 1, &ptr, 10);
		}
	}
}

int fraction_snprintf(char *str, size_t size, const fraction_t *x)
{
	if (x->b == 0) {
		return snprintf(str, size, "%d", x->a);
	} else if (x->a == 0) {
		return snprintf(str, size, "%d/%d", x->b, x->c);
	} else {
		return snprintf(str, size, "%d/%d/%d", x->a, x->b, x->c);
	}
}

void fraction_sum(fraction_t *s, const fraction_t *x, const fraction_t *y) 
{
	int gcd;

	s->a = x->a + y->a;
	s->b = x->b * y->c + y->b * x->c;
	s->c = x->c * y->c;

	if (s->b >= s->c) {
		s->a++;
		s->b -= s->c;
	}

	if (s->b != 0) {
		gcd = greatestCommonDivisor(s->b, s->c);
		s->b /= gcd;
		s->c /= gcd;
	}
}

int main()
{
	int d, i;
	char lineIn[6 * 5 + 5 + 1 + 1];
	char lineOut[128];
	char *xP, *yP, *tP;
	fraction_t s, x, y;

	scanf("%d\n", &d);

	for (i = 0; i < d; i++) {
		fgets(lineIn, sizeof(lineIn), stdin);

		xP = lineIn;
		yP = strchr(lineIn, '+');
		tP = strchr(yP, '\n');
		*(yP++) = '\0';
		if (tP != NULL) {
			*tP = '\0';
		}

		fraction_scanf(&x, xP);
		fraction_scanf(&y, yP);
		fraction_sum(&s, &x, &y);

		fraction_snprintf(lineOut, sizeof(lineOut), &s);
		puts(lineOut);
	}

	return 0;
}
