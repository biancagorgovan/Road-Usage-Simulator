/*GORGOVAN Bianca Maria 314CB*/
#include "functii.h"

TGL* AlocG(int nr) /* aloca spatiu pentru descriptor graf si
	                      vector de (n+1) adrese liste arce */
{
  TGL* g = (TGL*)malloc(sizeof(TGL));    /* spatiu descriptor */
  if (!g) return NULL;
  g->x = (AArc*)calloc((nr+1), sizeof(AArc)); /* spatiu vector adr.liste arce */
  if(!g->x) { free(g); return NULL; }
  g->n = nr;
  return g;
}

void DistrG(TGL** g) {
    //se dezaloca memoria alocata grafului
    int i;
    for (i = 0; i < (*g)->n; i++) {
        AArc p = (*g)->x[i];
        while (p) {
            AArc aux = p;
            p = p->urm;
            free(aux->c);
            free(aux);
        }
    }
    free((*g)->x);
    free(*g);
    *g = NULL;
}

TGL* ConstrGraf(char numefis[250], int *K, float *L, int *R, TAsociereNr *noduri) {
    FILE *f = fopen (numefis, "rt");
    if (!f) return NULL;
    int nrCrtNoduri = 0;
    fscanf(f, "%d", R); //se citeste nr de rute
    fscanf(f, "%d", K); //se citeste nr de ani
    fscanf(f, "%f", L); //se citeste grad max de uzura
    int i = 0;
    for (i = 0; i < (*R); i++) {
        // citim fiecare linie, cu informatiile arcului curent
        // stabilesc corespondenta dintre fiecare nod citit si un index
        char sursa[250];
        char destinatie[250];
        fscanf(f, "%s", sursa);
        fscanf(f, "%s", destinatie);
        int j = 0;
        int existaS = 0;
        int existaD = 0;
        for (j = 0; j < nrCrtNoduri; j++) {
            // verific daca exista deja nodul
            if (strcmp(sursa, noduri[j].denumire) == 0) {
                existaS = 1;
            }
            if (strcmp(destinatie, noduri[j].denumire) == 0) {
                existaD = 1;
            }
        }
        // daca nu s-a citti deja nodul, ii asociez un index, conform ordinii citirii
        if (!existaS) {
            strcpy(noduri[nrCrtNoduri].denumire, sursa);
            noduri[nrCrtNoduri].index = nrCrtNoduri;
            nrCrtNoduri++;
        }
        if (!existaD) {
            strcpy(noduri[nrCrtNoduri].denumire, destinatie);
            noduri[nrCrtNoduri].index = nrCrtNoduri;
            nrCrtNoduri++;
        }
        int nrTronsoane = 0;
        fscanf(f, "%d", &nrTronsoane);
        float *c = (float *)malloc(nrTronsoane * sizeof(float));
        for (j = 0; j < nrTronsoane; j++) {
            fscanf(f, "%f", &c[j]);
        }
        free(c);
    }
    fclose(f);
    f = fopen (numefis, "rt"); // redeschid fisierul de citire, pt a ma asigura ca sunt la inceputul lui ca sa pot sa stabilesc arcele intre nodurile codificate
    if (!f) return NULL;
    TGL *g = AlocG(nrCrtNoduri); //aloc graful in fct de nr de noduri det
    if (!g) return 0;
    //consum caracterele deja citite si nefolositoare in constructia arcelor
    int neglect = 0;
    for (i = 0; i < 2; i++) {
        fscanf(f, "%d", &neglect);
    }
    float neglect2 = 0;
    fscanf(f, "%f", &neglect2);
    AArc *p, aux, *p2, aux2;
    int indexArc = 0;
    for (i = 0; i < (*R); i++) {
        char sursa[250];
        char destinatie[250];
        fscanf(f, "%s", sursa);
        fscanf(f, "%s", destinatie);
        int indexNodS = 0;
        int indexNodD = 0;
        int j = 0;
        // determin indecsii sursei si ddestinatiei
        for (j = 0; j < nrCrtNoduri; j++) {
            if (strcmp(sursa, noduri[j].denumire) == 0) {
                indexNodS = noduri[j].index;
            }
            if (strcmp(destinatie, noduri[j].denumire) == 0) {
                indexNodD = noduri[j].index;
            }
        }
        int nrTronsoane = 0;
        fscanf(f, "%d", &nrTronsoane); //citesc nr de tronsoane coresp arcului
        //aloc arcul direct, completand informatiile necesare
        p = g->x + indexNodS;
        while (*p && (*p)->d < indexNodD) p = &(*p)->urm;
        aux = (TCelArc*)calloc(sizeof(TCelArc),1);
        if (!aux) {
        DistrG(&g); return NULL;
        }                     
        aux->urm = *p; *p = aux;
        aux->d = indexNodD;
        aux->nrTronsoane = nrTronsoane;
        aux->indexArc = indexArc; //salvez ordinea in care sunt citite arcele pentru a le putea afisa in ordine
        indexArc++;
        aux->c = (float *)malloc( nrTronsoane * sizeof(float)); //aloc vectorul in care salvez uzura fiecarui tronson
        for (j = 0; j < nrTronsoane; j++) {
            fscanf(f, "%f", &aux->c[j]);
        }
        //alocul arcul invers, completand informatiile necesare
        p2 = g->x + indexNodD;
        while (*p2 && (*p2)->d < indexNodS) p2 = &(*p2)->urm;
        aux2 = (TCelArc*)calloc(sizeof(TCelArc),1);
        if (!aux2) {
        DistrG(&g); return NULL;
        }                     
        aux2->urm = *p2; *p2 = aux2;
        aux2->d = indexNodS;
        aux2->nrTronsoane = nrTronsoane;
        aux2->indexArc = -1; // marchez cu -1 arcul invers pentru a ma asigura ca in anumite situatii nu modific de 2 ori acelasi arc
        aux2->c = (float *)malloc( nrTronsoane * sizeof(float));
        for (j = 0; j < nrTronsoane; j++) {
            aux2->c[j] = aux->c[nrTronsoane - j - 1]; //salvez valorile in ordine inversa fata de arcul direct
        }
    }
    fclose(f);
    return g;
}
