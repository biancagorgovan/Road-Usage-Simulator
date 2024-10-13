/*GORGOVAN Bianca Maria 314CB*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct celarc 
{ int d;           /* destinatie arc */
  float *c;            /* cost arc */
  int nrTronsoane;
  int indexArc;
  struct celarc *urm; /* adresa urmatorul adiacent */
} TCelArc, *AArc;

typedef struct 
{ int n;     /* numar noduri */
  AArc* x;    /* vector adrese liste arce */
} TGL;

typedef struct 
{   int index;
    char denumire[250];
} TAsociereNr; //structura cu care stabilesc corespondenta dintre numele orasului si indexul de ordine al citirii

typedef struct ArcVector {
    int sursa;
    int destinatie;
    int nrTronsoane;
    float *c;
    int indexArc;
} ArcVector; //structura cu care imi creez un vector de arce cu toate info despre fiecare arc, ca sa le pot ordona dupa anumite criterii

TGL* AlocG(int nr);
void DistrG(TGL** g);
TGL* ConstrGraf(char numefis[250], int *K, float *L, int *R, TAsociereNr *noduri);
void ModificareUzura(int K, TGL *g);
void RuteDePastrat(TGL *g, float L, FILE *fout);
void colectareArce(TGL *g, ArcVector **arce, int *nrArce);
int comparaArce(const void *a, const void *b);
void afisareGrafCuUzura(TGL *g, TAsociereNr *noduri, FILE *fout, int *R);
int cmpIndex(const void *a, const void *b);