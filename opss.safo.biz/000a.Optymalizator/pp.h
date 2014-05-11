#include <stdio.h>
#define OGR_WAGI 20
#define OGR_ROZM 20

typedef struct 
	{ unsigned int waga;
	unsigned int rozmiar;
	} Element;

typedef struct 
	{ unsigned int wartosc;
	unsigned char znacznik;
	} ElementTabeli;

void WypelnijMagazyn(Element *wskaznik, unsigned int rozmiar);
void PokazZawartoscMagazynu(Element *wskaznik, unsigned int rozmiar);
ElementTabeli** AlokujTabliceAlgorytmu(unsigned int V, unsigned int j);
void ZwolnijTabliceAlgorytmu(ElementTabeli** wskaznik, unsigned int V);
void BudujTabliceAlgorytmu(ElementTabeli** wskaznik, Element* mag, unsigned int V, unsigned int j);
void PokazTabliceAlgorytmu(ElementTabeli** wskaznik, unsigned int V, unsigned int j);
void PokazElementyPlecaka(ElementTabeli** wskaznik, Element *mag, unsigned int w, unsigned int k);