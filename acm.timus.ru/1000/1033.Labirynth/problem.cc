/* @JUDGE_ID: 16232QS 1033 C++ */

#include <cstdio>
#include <string>
#include <vector>
using namespace std;

static const int MAX_N = 33;

class Coordinate
{
	public:
		Coordinate()
		{
			x = 0;
			y = 0;
		}

		Coordinate(int aX, int aY)
		{
			x = aX;
			y = aY;
		}

		int x;
		int y;
};

class Labirynth
{
	public:
		Labirynth(int aSize)
		{
			size = aSize;
			initialize();
		}

		void read()
		{
			char line[MAX_N + 3];
			for (int i = 0; i < size; i++) {
				fgets(line, sizeof(line), stdin);
				memcpy(area[i], line, size);
			}
		}

		void print()
		{
			for (int i = 0; i < size; i++) {
				printf("%.*s\n", size, area[i]);
			}
		}


		int visitAvailable(int x, int y)
		{
			int result = 0;
			vector<Coordinate> queue;
			queue.reserve(MAX_N * MAX_N);

			Coordinate start(x, y);
			queue.push_back(start);

			do {
				const Coordinate point = queue.back();
				queue.pop_back();

				if (canGoTo(point)) {

					area[point.y][point.x] = L_VISITED;
					result += getNumberOfWalls(point);

#if __DEBUG
					printf("%d %d %d\n", point.x, point.y, getNumberOfWalls(point));
#endif

					Coordinate n(point.x, point.y - 1);
					Coordinate e(point.x + 1, point.y);
					Coordinate s(point.x, point.y + 1);
					Coordinate w(point.x - 1, point.y);

					if (canGoTo(n)) queue.push_back(n);
					if (canGoTo(e)) queue.push_back(e);
					if (canGoTo(s)) queue.push_back(s);
					if (canGoTo(w)) queue.push_back(w);
				}
			} while (!queue.empty());

			return result;
		}


	private:

		static const char L_EMPTY   = '.';
		static const char L_VISITED = '_';
		static const char L_WALL    = '#';
		char area[MAX_N][MAX_N];

		int size;

		void initialize()
		{
			memset(area, L_WALL, sizeof(area));
		}

		bool canGoTo(const Coordinate& aCoordinate)
		{
			return isCoordinateValid(aCoordinate) && isEmptyNotVisited(aCoordinate);
		}

		bool isCoordinateValid(const Coordinate& aPoint)
		{
			return (aPoint.x >= 0 && aPoint.y >= 0 && aPoint.x < size && aPoint.y < size);
		}

		bool isEmptyNotVisited(const Coordinate& aPoint)
		{
			return area[aPoint.y][aPoint.x] == L_EMPTY;
		}

		bool isWall(const Coordinate& aPoint)
		{
			return !isCoordinateValid(aPoint) || area[aPoint.y][aPoint.x] == L_WALL;
		}

		int getNumberOfWalls(const Coordinate& aPoint)
		{
			int result = 0;
			Coordinate n(aPoint.x, aPoint.y - 1);
			Coordinate e(aPoint.x + 1, aPoint.y);
			Coordinate s(aPoint.x, aPoint.y + 1);
			Coordinate w(aPoint.x - 1, aPoint.y);

			if (isWall(n)) result++;
			if (isWall(e)) result++;
			if (isWall(s)) result++;
			if (isWall(w)) result++;

			return result;
		}
};




int main()
{
	int n;

	scanf("%d\n", &n);

	Labirynth labirynth(n);
	labirynth.read();

	int walls = labirynth.visitAvailable(0, 0) + labirynth.visitAvailable(n - 1, n - 1) - 4;
	printf("%d\n", walls * 9);

	return 0;
}
