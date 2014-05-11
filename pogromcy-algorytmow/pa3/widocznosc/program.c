#include <stdio.h>

#define MAX(a, b) (a > b ? a : b)

int h[40000];			
int hp = 0;
int v[40000] = {0};    
int c[40000] = {0};	

int main()
{
	int i, j, count;
	int pairs = 0;

	scanf("%d", &count);

	scanf("%d", &h[hp++]);
	for (i = 1; i < count; i++)
	{
		scanf("%d", &h[hp]);
	
		c[hp] = 0;
		v[hp] = 1;
		while (hp && h[hp] >= h[hp - 1]) {
			if (h[hp] == h[hp - 1]) {
				pairs += v[hp - 1];
				v[hp - 1] = v[hp];
				h[hp - 1] = h[hp];
				c[hp - 1] = 1;
			} else {
				pairs += MAX(v[hp - 1] - 1, 0) + c[hp - 1];
				v[hp - 1] = hp == 1 ? v[hp] : v[hp] + 1;
				h[hp - 1] = h[hp];
				c[hp - 1] = hp == 1 ? 1 : 0;
			}
			hp--;
		}
		pairs += v[hp];
		if (hp && !c[hp]) {
			pairs += v[hp - 1];
		}
		hp++;
	}

	printf("%d\n", pairs);
	return 0;
}
