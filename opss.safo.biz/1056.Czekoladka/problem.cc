#include <iostream>
#include <string>
using namespace std;

int main()
{
	int d, c;

	cin >> d;
	while (d--) {
		cin >> c;

		bool lastForAla = false;
		while (c--) {
			int a, b;
			cin >> a >> b;

			bool isOdd = (a % 2) && (b % 2);
			if (isOdd) lastForAla = !lastForAla;
		}

		printf("%d\n", lastForAla ? 0 : 1);
	}
	return 0;
}
