#include <iostream>
#include <map>
using namespace std;

static const int MAX_N = 200000;
static const int MAX_M = 1000000000;

struct piece_t;
typedef map<int, piece_t*> boardline_t;
typedef map<int, boardline_t*> boardlineMap_t;

struct piece_t {
	char type;
	int x;	// X coordinate
	int y;	// Y coordinate
	int a;	// A diagonal
	int b;	// B diagonal

	boardline_t* row;
	boardline_t* col;
	boardline_t* dA;
	boardline_t* dB;

	boardline_t::const_iterator rowIt;
	boardline_t::const_iterator colIt;
	boardline_t::const_iterator dAIt;
	boardline_t::const_iterator dBIt;
} piece[MAX_N];

boardline_t row[MAX_N + 1];
boardline_t col[MAX_N + 1];
boardline_t dA[MAX_N + 1];
boardline_t dB[MAX_N + 1];

boardlineMap_t rowMap, colMap, dAMap, dBMap;

pair<unsigned int, unsigned int> checkCol(const piece_t& aPiece, int aLimit)
{
	pair<unsigned int, unsigned int> result(aPiece.y - 1, aLimit - aPiece.y);
	boardline_t::const_iterator t;

	t = aPiece.colIt;
	if (t != aPiece.col->begin()) {
		t--;
		result.first -= t->second->y;
	}

	t = aPiece.colIt;
	t++;
	if (t != aPiece.col->end()) {
		result.second -= (aLimit - t->second->y + 1);
	}

	return result;
}


pair<unsigned int, unsigned int> checkRow(const piece_t& aPiece, int aLimit)
{
	pair<unsigned int, unsigned int> result(aPiece.x - 1, aLimit - aPiece.x);
	boardline_t::const_iterator t;

	t = aPiece.rowIt;
	if (t != aPiece.row->begin()) {
		t--;
		result.first -= t->second->x;
	}

	t = aPiece.rowIt;
	t++;
	if (t != aPiece.row->end()) {
		result.second -= (aLimit - t->second->x + 1);
	}

	return result;
}


pair<unsigned int, unsigned int> checkDiagA(const piece_t& aPiece, int aLimit)
{
	pair<unsigned int, unsigned int> result(min(aPiece.x - 1, aLimit - aPiece.y), min(aLimit - aPiece.x, aPiece.y - 1));
	boardline_t::const_iterator t;

	t = aPiece.dAIt;
	if (t != aPiece.dA->begin()) {
		t--;
		result.first -= min(t->second->x - 1, aLimit - t->second->y) + 1;
	}

	t = aPiece.dAIt;
	t++;
	if (t != aPiece.dA->end()) {
		result.second -= min(aLimit - t->second->x, t->second->y - 1) + 1;
	}

	return result;
}


pair<unsigned int, unsigned int> checkDiagB(const piece_t& aPiece, int aLimit)
{
	pair<unsigned int, unsigned int> result(min(aPiece.x - 1, aPiece.y - 1), min(aLimit - aPiece.x, aLimit - aPiece.y));
	boardline_t::const_iterator t;

	t = aPiece.dBIt;
	if (t != aPiece.dB->begin()) {
		t--;
		result.first -= min(t->second->x - 1, t->second->y - 1) + 1;
	}

	t = aPiece.dBIt;
	t++;
	if (t != aPiece.dB->end()) {
		result.second -= min(aLimit - t->second->x, aLimit - t->second->y) + 1;
	}

	return result;
}


unsigned int checkKing(const piece_t& aPiece, int limit)
{
	unsigned int result = 0;
	pair<unsigned int, unsigned int> t;

	// col 
	t = checkCol(aPiece, limit);
	result += min(1U, t.first) + min(1U, t.second);

	// row 
	t = checkRow(aPiece, limit);
	result += min(1U, t.first) + min(1U, t.second);

	// diagA
	t = checkDiagA(aPiece, limit);
	result += min(1U, t.first) + min(1U, t.second);

	// diagB
	t = checkDiagB(aPiece, limit);
	result += min(1U, t.first) + min(1U, t.second);

	return result;
}


unsigned int checkRook(const piece_t& aPiece, int limit)
{
	unsigned int result = 0;
	pair<unsigned int, unsigned int> t;

	// col 
	t = checkCol(aPiece, limit);
	result += t.first + t.second;

	// row 
	t = checkRow(aPiece, limit);
	result += t.first + t.second;

	return result;
}


unsigned int checkBishop(const piece_t& aPiece, int limit)
{
	unsigned int result = 0;
	pair<unsigned int, unsigned int> t;

	// diagA
	t = checkDiagA(aPiece, limit);
	result += t.first + t.second;

	// diagB
	t = checkDiagB(aPiece, limit);
	result += t.first + t.second;

	return result;
}


