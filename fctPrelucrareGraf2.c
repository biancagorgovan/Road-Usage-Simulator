/*GORGOVAN Bianca Maria 314CB*/
#include "functii2.h"

TGL2* AlocG2(int nr) /* aloca spatiu pentru descriptor graf si
	                      vector de (n+1) adrese liste arce */
{
  TGL2* g = (TGL2*)malloc(sizeof(TGL2));    /* spatiu descriptor */
  if (!g) return NULL;
  g->x = (AArc2*)calloc((nr+1), sizeof(AArc2)); /* spatiu vector adr.liste arce */
  if(!g->x) { free(g); return NULL; }
  g->n = nr;
  return g;
}

void DistrG2(TGL2** g) {
    //se dezaloca memoria ocupata de graf
    int i;
    for (i = 0; i < (*g)->n; i++) {
        AArc2 p = (*g)->x[i];
        while (p) {
            AArc2 aux = p;
            p = p->urm;
            free(aux);
        }
    }
    free((*g)->x);
    free(*g);
    *g = NULL;
}

TGL2* ConstrGraf2(char numefis[250], int *K, char oras_start[250], int *M, TAsociereNr2 *noduri) {
    FILE *f = fopen (numefis, "rt");
    if (!f) return NULL;
    int nrCrtNoduri = 0;
    fscanf(f, "%s", oras_start); //se citeste denumirea orasului de start
    fscanf(f, "%d", K); //se citeste nr max de cai ce pot fi pastrate
    fscanf(f, "%d", M); // se nr de arce 
    int i = 0;
    for (i = 0; i < (*M); i++) {
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
        int c = 0;
        fscanf(f, "%d", &c);
    }
    fclose(f);
    // redeschid fisierul de citire, pt a ma asigura ca sunt la inceputul lui ca sa pot sa stabilesc arcele intre nodurile codificate
    f = fopen (numefis, "rt");
    if (!f) return NULL;
    TGL2 *g = AlocG2(nrCrtNoduri); //aloc graful in fct de nr de noduri det
    if (!g) return 0;
    //consum caracterele deja citite si nefolositoare in constructia arcelor
    char neglect[250];
    fscanf(f, "%s", neglect);
    int neglect2 = 0;
    for (i = 0; i < 2; i++) {
        fscanf(f, "%d", &neglect2);
    }
    AArc2 *p, aux, *p2, aux2;
    int indexArc = 0;
    for (i = 0; i < (*M); i++) {
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
        //aloc arcul direct, completand informatiile necesare
        p = g->x + indexNodS;
        while (*p && (*p)->d < indexNodD) p = &(*p)->urm;
        aux = (TCelArc2*)calloc(sizeof(TCelArc2),1);
        if (!aux) {
        DistrG2(&g); return NULL;
        }                     
        aux->urm = *p; *p = aux;
        aux->indexArc = indexArc; //salvez ordinea in care sunt citite arcele pentru a le putea afisa in ordine
        indexArc++;
        int c = 0;
        fscanf(f, "%d", &c);
        aux->c = c;
        aux->d = indexNodD;
        //alocul arcul invers, completand informatiile necesare
        p2 = g->x + indexNodD;
        while (*p2 && (*p2)->d < indexNodS) p2 = &(*p2)->urm;
        aux2 = (TCelArc2*)calloc(sizeof(TCelArc2),1);
        if (!aux2) {
        DistrG2(&g); return NULL;
        }                     
        aux2->urm = *p2; *p2 = aux2;
        aux2->d = indexNodS;
        aux2->indexArc = -1; // marchez cu -1 arcul invers pentru a ma asigura ca in anumite situatii nu modific de 2 ori acelasi arc
        aux2->c = c;
    }
    fclose(f); // ma asigur ca inchid fisierul de citire
    return g; //returnez graficul nou creat
}
