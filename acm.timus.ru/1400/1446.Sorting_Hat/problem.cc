#include <iostream>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

static const int MAX_N = 1000;
static const int MAX_L = 200;

char gNames[MAX_N][MAX_L + 2];

vector<char *> slytherin;
vector<char *> hufflepuff;
vector<char *> gryffindor;
vector<char *> ravenclaw;

int main()
{
	int n;
	char house[16];

	scanf("%d\n", &n);
	for (int i = 0; i < n; i++) {
		char* name = fgets(gNames[i], MAX_L + 2, stdin);
		fgets(house, sizeof(house), stdin);

		if (house[0] == 'S') {
			slytherin.push_back(name);
		} else if (house[0] == 'H') {
			hufflepuff.push_back(name);
		} else if (house[0] == 'G') {
			gryffindor.push_back(name);
		} else if (house[0] == 'R') {
			ravenclaw.push_back(name);
		}
	}

	cout << "Slytherin:" << endl;
	copy(slytherin.begin(), slytherin.end(), ostream_iterator<char*>(cout, ""));
	cout << endl;
	
	cout << "Hufflepuff:" << endl;
	copy(hufflepuff.begin(), hufflepuff.end(), ostream_iterator<char*>(cout, ""));
	cout << endl;
	
	cout << "Gryffindor:" << endl;
	copy(gryffindor.begin(), gryffindor.end(), ostream_iterator<char*>(cout, ""));
	cout << endl;
	
	cout << "Ravenclaw:" << endl;
	copy(ravenclaw.begin(), ravenclaw.end(), ostream_iterator<char*>(cout, ""));
	
	return 0;
}
