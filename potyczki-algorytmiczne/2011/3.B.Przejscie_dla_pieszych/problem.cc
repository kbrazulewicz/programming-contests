#include <cstdio>
#include <map>
using namespace std;

#undef DEBUG

const int MAX_N = 500000;
int lengths[MAX_N];

void addWhiteStripe(int l, int r, map<int, int> &stripe)
{
#ifdef DEBUG
	printf("addWhiteStripe: l %d; r %d\n", l, r);
#endif
	map<int, int>::iterator i = stripe.lower_bound(l);
	if (i != stripe.begin()) i--;

	while (i != stripe.end() && i->first < r)
	{
		int blackL = i->first;
		int blackR = i->second;

		if (blackL < l && blackR > r) {
			i->second = l;
			stripe[r] = blackR;
			i++;
		} else if (blackL < l && blackR > l) {
			i->second = l;
			i++;
		} else if (blackL >= l && blackR > r) {
			stripe.erase(i++);
			stripe[r] = blackR;
		} else if (blackL >= l && blackR <= r) {
			stripe.erase(i++);
		} else {
			i++;
		}
	}

#ifdef DEBUG
	for (map<int, int>::const_iterator i = stripe.begin(); i != stripe.end(); i++)
	{
		printf("black stripe [%d - %d]\n", i->first, i->second);
	}
#endif
}



bool przejscieDlaPieszych(int feet, int step, int n, int lengths[])
{
	int l = 0, r;
	map<int, int> stripe;

	// all black at the beginning
	stripe[0] = step;

	for (int i = 0; i < n; i++)
	{
		r = l + lengths[i];
		if (i % 2 == 0) {
			// white stripe
			if (r > step) {
				addWhiteStripe(l, step, stripe);
				l = 0;
				r %= step;
			}
			addWhiteStripe(l, r, stripe);
		}
		l = r % step;
	}

	// search for a black stripe of length at least feet
	for (map<int, int>::const_iterator i = stripe.begin(); i != stripe.end(); i++)
	{
#ifdef DEBUG
		printf("black stripe [%d - %d]\n", i->first, i->second);
#endif
		if (i->second - i->first >= feet) {
			return true;
		}
	}

	return false;
}


int main()
{
	int t, s, k, n;

	scanf("%d", &t);

	while (t--) {
		scanf("%d %d %d", &s, &k, &n);
		for (int i = 0; i < n; scanf("%d", &lengths[i++]));

		puts(przejscieDlaPieszych(s, k, n, lengths) ? "TAK" : "NIE");
	}

	return 0;
}
