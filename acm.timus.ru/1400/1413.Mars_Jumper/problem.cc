#include <cstdio>
#include <math.h>
using namespace std;

static const int MAX_LEN = 1000000;

char buffer[MAX_LEN + 1];

int main()
{
	double x = 0, y = 0, xS = 0, yS = 0;
	char* order;
	bool stop = false;

	order = fgets(buffer, sizeof(buffer), stdin);
	while (!stop) {
		if (*order >= '1' && *order <= '9') {
			switch (*order) {
				case '1': xS--; yS--; break;
				case '2': y--; break;
				case '3': xS++; yS--; break;
				case '4': x--; break;
				case '5': break;
				case '6': x++; break;
				case '7': xS--; yS++; break;
				case '8': y++; break;
				case '9': xS++; yS++; break;
			}
			order++;
		} else {
			stop = true;
		}
	}

	x += xS * sqrt(0.5);
	y += yS * sqrt(0.5);

	printf("%.10f %.10f\n", x, y);
	return 0;
}
