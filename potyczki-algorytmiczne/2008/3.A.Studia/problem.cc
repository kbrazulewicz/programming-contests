#include <iostream>
#include <iterator>
#include <set>
using namespace std;

#undef DEBUG

static const int MAX_N =         300;
static const int MIN_C = -1000000000;
static const int MAX_C =  1000000000;

long long gain[MAX_N + 1][MAX_N + 1];
char linkMatrix[MAX_N + 1][MAX_N + 1];

int connF[MAX_N + 1][MAX_N];  // connections from X
int connT[MAX_N + 1][MAX_N];  // connections to X

int main()
{
	int n, m;
	int a, b, c, g;

	int iterationCount = 0;
	set<int> queue;
	set<int> result;

	cin >> n >> m;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			gain[i][j] = MIN_C - 1;
		}
	}

	for (int i = 1; i <= m; i++) {
		cin >> a >> b >> c;

		queue.insert(b);
		gain[a][b] = c;
		linkMatrix[a][b] = 1;

		connF[a][++connF[a][0]] = b;
		connT[b][++connT[b][0]] = a;
	}



	while (!queue.empty()) {
		int node = *(queue.begin());
		queue.erase(node);

#if DEBUG
		cout << "Processing [" << node << "]" << endl;
#endif

		for (int ii = 1; ii <= connT[node][0]; ii++) {
			int i = connT[node][ii];
			if (i != node) {
#if DEBUG
				cout << "Checking [" << i << ":" << node << "]" << endl;
#endif
				for (int jj = 1; jj <= connF[node][0]; jj++) {
					int j = connF[node][jj];
					if (j != node) {
						iterationCount++;
						g = gain[i][node] + gain[node][j];
#if DEBUG
						cout << "Extending [" << node << ":" << j << "] gain [" << g << "]" << endl;
#endif
						// register link
						if (linkMatrix[i][j] == 0) {
							linkMatrix[i][j] = 1;
							connF[i][++connF[i][0]] = j;
							connT[j][++connT[j][0]] = i;
						}
						if (gain[i][j] <= 0 && g > gain[i][j]) {

							if (i == j) {
								result.insert(i);
								g = MAX_C;

								for (int kk = 1; kk <= connT[i][0]; kk++) {
									int k = connT[i][kk];

									if (linkMatrix[k][i] && linkMatrix[i][k] && gain[k][k] <= 0) {
										gain[k][k] = MAX_C;
										result.insert(k);
										queue.insert(k);
									}
								}
								for (int kk = 1; kk <= connF[i][0]; kk++) {
									int k = connF[i][kk];

									if (linkMatrix[k][i] && linkMatrix[i][k] && gain[k][k] <= 0) {
										gain[k][k] = MAX_C;
										result.insert(k);
										queue.insert(k);
									}
								}
							}

							gain[i][j] = g;
							queue.insert(j);
#if DEBUG
							cout << "Queueing [" << j << "]" << endl;
#endif
						}
					}
				}
			}
		}
	}

	cout << result.size() << endl;
	copy(result.begin(), result.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	cout << iterationCount << endl;

	return 0;
}
