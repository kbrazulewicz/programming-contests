#include <stdio.h>

int main()
{
	int i, n, t1, ta, tb;
	int gradPlus = 0, gradMinus = 0;

	scanf("%d %d", &n, &t1);
	ta = t1;

	for (i = 2; i <= n; i++)
	{
		scanf("%d", &tb);
		if (tb > ta) gradPlus++;
		if (tb < ta) gradMinus++;
		ta = tb;
	}

	tb = t1;
	if (tb > ta) gradPlus++;
	if (tb < ta) gradMinus++;

	puts((gradPlus <= 1 || gradMinus <= 1) ? "TAK" : "NIE");

	return 0;
}
