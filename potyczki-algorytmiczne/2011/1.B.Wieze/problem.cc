#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
using namespace std;

const int MAX_N = 1000;

char input[MAX_N + 2];
char output[MAX_N + 2];
int w[MAX_N];
int k[MAX_N];

int main()
{
	int n;

	scanf("%d\n", &n);

	memset(w, -1, sizeof(w));
	memset(k, -1, sizeof(w));

	for (int i = 0; i < n; i++)
	{
		fgets(input, sizeof(input), stdin);
		for (int j = 0; j < n; j++)
		{
			if (input[j] == 'W')
			{
				w[i] = j;
				k[j] = i;
			}
		}
	}

	int pierwszaWolnaKolumna = -1;
	memset(output, '.', n);
	output[n] = 0;
	for (int i = 0; i < n; i++)
	{
		if (w[i] < 0) 
		{
			while (k[++pierwszaWolnaKolumna] >= 0);
			w[i] = pierwszaWolnaKolumna;
			k[pierwszaWolnaKolumna] = i;
		}

		output[w[i]] = 'W';
		puts(output);
		output[w[i]] = '.';
	}

	return 0;
}
