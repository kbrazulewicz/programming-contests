#include <cstdio>

#include <algorithm>
#include <list>
#include <utility>
#include <vector>

using namespace std;

class CardFile
{
	public:
		int index;
		int size;

		CardFile(int aIndex, int aSize)
			: index(aIndex), size(aSize)
		{}

		void merge(CardFile& aFile) 
		{
			size += aFile.size;
			aFile.size = 0;
		}

		bool operator < (const CardFile& rhs) const
		{
			return this->size < rhs.size;
		}
};

typedef vector<CardFile> CardFileVector;


int getNextIdx(const CardFileVector& aCardFiles, list<int>& aListA, list<int>& aListB)
{
	int result = 0;

	if (aListA.empty() && aListB.empty()) {
	} else if (aListA.empty()) {
		result = aListB.front();
		aListB.pop_front();
	} else if (aListB.empty()) {
		result = aListA.front();
		aListA.pop_front();
	} else if (aCardFiles[aListA.front()].size > aCardFiles[aListB.front()].size) {
		result = aListB.front();
		aListB.pop_front();
	} else {
		result = aListA.front();
		aListA.pop_front();
	}

	return result;
}


int main()
{
	int n, tmp;
	unsigned long long x = 0;
	CardFileVector s;
	CardFileVector sSorted;
	list<int> valQ, sumQ;
	list< pair<int, int> > r;

	// read n value
	scanf("%d", &n);
	s.reserve(n);
	
	// read n of s values	
	for (int i = 0; i < n; i++) {
		scanf("%d", &tmp);
		s.push_back(CardFile(i, tmp));
	}

	// initial sort
	sSorted = s;
	sort(sSorted.begin(), sSorted.end());
	for (CardFileVector::const_iterator i = sSorted.begin(); i != sSorted.end(); i++) {
		valQ.push_back(i->index);
	}

	int i1, i2;

	do {
		// find 2 smallest values (s[i1], s[i2])
		i1 = getNextIdx(s, valQ, sumQ);
		i2 = getNextIdx(s, valQ, sumQ);

		if (i2 < i1) swap(i1, i2);

		r.push_back(make_pair(i1, i2));
		s[i1].merge(s[i2]);
		x += s[i1].size;

		if (!(valQ.empty() && sumQ.empty())) {
			sumQ.push_back(i1);
		}
	} while (!(valQ.empty() && sumQ.empty()));

	printf("%llu\n", x);

	for (list< pair<int, int> >::const_iterator i = r.begin(); i != r.end(); i++)
	{
		printf("%d %d\n", i->first + 1, i->second + 1);
	}

	return 0;
}
