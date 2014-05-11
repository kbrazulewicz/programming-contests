#include <iostream>
using namespace std;

int F(int a)
{
	while (a > 9) a = a / 10 + a % 10;
	return a;
}

int main()
{
	int l, s = 0, t;

	scanf("%d", &l);
	for (int i = 0; i < l; i++) {
		scanf("%d", &t);
		s = F(s + t * (1 + s));
		if (s == 8) break;
	}

	printf("%d\n", s);
		
	return 0;
}
