/*GORGOVAN Bianca Maria 314CB*/
#include "functii.h"
int cmpIndex(const void *a, const void *b) {
    //fct de comparare a indecsilor de la ordiena citirii, folosita la qsort pt afisare (se face in ord citirii)
    int *indexA = (int *)a;
    int *indexB = (int *)b;
    return (*indexA) - (*indexB);
}
void RuteDePastrat(TGL *g, float L, FILE *fout) {
    //functie care afiseaza (in ordinea citirii) indexul rutelor care merita pastrate
    int *rutePastrate = (int *)malloc(g->n * sizeof(int));
    int nrRutePastrate = 0;

    for (int i = 0; i < g->n; i++) {
        AArc arc = g->x[i];
        //pt fiecare arc calzulez media uzurii si determin daca este suficient de mic pt a fi pastrat
        while (arc) {
            if (arc->indexArc != -1) {
                float sumaUzura = 0;
                for (int j = 0; j < arc->nrTronsoane; j++) {
                    sumaUzura += arc->c[j];
                }
                float mediaUzura = sumaUzura / arc->nrTronsoane;
                if (mediaUzura < L) {
                    rutePastrate[nrRutePastrate++] = arc->indexArc + 1; //adaug in vector indexul care trb afisat
                }
            }
            arc = arc->urm;
        }
    }
    qsort(rutePastrate, nrRutePastrate, sizeof(int), cmpIndex); //le ordonez crescator
    //le afisez
    for (int i = 0; i < nrRutePastrate; i++) {
        fprintf(fout, "%d ", rutePastrate[i]);
    }

    free(rutePastrate);
}

void colectareArce(TGL *g, ArcVector **arce, int *nrArce) {
    //fct care construieste vectorul de arce
    // Alocare memorie pentru vectorul de arce
    *arce = (ArcVector *)malloc((*nrArce) * sizeof(ArcVector));

    // A doua parcurgere pentru a colecta arcele
    int index = 0;
    for (int i = 0; i < g->n; i++) {
        AArc arc = g->x[i];
        while (arc) {
            if (arc->indexArc != -1) {
                (*arce)[index].sursa = i;
                (*arce)[index].destinatie = arc->d;
                (*arce)[index].nrTronsoane = arc->nrTronsoane;
                (*arce)[index].c = arc->c;
                (*arce)[index].indexArc = arc->indexArc;
                index++;
            }
            arc = arc->urm;
        }
    }
}
int comparaArce(const void *a, const void *b) {
    //fct de comparare a indecsilor de la ordiena citirii, folosita la qsort pt afisare (se face in ord citirii)
    ArcVector *arcA = (ArcVector *)a;
    ArcVector *arcB = (ArcVector *)b;
    return arcA->indexArc - arcB->indexArc;
}
void afisareGrafCuUzura(TGL *g, TAsociereNr *noduri, FILE *fout, int *R) {
    ArcVector *arce = NULL;

    colectareArce(g, &arce, R);

    // Sortare vector de arce dupa indexArc (presupunând ca indexArc reflecta ordinea introducerii)
    qsort(arce, *R, sizeof(ArcVector), comparaArce);

    // Afisare arce
    for (int i = 0; i < *R; i++) {
        ArcVector arc = arce[i];
        fprintf(fout, "%s %s %d ", noduri[arc.sursa].denumire, noduri[arc.destinatie].denumire, arc.nrTronsoane);
        for (int j = 0; j < arc.nrTronsoane; j++) {
            float uzura = arc.c[j];
            fprintf(fout, "%.2f ", uzura);
        }
        fprintf(fout, "\n");
    }

    // Dezalocare memorie pentru vectorul de arce
    free(arce);
}