unsigned int checkKnight(const piece_t& aPiece, int aLimit)
{
	unsigned int result = 0;

	if (aLimit < 3) return result;

	boardlineMap_t::const_iterator t;

	if (aPiece.x > 2) {
		t = colMap.find(aPiece.x - 2);
		if (t == colMap.end()) {
			if (aPiece.y > 1) result++;
			if (aPiece.y < aLimit) result++;
		} else {
			const boardline_t* u = t->second;
			// x - 2, y - 1
			if (aPiece.y > 1 && u->find(aPiece.y - 1) == u->end()) result++;
			// x - 2, y + 1
			if (aPiece.y < aLimit && u->find(aPiece.y + 1) == u->end()) result++;
		}
	}

	if (aPiece.x > 1) {
		t = colMap.find(aPiece.x - 1);
		if (t == colMap.end()) {
			if (aPiece.y > 2) result++;
			if (aPiece.y < aLimit - 1) result++;
		} else {
			const boardline_t* u = t->second;
			// x - 1, y - 2
			if (aPiece.y > 2 && u->find(aPiece.y - 2) == u->end()) result++;
			// x - 1, y + 2
			if (aPiece.y < aLimit - 1 && u->find(aPiece.y + 2) == u->end()) result++;
		}
	}

	if (aPiece.x < aLimit) {
		t = colMap.find(aPiece.x + 1);
		if (t == colMap.end()) {
			if (aPiece.y > 2) result++;
			if (aPiece.y < aLimit - 1) result++;
		} else {
			const boardline_t* u = t->second;
			// x + 1, y - 2
			if (aPiece.y > 2 && u->find(aPiece.y - 2) == u->end()) result++;
			// x + 1, y + 2
			if (aPiece.y < aLimit - 1 && u->find(aPiece.y + 2) == u->end()) result++;
		}
	}

	if (aPiece.x < aLimit - 1) {
		t = colMap.find(aPiece.x + 2);
		if (t == colMap.end()) {
			if (aPiece.y > 1) result++;
			if (aPiece.y < aLimit) result++;
		} else {
			const boardline_t* u = t->second;
			// x + 2, y - 1
			if (aPiece.y > 1 && u->find(aPiece.y - 1) == u->end()) result++;
			// x + 2, y + 1
			if (aPiece.y < aLimit && u->find(aPiece.y + 1) == u->end()) result++;
		}
	}


	return result;
}


unsigned int checkQueen(const piece_t& aPiece, int limit)
{
	unsigned int result = 0;

	// col + row
	result += checkRook(aPiece, limit);

	// diagA + diagB
	result += checkBishop(aPiece, limit);

	return result;
}


int main()
{
	int n, m;

	scanf("%d%d\n", &n, &m);

	for (int i = 0; i < n; i++) {
		piece_t *p = &piece[i];
		scanf("%c%d%d\n", &p->type, &p->x, &p->y);
		p->a = p->x + p->y - 1;
		p->b = m + p->x - p->y;


		boardlineMap_t::const_iterator j;

		j = rowMap.find(p->y);
		if (j == rowMap.end()) {
			j = rowMap.insert(make_pair(p->y, &row[rowMap.size()])).first;
		}
		p->row   = j->second;
		p->rowIt = j->second->insert(make_pair(p->x, p)).first;

		j = colMap.find(p->x);
		if (j == colMap.end()) {
			j = colMap.insert(make_pair(p->x, &col[colMap.size()])).first;
		}
		p->col   = j->second;
		p->colIt = j->second->insert(make_pair(p->y, p)).first;

		j = dAMap.find(p->a);
		if (j == dAMap.end()) {
			j = dAMap.insert(make_pair(p->a, &dA[dAMap.size()])).first;
		}
		p->dA   = j->second;
		p->dAIt = j->second->insert(make_pair(p->b, p)).first;

		j = dBMap.find(p->b);
		if (j == dBMap.end()) {
			j = dBMap.insert(make_pair(p->b, &dB[dBMap.size()])).first;
		}
		p->dB   = j->second;
		p->dBIt = j->second->insert(make_pair(p->a, p)).first;

#ifdef DEBUG
		printf("Piece [%c], position [%d:%d], diagonal [%d:%d]\n",
				p->type, p->x, p->y, p->a, p->b);
#endif
	}

#ifdef DEBUG
	for (boardlineMap_t::const_iterator i = rowMap.begin(); i != rowMap.end(); i++) {
		for (boardline_t::const_iterator j = i->second->begin(); j != i->second->end(); j++) {
			printf("row [%d], col [%d], piece [%c]\n",
					i->first, j->first, j->second->type);
		}
	}
#endif

	for (int i = 0; i < n; i++) {
		unsigned int result = 0;
		switch (piece[i].type) {
			case 'G':
				result = checkBishop(piece[i], m);
				break;

			case 'H':
				result = checkQueen(piece[i], m);
				break;

			case 'K':
				result = checkKing(piece[i], m);
				break;

			case 'S':
				result = checkKnight(piece[i], m);
				break;

			case 'W':
				result = checkRook(piece[i], m);
				break;
		}
		printf("%u\n", result);
	}

	return 0;
}
