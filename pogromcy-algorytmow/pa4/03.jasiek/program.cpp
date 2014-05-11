#include <iostream>
#include <set>
#include <map>
using namespace std;


map<int, multiset<int> > rows;
char turn[128][128];
char xdelta[128];
char ydelta[128];

int main()
{
	xdelta['N'] =  0; ydelta['N'] =  1;
	xdelta['W'] = -1; ydelta['W'] =  0;
	xdelta['S'] =  0; ydelta['S'] = -1;
	xdelta['E'] =  1; ydelta['E'] =  0;
	xdelta['K'] =  0; ydelta['K'] =  0;
	xdelta['P'] =  0; ydelta['P'] =  0;
	
	turn['N']['N'] = 1;
	turn['N']['W'] = 1;
	turn['N']['S'] = 2;
	turn['N']['E'] = 0;
	turn['W']['N'] = 0;
	turn['W']['W'] = 0;
	turn['W']['S'] = 1;
	turn['W']['E'] = 1;
	turn['S']['N'] = 2;
	turn['S']['W'] = 0;
	turn['S']['S'] = 1;
	turn['S']['E'] = 1;
	turn['E']['N'] = 1;
	turn['E']['W'] = 1;
	turn['E']['S'] = 0;
	turn['E']['E'] = 0;

	char c = 'X', d = 'X', p;
	int x = 10000, y = 10000;
	bool end = false;
	int total = 0;

	cin >> d;
	do {
		cin >> c;
		if (d == 'P') {
			if (c == 'K') {
				total = 1;
				end = true;
			} else p = c;
		} else {
			if (c == 'K') {
				c = p;
				end = true;
			}
			int t = turn[d][c];
			while (t--) rows[y].insert(x);
		}
		x += xdelta[c]; y += ydelta[c];
		d = c;
	} while (!end);

	map<int, multiset<int> >::iterator itA(rows.begin());
	while (itA != rows.end()) {
		multiset<int>& row = (*itA).second;
		multiset<int>::iterator itB(row.begin());
		while(itB != row.end()) {
			total -= *itB; itB++;
			total += *itB; itB++;
			total++;
		}
		itA++;
	}

	cout << total << endl;
	return 0;
}
