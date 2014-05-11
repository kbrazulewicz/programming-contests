#include <stdio.h>

int main()
{
	double a = 1e15;
	double b = a + 1;
	double c = b - a;
	
	printf("%f\n", c);
	
	return 0;
}
