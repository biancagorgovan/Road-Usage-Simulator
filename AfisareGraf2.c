/*GORGOVAN Bianca Maria 314CB*/
#include "functii2.h"

void afisareGraf2(ArcVector2 *arcBun, TAsociereNr2 *noduri, FILE *fout, int *K) {
    // Sortare vector de arce dupa indexArc (presupunând ca indexArc reflecta ordinea introducerii)
    qsort(arcBun, *K, sizeof(ArcVector2), comparaArce2);
    fprintf(fout, "%d\n", *K); //printez nr de cai ferate pe care le putem opri
    // Afisare arce
    int i = 0;
    for (i = 0; i < *K; i++) {
        ArcVector2 arc = arcBun[i];
        fprintf(fout, "%s %s\n", noduri[arc.sursa].denumire, noduri[arc.destinatie].denumire); 
        //in functie de indexul sursei/destinatiei arcului curent, restabilim denumirea din vectorul "dictionar" noduri
    }

    // Dezalocare memorie pentru vectorul de arce
}