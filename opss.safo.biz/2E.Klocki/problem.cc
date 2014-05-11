#include <iostream>
#include <string>
using namespace std;

#include <math.h>

static const int gMaxBlockIndex = 11;
static const int gMaxBlockScore =   1000;
static const int gMinBlockScore = - 1000;
int gScore[gMaxBlockIndex + 1][gMaxBlockIndex + 1];



int main()
{
	int c, n, p;

	cin >> c;
	while (c--) {
		int blockIndex;
		int score;

		cin >> n;

		blockIndex = (sqrt(1 + 8 * n) - 1) / 2;
		for (int i = 1; i <= blockIndex; i++) {
			for (int j = i; j <= blockIndex; j++) {
				cin >> gScore[i][j];
				gScore[j][i] = gScore[i][j];
			}
		}

		int scoreMin = blockIndex * gMaxBlockScore, scoreMax = blockIndex * gMinBlockScore;
		cin >> p;

		if (p > blockIndex) {
			scoreMax = scoreMin = 0;
		} else {
			int perm[gMaxBlockIndex + 1];
			int c[gMaxBlockIndex];
			int N = blockIndex - 1;

			for (int n = 1, j = 1; n <= blockIndex; n++) {
				if (n != p) {
					perm[j] = n;
					c[j] = 1;
					j++;
				}
			}
			perm[0] = p;
			perm[blockIndex] = p;

			score = 0;
			for (int i = 0; i <= N; i++) {
				score += gScore[perm[i]][perm[i + 1]];
			}
			scoreMin = min(scoreMin, score);
			scoreMax = max(scoreMax, score);

			for (int n = 1; n <= N;) {
				if (c[n] < n) {
					int xL, t;
					xL = n % 2 ? 1 : c[n];

					score -= gScore[perm[xL - 1]][perm[xL]];
					score -= gScore[perm[xL]][perm[xL + 1]];
					score -= gScore[perm[n - 1]][perm[n]];
					score -= gScore[perm[n]][perm[n + 1]];

					t = perm[xL]; perm[xL] = perm[n]; perm[n] = t;

					score += gScore[perm[xL - 1]][perm[xL]];
					score += gScore[perm[xL]][perm[xL + 1]];
					score += gScore[perm[n - 1]][perm[n]];
					score += gScore[perm[n]][perm[n + 1]];

					scoreMin = min(scoreMin, score);
					scoreMax = max(scoreMax, score);

					c[n]++; 
					n = 1;

				} else c[n++] = 1;
			}

		}

		cout << scoreMin << " " << scoreMax << endl;

	}

	return 0;
}
