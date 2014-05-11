#include <stdio.h>

#define MIN(a,b) ((a) < (b) ? (a) : (b))

#define MAX_N 10000
#define MAX_Z 20000

typedef struct {
	int p;
	int g;
	int k;
} testimony_t;

testimony_t testimony[MAX_Z];

char liar[MAX_N + 1];
int guiltyOfChoice[MAX_N + 1];
int score[MAX_N + 1];

int testimonyCompare(const void* a, const void* b)
{
	const testimony_t* tA = (const testimony_t*) a;
	const testimony_t* tB = (const testimony_t*) b;

	if (tA->p != tB->p) {
		return tA->p - tB->p;
	}
	if (tA->g != tB->g) {
		return tB->g - tA->g;
	}
	return tA->k - tB->k;
}


void resolve(int n, int z)
{
	int totalGuiltyTestimonies = 0;

	// sort testimonies
	qsort(testimony, z, sizeof(testimony_t), testimonyCompare);

	for (int i = 1; i <= n; guiltyOfChoice[i++] = 0);
	for (int i = 1; i <= n; liar[i++] = 0);
	for (int i = 1; i <= n; score[i++] = 0);

	// find inconsistent testimonies
	for (int i = 0; i < z; i++) {
		int p = testimony[i].p;
		if (!liar[p]) {
			if (testimony[i].g) {
				if (guiltyOfChoice[p] && guiltyOfChoice[p] != testimony[i].k) {
					liar[p] = 1;
				} else {
					guiltyOfChoice[p] = testimony[i].k;
				}
			} else {
				if (guiltyOfChoice[p] && guiltyOfChoice[p] == testimony[i].k) {
					liar[p] = 1;
				}
			}
		}
	}

	// eliminate testimonies from liars, duplicates and 'not guilty' if the same person said 'guilty'
	{
		int newZ = z;
		for (int i = 0; i < z; i++) {
			if (liar[testimony[i].p]) {
				testimony[i].p = n + 1;
				newZ--;
			} else if (i > 0 && testimonyCompare(&testimony[i - 1], &testimony[i]) == 0) {
				testimony[i].p = n + 1;
				newZ--;
			} else if (!testimony[i].g && guiltyOfChoice[testimony[i].p]) {
				testimony[i].p = n + 1;
				newZ--;
			}
		}
		qsort(testimony, z, sizeof(testimony_t), testimonyCompare);
		z = newZ;
	}

	// calculate 'score'
	for (int i = 0; i < z; i++) {
		if (testimony[i].g) {
			score[testimony[i].k]--;
		} else {
			score[testimony[i].k]++;
		}
	}
	int minScore = n;
	for (int i = 1; i <= n; i++) {
		minScore = MIN(minScore, score[i]);
	}

	// print results
	char firstResult = 1;
	for (int i = 1; i <= n; i++) {
		if (score[i] == minScore) {
			printf(firstResult ? "%d" : " %d", i);
			firstResult = 0;
		}
	}
	printf("\n");


#if 0
	for (int i = 0; i < z; i++) {
		if (!liar[testimony[i].p - 1]) {
			printf("[%d] claims that [%d] is [%s]\n", 
					testimony[i].p, 
					testimony[i].k, 
					testimony[i].g ? "GUILTY" : "NOT GUILTY");
		}
	}
#endif
}


int main()
{
	int d, n, z, p, k;
	int g;
	char c;

	scanf("%d", &d);

	while (d--) {
		scanf("%d%d", &n, &z);
		for (int i = 0; i < z; i++) {
			scanf("%d %c %d", &p, &c, &k);
			switch (c) {
				case 'W': g = 1; break;
				case 'P':
					g = testimony[k - 1].g ? 1 : 0;
					k = testimony[k - 1].k;
					break;
				case 'F':
					g = testimony[k - 1].g ? 0 : 1;
					k = testimony[k - 1].k;
					break;
			}
			testimony[i].p = p;
			testimony[i].g = g;
			testimony[i].k = k;
		}
		resolve(n, z);
	}
	return 0;
}
