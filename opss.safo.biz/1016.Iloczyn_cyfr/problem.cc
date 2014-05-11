#include <iostream>
#include <string>
using namespace std;

int x[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int main()
{
	int n;

	cin >> n;

	if (n == 0) {
		printf("10");
	} else if (n == 1) {
		printf("1");
	} else {
		for (int i = 9; i > 1; i--) {
			while (!(n % i)) {
				x[i]++;
				n /= i;
			}
		}

		if (n == 1) {
			for (int i = 2; i < 10; i++) {
				for (int j = 0; j < x[i]; j++) {
					putchar('0' + i);
				}
			}
		} else {
			printf("-1");
		}
	}
	putchar('\n');
	
	return 0;
}
