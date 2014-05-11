#include <cstdio>

#include <algorithm>
#include <map>
#include <set>

using namespace std;

#undef _DEBUG

static const int MAX_PLATFORMS  = 25000;
static const int MAX_COORDINATE = 1000000000;

typedef struct
{
	int x1, x2, y1, y2;
} Platform;

typedef map<int, set<int> > WorldOrder;

Platform gPlatform[MAX_PLATFORMS];
WorldOrder worldOrderX;
WorldOrder worldOrderY;

/**
 */
void initialize(int aPlatformCount)
{
	set<int> xCoordinates;
	set<int> yCoordinates;

	// to make sure we have a reference point
	xCoordinates.insert(-2 * (MAX_COORDINATE + 1));
	yCoordinates.insert(-2 * (MAX_COORDINATE + 1));

	for (int i = 0; i < aPlatformCount; i++) {
		xCoordinates.insert(gPlatform[i].x1);
		yCoordinates.insert(gPlatform[i].y1);
		xCoordinates.insert(gPlatform[i].x2);
		yCoordinates.insert(gPlatform[i].y2);
	}

	for (set<int>::const_iterator i = xCoordinates.begin(); i != xCoordinates.end(); i++) {
		worldOrderX.insert(make_pair(*i, set<int>()));
	}

	for (set<int>::const_iterator i = yCoordinates.begin(); i != yCoordinates.end(); i++) {
		worldOrderY.insert(make_pair(*i, set<int>()));
	}

	for (int i = 0; i < aPlatformCount; i++) {
		WorldOrder::iterator iX = worldOrderX.lower_bound(gPlatform[i].x1);
		do {
			iX->second.insert(i);
			iX++;
		} while (iX->first != gPlatform[i].x2);

		WorldOrder::iterator iY = worldOrderY.lower_bound(gPlatform[i].y1);
		do {
			iY->second.insert(i);
			iY++;
		} while (iY->first != gPlatform[i].y2);
	}
}


#ifdef _DEBUG
void printWorld()
{
	WorldOrder::const_iterator i;
	set<int>::const_iterator   j;

	for (i = worldOrderX.begin(); i != worldOrderX.end(); i++) {
		printf("X [%d]:", i->first / 2);
		for (j = i->second.begin(); j != i->second.end(); j++) {
			printf(" [%d]", *j);
		}
		printf("\n");
	}

	for (i = worldOrderY.begin(); i != worldOrderY.end(); i++) {
		printf("Y [%d]:", i->first / 2);
		for (j = i->second.begin(); j != i->second.end(); j++) {
			printf(" [%d]", *j);
		}
		printf("\n");
	}
}
#endif


/**
 */
void addPlatform(int aPlatformId, int x1, int y1, int x2, int y2)
{
	x1 <<= 1; y1 <<= 1; x2 <<= 1; y2 <<= 1;
	x2 += 1; y2 += 1;

	gPlatform[aPlatformId].x1 = x1;
	gPlatform[aPlatformId].y1 = y1;
	gPlatform[aPlatformId].x2 = x2;
	gPlatform[aPlatformId].y2 = y2;
}


/**
 * test if point is on the platform
 */
bool isOnPlatform(int x, int y)
{
	WorldOrder::const_iterator iX;
	WorldOrder::const_iterator iY;

	iX = worldOrderX.upper_bound(x);
	iX--;
	if (iX->second.empty()) return false;

	iY = worldOrderY.upper_bound(y);
	iY--;
	if (iY->second.empty()) return false;

	set<int>::const_iterator searchX    = iX->second.begin();
	set<int>::const_iterator searchXEnd = iX->second.end();
	set<int>::const_iterator searchY    = iY->second.begin();
	set<int>::const_iterator searchYEnd = iY->second.end();

	bool found = false;

	do {
		if (*searchX == *searchY) {
			found = true;
		} else if (*searchX < *searchY) {
			searchX = iX->second.lower_bound(*searchY);
		} else {
			searchY = iY->second.lower_bound(*searchX);
		}
	} while (!found && searchX != searchXEnd && searchY != searchYEnd);

	return found;
}


/**
 * test if object is stable
 */
bool isStable(int x1, int y1, int x2, int y2)
{
	// test for center
	if (isOnPlatform(x1 + x2, y1 + y2)) return true;

	x1 <<= 1; y1 <<= 1; x2 <<= 1; y2 <<= 1;

	// test for corners
	int cornersOnPlatform = 0;
	if (isOnPlatform(x1, y1)) cornersOnPlatform++;
	if (isOnPlatform(x1, y2)) cornersOnPlatform++;
	if (isOnPlatform(x2, y1)) cornersOnPlatform++;

	if (cornersOnPlatform != 3) {
		if (isOnPlatform(x2, y2)) cornersOnPlatform++;
	}

	return cornersOnPlatform >= 3;
}


int main()
{
	int n, q;
	int x1, x2, y1, y2;


	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		addPlatform(i, x1, y1, x2, y2);
	}
	initialize(n);

#ifdef _DEBUG
	printWorld();
#endif

	return 0;

	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		printf("%s\n", isStable(x1, y1, x2, y2) ? "TAK" : "NIE");
	}

	return 0;
}
