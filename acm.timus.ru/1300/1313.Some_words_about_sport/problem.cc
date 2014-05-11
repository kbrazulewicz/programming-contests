/* @JUDGE_ID: 16232QS XXXX C++ */

#include <iostream>
#include <string>
using namespace std;


void writePixels(int aBox[], int aSize)
{
	int x1 = 0, y1 = 0;

	do {
		int x2 = x1, y2 = y1;

		do {
			cout << aBox[x2 + y2 * aSize] << " ";
			x2++; y2--;
		} while (x2 < aSize && y2 >= 0);


		if (y1 < aSize - 1) {
			y1++;
		} else {
			x1++;
		}

	} while (x1 < aSize && y1 < aSize);
}

void readPixels(int aBox[], int aSize)
{
	for (int i = 0; i < aSize; i++) {
		for (int j = 0; j < aSize ; j++) {
			cin >> aBox[i * aSize + j];
		}
	}
}

int main()
{
	int n;

	cin >> n;

	int* box = new int[n * n];

	readPixels(box, n);
	writePixels(box, n);

	delete[](box);

	return 0;
}
