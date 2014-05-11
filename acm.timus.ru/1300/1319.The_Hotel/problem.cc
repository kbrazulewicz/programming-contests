/* @JUDGE_ID: 16232QS XXXX C++ */

#include <iostream>
#include <string>
using namespace std;


void labelBox(int aBox[], int aSize)
{
	int label = 1;
	int x1 = 0, y1 = 0;

	do {
		int x2 = x1, y2 = y1;

		do {
			aBox[x2 + y2 * aSize] = label++;
			x2++; y2--;
		} while (x2 < aSize && y2 >= 0);


		if (y1 < aSize - 1) {
			y1++;
		} else {
			x1++;
		}

	} while (x1 < aSize && y1 < aSize);
}

void printBox(int aBox[], int aSize)
{
	for (int j = 0; j < aSize ; j++) {
		for (int i = aSize - 1; i >= 0; i--) {
			cout << aBox[i * aSize + j] << " ";
		}
		cout << endl;
	}
}

int main()
{
	int n;

	cin >> n;

	int* box = new int[n * n];

	labelBox(box, n);
	printBox(box, n);

	delete[](box);

	return 0;
}
