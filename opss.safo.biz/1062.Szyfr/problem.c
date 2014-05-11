#include <stdio.h>
int f(int n){return n^(n>>1);}
int o(int n){int r=n;do{n>>=1;r^=n;}while(n);return r;}
int main()
{
	int n;
	do {scanf("%d",&n);if(n)printf("%d %d\n",f(n),o(n));}while(n);
	return 0;
}
