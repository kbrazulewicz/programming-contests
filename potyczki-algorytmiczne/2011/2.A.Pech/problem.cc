#include <iomanip>
#include <iostream>
#include <cmath>
using namespace std;

#undef DEBUG

double pech(int s, int w, int k)
{
	double distance = s;
	double water = w;
	int rounds = ceil(water / k);

	while (distance > 0)
	{
		double projectedWaterAfterStep = k * (rounds - 1);
		double step = (water - projectedWaterAfterStep) / (rounds * 2 - 1);

		if (distance > step) {
			water = projectedWaterAfterStep;
			distance -= step;
			rounds--;
		} else {
			water -= distance * (rounds * 2 - 1);
			break;
		}

#ifdef DEBUG
		cout << "Distance to go " << distance << "; step " << step << "; water " << water << endl;
#endif
	}

	return water;
}


int main()
{
	int s, w, k;

	cin >> s >> w >> k;

	cout << setiosflags(ios::fixed) << setprecision(3) << pech(s, w, k) << endl;

	return 0;
}
