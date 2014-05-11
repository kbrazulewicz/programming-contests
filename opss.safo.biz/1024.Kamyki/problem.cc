#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

static const int MAX_I = 1000;

int main()
{
	int c;

	cin >> c;

	for (int i = 0; i < c; i++) {
		int n, j = 0;
		int a, b;
		vector<int> queue;

		cin >> n;
		queue.reserve(min(MAX_I, n));

		while (n) {
			cin >> a;

			if (j > 0) queue.insert(queue.end(), b - a, j);

			n -= a;
			b = a;
			j++;
		}
		queue.insert(queue.end(), a, j);

		reverse_copy(queue.begin(), queue.end(), ostream_iterator<int>(cout, " "));
		cout << endl;
	}

	return 0;
}
