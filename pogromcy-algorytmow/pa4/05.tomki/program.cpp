#include <iostream>

using namespace std;

int ax, ay, bx, by;
int minDistance;

int main()
{
	int aL, bL;
	int x = 0, y = 0;
	
	cin >> ax >> ay >> bx >> by;
	aL = abs(ax) + abs(ay);
	bL = abs(bx) + abs(by);

	// longer first - just to have an order here
	if (bL > aL) {
		swap(ax, bx);
		swap(ay, by);
		swap(aL, bL);
	}

	// minDistance initialisation
	minDistance = min(aL, bL);
	if (ax + ay < 0) {
		ax = -ax; ay = -ay; 
	}
	if (bx + by >= 0) {
		bx = -bx; by = -by; 
	}

	int limit = aL;
	int currentValue = 0, aValue, bValue;
	int aD, bD;

	while (currentValue < limit && minDistance != 1) {

		aD = abs(x + ax) + abs(y + ay);
		bD = abs(x + bx) + abs(y + by);

		if ((aD != 0 && aD < bD) || bD == 0) {
			x += ax; y += ay;
		} else {
			x += bx; y += by;
		}

		currentValue = abs(x) + abs(y);
		minDistance = min(minDistance, currentValue);
	}

	cout << minDistance << endl;

	return 0;
}
