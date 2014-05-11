#include <cstdio>
#include <map>
#include <list>

using namespace std;

#define MAX_PROVINCES       30000
#define MAX_PROVINCES_LOG_2 (15 + 1)
#define MAX_CITIES          10

// size: 30kB
unsigned char cityCount[MAX_PROVINCES];
// size: 12MB
typedef unsigned short HighwayArray[MAX_CITIES][MAX_CITIES];
//unsigned short highway[2 * (MAX_PROVINCES - 1)][MAX_CITIES][MAX_CITIES];
HighwayArray highway[2 * (MAX_PROVINCES - 1)];
map<int, map<int, int> > shortcuts;


unsigned short shortcutBegin[MAX_PROVINCES][MAX_PROVINCES_LOG_2];
unsigned short shortcutEnd[MAX_PROVINCES][MAX_PROVINCES_LOG_2];


/**
 *
 * A: rows cityCount[provinceA]
 * A: cols cityCount[provinceB]
 * B: rows cityCount[provinceB]
 * B: cols cityCount[provinceC]
 *
 * C: rows cityCount[provinceA]
 * C: cols cityCount[provinceC]
 */ 
void calcDistanceMatrix(const HighwayArray *AB, const HighwayArray *BC, HighwayArray *AC, 
		int cityCountA, int cityCountB, int cityCountC, int aModulator)
{
	int a, b, result;

	for (int cityA = 0; cityA < cityCountA; cityA++) {
		for (int cityC = 0; cityC < cityCountC; cityC++) {
			result = 0;
			for (int cityB = 0; cityB < cityCountB; cityB++) {
				a = (*AB)[cityA][cityB];
				b = (*BC)[cityB][cityC];
				result += a * b;
				result %= aModulator;
			}
			(*AC)[cityA][cityC] = result;
#ifdef _DEBUG
			printf("calcDistanceMatrix [%d x %d] [%d]\n", cityA, cityC, result);
#endif
		}
	}
}

/**
 *
 * A: rows cityCount[provinceA]
 * A: cols cityCount[provinceB]
 * B: rows cityCount[provinceB]
 * B: cols cityCount[provinceC]
 *
 * C: rows cityCount[provinceA]
 * C: cols cityCount[provinceC]
 */ 
void calcDistanceMatrix(int provinceA, int provinceB, int provinceC, HighwayArray *C, int aModulator)
{
	int cityCountA = cityCount[provinceA];
	int cityCountB = cityCount[provinceB];
	int cityCountC = cityCount[provinceC];

	HighwayArray *A = &highway[shortcuts[provinceA][provinceB]];
	HighwayArray *B = &highway[shortcuts[provinceB][provinceC]];

#ifdef _DEBUG
	printf("calcDistanceMatrix [%d-%d x %d-%d = %d-%d]\n", 
			provinceA, provinceB, provinceB, provinceC, provinceA, provinceC);
#endif
	calcDistanceMatrix(A, B, C, cityCountA, cityCountB, cityCountC, aModulator);
}


/**
 */
void updateRouteTable(int aSrcProvince, int aSrcCity, int aDstCity, int aRouteCount, int aModulator, int aProvinceCount)
{
	highway[aSrcProvince][aSrcCity][aDstCity] = aRouteCount % aModulator;
	for (int i = 1; shortcutEnd[aSrcProvince][i] < aProvinceCount; i++) {
		int provinceA = shortcutBegin[aSrcProvince][i];
		int provinceC = shortcutEnd[aSrcProvince][i];
		int provinceB = (provinceA + provinceC) / 2;
#ifdef _DEBUG
		printf("updateRouteTable [%d - %d]\n", 
				shortcutBegin[aSrcProvince][i], shortcutEnd[aSrcProvince][i]);
#endif
		calcDistanceMatrix(provinceA, provinceB, provinceC, &highway[shortcuts[provinceA][provinceC]], aModulator);
	}
}


/**
 */
