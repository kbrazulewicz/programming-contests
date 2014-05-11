#include "pp.h"

void WypelnijMagazyn(Element *wskaznik, unsigned int rozmiar)
{ unsigned int i;
for (i=0; i<rozmiar; i++)
	{ wskaznik[i].waga = rand() % OGR_WAGI + 1;
	wskaznik[i].rozmiar = rand() % OGR_ROZM + 1;
	}
}

void PokazZawartoscMagazynu(Element *wskaznik, unsigned int rozmiar)
{ unsigned int i;
  printf("\n+----------+------+---------+\n| Nr elem. | Waga | Rozmiar |\n+----------+------+---------+");
  for (i=0; i<rozmiar; i++) printf("\n|%10u|%6u|%9u|",i+1, wskaznik[i].waga, wskaznik[i].rozmiar);
  printf("\n+----------+------+---------+");
}

ElementTabeli** AlokujTabliceAlgorytmu(unsigned int V, unsigned int j)
	{ ElementTabeli** wskaznik;
	unsigned int i;
	wskaznik = (ElementTabeli**) malloc((V+1)*sizeof(ElementTabeli*));
	if (!wskaznik) return NULL;
	for (i=0; i<=V; i++) { wskaznik[i] = (ElementTabeli*) malloc((j+1)*sizeof(ElementTabeli));
				if (!wskaznik[i]) { wskaznik = NULL;
				break; }
				}
	return wskaznik;
	}
	
void ZwolnijTabliceAlgorytmu(ElementTabeli** wskaznik, unsigned int V)
	{ unsigned int i;
	for (i=0; i<=V; i++) free(wskaznik[i]);
	free(wskaznik);
	}

void BudujTabliceAlgorytmu(ElementTabeli** wskaznik, Element* mag, unsigned int V, unsigned int j)
	{ unsigned int w,k,war0,war1;
	for (w=0; w<=V; w++)
		for (k=0; k<=j; k++)
			{ if ((w==0)||(k==0)) 
				{ wskaznik[w][k].wartosc=0;
				wskaznik[w][k].znacznik=0;
				}
			else 
			{ war0 = wskaznik[w][k-1].wartosc;
			if ((long int)(w-mag[k-1].rozmiar)<0) war1=0; 
				else war1=wskaznik[w-mag[k-1].rozmiar][k-1].wartosc+mag[k-1].waga;
			if (war0>=war1) wskaznik[w][k].znacznik=0;
				else wskaznik[w][k].znacznik=1;
			wskaznik[w][k].wartosc=(war0>=war1?war0:war1);
			}
			}
	}

void PokazTabliceAlgorytmu(ElementTabeli** wskaznik, unsigned int V, unsigned int j)
	{ unsigned int w,k;
	printf("\n------------");
	for (w=0; w<=V; w++)
		{ printf("\n");
		for (k=0; k<=j; k++) printf("R%dZ%d ",wskaznik[w][k].wartosc,wskaznik[w][k].znacznik);
		}
	}
	
void PokazElementyPlecaka(ElementTabeli** wskaznik, Element *mag, unsigned int w, unsigned int k)
	{ if (!wskaznik[w][k].wartosc) return;
	if (!wskaznik[w][k].znacznik) PokazElementyPlecaka(wskaznik, mag, w, k-1);
		else 
		{ 
		#ifdef POKAZUJ_WSZYSTKO
		printf("%u ", k);
		#endif
		PokazElementyPlecaka(wskaznik, mag, w-mag[k-1].rozmiar, k-1);
		}
		
	}