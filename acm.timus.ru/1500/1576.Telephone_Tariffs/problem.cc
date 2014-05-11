/* @JUDGE_ID: 16232QS 1576 C++ */

#include <iostream>
#include <string>
using namespace std;

int main()
{
	int n1, c1;
	int n2, t2, c2;
	int n3;
	int k;
	int minutes, seconds, totalMinutes = 0;
	int payment[3];

	scanf("%d%d%d%d%d%d%d", &n1, &c1, &n2, &t2, &c2, &n3, &k);

	for (int i = 0; i < k; i++) {
		scanf("%d:%d", &minutes, &seconds);
		if (minutes > 0 || seconds > 6) {
			if (seconds > 0) {
				minutes++;
			}
			totalMinutes += minutes;
		}
	}

	payment[0] = n1 + totalMinutes * c1;
	payment[1] = n2 + ((totalMinutes > t2) ? (totalMinutes - t2) * c2 : 0);
	payment[2] = n3;

	cout 
		<< "Basic:     " << payment[0] << endl
		<< "Combined:  " << payment[1] << endl
		<< "Unlimited: " << payment[2] << endl;

	return 0;
}