int queryRouteTable(int aSrcProvince, int aSrcCity, int aDstProvince, int aDstCity, int aModulator) 
{
	int provinceA = aSrcProvince, provinceB = aDstProvince, provinceC;
	int provinceLeap = 0;

	list<int> provinceList;

#ifdef _DEBUG
	printf("queryRouteTable: [%d:%d - %d:%d]\n", aSrcProvince, aSrcCity, aDstProvince, aDstCity);
#endif
	while (provinceA < provinceB) {
		provinceList.push_back(provinceA);

		while (shortcutBegin[provinceA][provinceLeap] == provinceA && shortcutEnd[provinceA][provinceLeap] <= provinceB) {
			provinceLeap++;
		}

		while (shortcutEnd[provinceA][provinceLeap] > provinceB) {
			provinceLeap--;
		}

		provinceA = shortcutEnd[provinceA][provinceLeap];
	}

	provinceList.push_back(provinceA);

	HighwayArray C, tmp;

	provinceA = provinceList.front(); provinceList.pop_front();
	provinceB = provinceList.front(); provinceList.pop_front();

	// maximal size of useful data in matrix for roadmap from city 'A'
	int arraySizeA = MAX_CITIES * cityCount[provinceA] * sizeof(highway[0][0][0]);

	memset(C, 0, sizeof(C));
	memset(tmp, 0, sizeof(tmp));
	memcpy(C, highway[shortcuts[provinceA][provinceB]], arraySizeA);

	while (!provinceList.empty()) {
		memcpy(tmp, C, arraySizeA);
		provinceC = provinceList.front(); provinceList.pop_front();

#ifdef _DEBUG
		printf("queryRouteTable [%d:%d x %d:%d]\n", provinceA, provinceB, provinceB, provinceC);
#endif

		calcDistanceMatrix(&tmp, &highway[shortcuts[provinceB][provinceC]], &C,
				cityCount[provinceA], cityCount[provinceB], cityCount[provinceC], aModulator);

		provinceB = provinceC;
	}

	return C[aSrcCity][aDstCity];
}



/**
 */
void initialize(int aModulator, int aProvinceCount)
{
	int distance = 1;
	for (int i = 0; i < MAX_PROVINCES_LOG_2; i++) {
		for (int j = 0; j < aProvinceCount; j++) {
			shortcutBegin[j][i] = j - j % distance;
			shortcutEnd[j][i] = shortcutBegin[j][i] + distance;

#ifdef _DEBUG
			printf("initialize: province [%d], level [%d], begin [%d], end [%d]\n",
					j, i, shortcutBegin[j][i], shortcutEnd[j][i]);
#endif
		}
		distance <<= 1;
	}

	int shortcutOffset = aProvinceCount - 1;

	for (int iA = 2; iA < aProvinceCount; iA *= 2) {
		for (int iB = 0; iB < aProvinceCount - iA; iB += iA) {
			int provinceA = iB, provinceB = iB + iA / 2, provinceC = iB + iA;

			calcDistanceMatrix(provinceA, provinceB, provinceC, &highway[shortcutOffset], aModulator);
			shortcuts[provinceA][provinceC] = shortcutOffset++;
		}
	}
}



int main()
{
	unsigned short d, n;
	int i, j, k, r;
	char c;

	scanf("%hu%hu", &d, &n);

	for (int i = 0; i < n; i++) {
		scanf("%hhu", &cityCount[i]);
	}

	for (int i = 0; i < n - 1; i++) {
		for (j = 0; j < cityCount[i]; j++) {
			for (k = 0; k < cityCount[i + 1]; k++) {
				scanf("%d", &r);
				highway[i][j][k] = r % d;
			}
		}
		shortcuts[i][i + 1] = i;
	}

	initialize(d, n);

	do {
		scanf("%c %d %d %d %d", &c, &k, &i, &j, &r);

		switch (c) {
			case 'q':
				printf("%d\n", queryRouteTable(k - 1, i - 1, j - 1, r - 1, d));
				break;

			case 'u':
				updateRouteTable(k - 1, i - 1, j - 1, r, d, n);
				break;
		}
	} while (c != 'e');

	

	return 0;
}
