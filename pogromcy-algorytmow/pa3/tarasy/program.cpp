#include <stdio.h>
#include <algorithm>
using namespace std;

int main()
{
	int liczbaTarasow, pieniadze;
	int liczbaWind;
	int kosztR[20000];
	int kosztL[20000];
	int tarasA, tarasB;
	int odwiedzoneTarasy = 1;

	scanf("%d %d", &liczbaTarasow, &pieniadze);
	liczbaWind = liczbaTarasow - 1;

	scanf("%d", &tarasA);
	for (int i = 0; i < liczbaTarasow - 1; i++) {
		scanf("%d", &tarasB);
		kosztR[i] = tarasA >= tarasB ? 0 : tarasB - tarasA;
		kosztL[i] = tarasB >= tarasA ? 0 : tarasA - tarasB;
		tarasA = tarasB;
	}

	int l, r, koszt = 0;
	l = r = 0;

	while (pieniadze >= koszt && l < liczbaWind && r < liczbaWind) {
		do {
			koszt += kosztR[r++];
		} while (pieniadze >= koszt && r < liczbaWind);

		odwiedzoneTarasy = max(odwiedzoneTarasy, r - l);
		
		if (pieniadze < koszt) {
			odwiedzoneTarasy = max(odwiedzoneTarasy, r - l);
			koszt -= kosztR[--r];
			koszt -= kosztR[l++];
		} else {
			odwiedzoneTarasy = max(odwiedzoneTarasy, r - l + 1);
		}
	}

	koszt = 0;
	l = r = 0;
	while (pieniadze >= koszt && l < liczbaWind && r < liczbaWind) {
		do {
			koszt += kosztL[r++];
		} while (pieniadze >= koszt && r < liczbaWind);

		if (pieniadze < koszt) {
			odwiedzoneTarasy = max(odwiedzoneTarasy, r - l);
			koszt -= kosztL[--r];
			koszt -= kosztL[l++];
		} else {
			odwiedzoneTarasy = max(odwiedzoneTarasy, r - l + 1);
		}
	}

	printf("%d\n", odwiedzoneTarasy);
	return 0;
}
