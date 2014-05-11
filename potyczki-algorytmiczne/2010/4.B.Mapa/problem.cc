#include <iostream>
#include <string>
using namespace std;

static const int MAX_D = 1000000000;
static const int MAX_N = 1000000;

typedef struct {
	int x;
	int y;
	bool startPointCandidate;
} mapPoint;

mapPoint input[MAX_N];

struct sort_x_asc : public binary_function<mapPoint, mapPoint, bool> {
	bool operator()(const mapPoint& a, const mapPoint& b) { return a.x < b.x; }
};

struct sort_y_asc : public binary_function<mapPoint, mapPoint, bool> {
	bool operator()(const mapPoint& a, const mapPoint& b) { return a.y < b.y; }
};


int main()
{
	int n, d;

	scanf("%d%d", &n, &d);

	for (int i = 0; i < n; i++) {
		scanf("%d%d", &input[i].x, &input[i].y);
		input[i].startPointCandidate = true;
	}

	int result = n;

	sort(input, input + n, sort_x_asc());
	for (int i = 0, yMin = d, yMax = 0; i < n; i++) {
		if (input[i].startPointCandidate) {
			if (input[i].y <= yMin || input[i].y >= yMax) {
				input[i].startPointCandidate = false;
				result--;
			}
		}

		yMin = min(yMin, input[i].y);
		yMax = max(yMax, input[i].y);
	}
	for (int i = n - 1, yMin = d, yMax = 0; i >= 0; i--) {
		if (input[i].startPointCandidate) {
			if (input[i].y <= yMin || input[i].y >= yMax) {
				input[i].startPointCandidate = false;
				result--;
			}
		}

		yMin = min(yMin, input[i].y);
		yMax = max(yMax, input[i].y);
	}


	sort(input, input + n, sort_y_asc());
	for (int i = 0, xMin = d, xMax = 0; i < n; i++) {
		if (input[i].startPointCandidate) {
			if (input[i].x <= xMin || input[i].x >= xMax) {
				input[i].startPointCandidate = false;
				result--;
			}
		}
		xMin = min(xMin, input[i].x);
		xMax = max(xMax, input[i].x);
	}
	for (int i = n - 1, xMin = d, xMax = 0; i >= 0; i--) {
		if (input[i].startPointCandidate) {
			if (input[i].x <= xMin || input[i].x >= xMax) {
				input[i].startPointCandidate = false;
				result--;
			}
		}
		xMin = min(xMin, input[i].x);
		xMax = max(xMax, input[i].x);
	}

	printf("%d\n", result);

	return 0;
}
