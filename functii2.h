/*GORGOVAN Bianca Maria 314CB*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
typedef struct celarc2 
{ int d;           /* destinatie arc */
  int c;            /* cost arc */
  int indexArc;
  struct celarc2 *urm; /* adresa urmatorul adiacent */
} TCelArc2, *AArc2;

typedef struct 
{ int n;     /* numar noduri */
  AArc2* x;    /* vector adrese liste arce */
} TGL2;

typedef struct 
{   int index;
    char denumire[250];
} TAsociereNr2; //structura cu care stabilesc corespondenta dintre numele orasului si indexul de ordine al citirii

typedef struct ArcVector2 {
    int sursa;
    int destinatie;
    int c; //costul arcului
    int indexArc;
    int necesar; //stabilesc daca apartine vreunui drum de cost minim, marcat cu 1
    int maxDist; //stabilesc cel mai lung drum de cost minim din care face parte arcul
} ArcVector2; //structura cu care imi creez un vector de arce cu toate info despre fiecare arc, ca sa le pot ordona dupa anumite criterii

void DistrG2(TGL2** g);
TGL2* AlocG2(int nr);
TGL2* ConstrGraf2(char numefis[250], int *K, char oras_start[250], int *M, TAsociereNr2 *noduri);
void colectareArce2(TGL2 *g, ArcVector2 **arce, int *nrArce);
int comparaArce2(const void *a, const void *b);
int minDistance(int dist[], int sptSet[], int V);
void dijkstra(TGL2 *graph, int src, int *dist, int *parent);
void arceDijkstra(int *parent, int *dist, int src, ArcVector2 *arce, int V, int M);
void SelectieArce(int count, ArcVector2 *arce, int *K, int *M, ArcVector2 *arcBun);
void afisareGraf2(ArcVector2 *arcBun, TAsociereNr2 *noduri, FILE *fout, int *K);
int comparaDistMax(const void* a, const void* b);

