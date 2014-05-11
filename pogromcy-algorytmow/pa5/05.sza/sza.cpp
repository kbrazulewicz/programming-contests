#include <cstdio>
#include <cstring>

#include <map>
#include <set>
#include <vector>

using namespace std;

#undef _DEBUG

static const int MAX_CHESSBOARD_SIZE = 1000000;
static const unsigned char FIELD_DRILLED = 'X';
static const unsigned char FIELD_NOT_DRILLED = '.';

unsigned char chessboard[MAX_CHESSBOARD_SIZE];

vector< set<int> > availableFieldsByRow;
vector< set<int> > availableFieldsByCol;
vector<int> fieldsNotDrilledByRow;
vector<int> fieldsNotDrilledByCol;

typedef map< int, set<int> > ResultMap;
ResultMap results;
int resultCount = 0;


void printChessboard(int k, int w)
{
	for (int i = 0; i < w; i++) {
		printf("%.*s\n", k, &chessboard[i * k]);
	}
}

void drillChessboard(int col, int row, int k, int w)
{
	chessboard[row * k + col] = FIELD_DRILLED;
	availableFieldsByRow[row].erase(col);
	availableFieldsByCol[col].erase(row);
	fieldsNotDrilledByRow[row]--;
	fieldsNotDrilledByCol[col]--;
}

int main()
{
	int k, w, p;

	scanf("%d%d%d", &k, &w, &p);

	int availableCols = k;
	int availableRows = w;

	memset(chessboard, FIELD_NOT_DRILLED, k * w * sizeof(chessboard[0]));

	set<int> colFields;
	set<int> rowFields;
	for (int i = 0; i < k; rowFields.insert(i++));
	for (int i = 0; i < w; colFields.insert(i++));

	availableFieldsByRow.insert(availableFieldsByRow.begin(), w, rowFields);
	availableFieldsByCol.insert(availableFieldsByCol.begin(), k, colFields);
	fieldsNotDrilledByRow.insert(fieldsNotDrilledByRow.begin(), w, k);
	fieldsNotDrilledByCol.insert(fieldsNotDrilledByCol.begin(), k, w);

	for (int i = 0; i < p; i++) {
		int col, row;
		scanf("%d%d", &col, &row);

		drillChessboard(--col, --row, k, w);

		if (availableFieldsByRow[row].empty()) availableRows--;
		if (availableFieldsByCol[col].empty()) availableCols--;
	}

#ifdef _DEBUG
	printChessboard(k ,w);
#endif

	// find a good place to drill
	map<int, bool> rowChecked;
	int row = 0;
	while (row < w && !(availableRows < w || availableCols < w)) {
		if (!rowChecked[row] && fieldsNotDrilledByRow[row] == 1) {
			int suspectedCol = *(availableFieldsByRow[row].begin());
#ifdef _DEBUG
			printf("suspected col [%d], row other than [%d]\n", suspectedCol, row);
#endif

			set<int> fields = availableFieldsByCol[suspectedCol];
			fields.erase(row);
			for (set<int>::iterator i = fields.begin(); i != fields.end(); i++) {
				results[suspectedCol].insert(*i);
				resultCount++;
				drillChessboard(suspectedCol, *i, k, w);
			}
			rowChecked[row] = true;
			row = 0;
		} else row++;
	}

	if (availableRows < w || availableCols < w) {
		// special case - all fields can be drilled
		for (int iRow = 0; iRow < w; iRow++) {
			for (int iCol = 0; iCol < k; iCol++) {
				if (chessboard[iRow * k + iCol] == FIELD_NOT_DRILLED) {
					results[iCol].insert(iRow);
					resultCount++;
				}
			}
		}
	}

	printf("%d\n", resultCount);
	for (ResultMap::const_iterator i = results.begin(); i != results.end(); i++) {
		for (set<int>::const_iterator j = i->second.begin(); j != i->second.end(); j++) {
			printf("%d %d\n", i->first + 1, *j + 1);
		}
	}

	return 0;
}
