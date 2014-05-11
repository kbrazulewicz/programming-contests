#include <iostream>
using namespace std;

unsigned int sArray[5] = {1, 1, 2, 6, 4};

int main() 
{
	unsigned int n;

	cin >> n;
	cout << ((n < 5) ? sArray[n] : 0);
	return 0;
}
