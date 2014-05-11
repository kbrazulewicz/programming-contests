/**
 * Keywords: Fibonacci
 * http://www.research.att.com/~njas/sequences/A000045
 * F(n+2) = number of binary sequences of length n that have no consecutive 0's.
 */
#include <iostream>
using namespace std;

static const int FLD_PERIOD = 60;

const char fld[FLD_PERIOD + 1] = "235831459437077415617853819099875279651673033695493257291011";

int main()
{
	int n;

	cin >> n;
	cout << fld[(n - 2) % FLD_PERIOD] << endl;
	
	return 0;
}
