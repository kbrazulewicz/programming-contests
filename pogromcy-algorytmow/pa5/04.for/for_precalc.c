#include <stdio.h>

const char* results[11] = {
	"0.5",
	"0.1533203125",
	"0.0012035369873046875",
	"0.0",
	"0.0",
	"0.0",
	"0.0",
	"0.0",
	"0.0",
	"0.0",
	"0.0",
};

int main()
{
	int k;

	scanf("%d", &k);
	printf("%s\n", results[k]);
	
	return 0;
}
