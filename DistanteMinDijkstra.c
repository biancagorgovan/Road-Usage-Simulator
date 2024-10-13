/*GORGOVAN Bianca Maria 314CB*/
#include "functii2.h"

int minDistance(int dist[], int sptSet[], int V) {
    int min = INT_MAX, min_index;
    int v = 0;
    // Parcurge toate nodurile pentru a gasi nodul cu cea mai mica distanta
    for (v = 0; v < V; v++)
        if (sptSet[v] == 0 && dist[v] <= min) // Daca nodul nu este inclus în setul procesat si distanta sa este mai mica decat min
            min = dist[v], min_index = v;
    return min_index; //returneaza nodul indexului cu cea mai mica distanta
}

void dijkstra(TGL2 *graph, int src, int *dist, int *parent) {
    int V = graph->n;
    int sptSet[V]; //set de noduri pt care distanta minima este cunoscuta
    int i = 0;
    int count = 0;
    // Initializeaza toate distantele ca infinite si sptSet[] ca false
    for (i = 0; i < V; i++) {
        dist[i] = INT_MAX; 
        sptSet[i] = 0; 
        parent[i]=-1;
    }
    dist[src] = 0; // Distanta nodului sursa la sine este intotdeauna 0
    
    // Gaseste distanta minima pentru toate nodurile
    for (count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet, V); // Alege nodul cu distanaa minima
        sptSet[u] = 1; // Marcheaza nodul ca fiind procesat
        // Actualizeaza valoarea distantei nodurilor adiacente ale nodului ales
        AArc2 itr = graph->x[u];
        while (itr != NULL) {
            int v = itr->d;
            // Actualizeaza dist[v] doar daca nu este în sptSet, exista un drum de la src la v prin u
            if (sptSet[v] == 0 && dist[u] != INT_MAX && dist[u] + itr->c < dist[v]) {
                dist[v] = dist[u] + itr->c;
                parent[v] = u;
            }
            itr = itr->urm;
        }
    }
}

void arceDijkstra(int *parent, int *dist, int src, ArcVector2 *arce, int V, int M) {
    int i = 0;
    int j = 0;
    //iterez prin toate nodurile
    for (i = 0; i < V; i++) {
        //verific ca nu e cazul sursei si ca nodul curent este precedat de un anterior in drumul minim
        if (i != src && parent[i] != -1) {
            // Caut toate arcele care conecteaza nodul curent cu parintele sau
            for (j = 0; j < M; j++) {
                // Verificam daca arcul este fie de la parinte la nod, fie de la nod la parinte
                if ((arce[j].sursa == parent[i] && arce[j].destinatie == i) || 
                    (arce[j].sursa == i && arce[j].destinatie == parent[i])) {
                    arce[j].necesar = 1;  // Marcam arcul ca fiind necesar
                    if (arce[j].maxDist < dist[i]) {
                        arce[j].maxDist = dist[i]; // Actualizam distanaa maxima din care face parte arcul daca distanaa curenta este mai mare
                    }
                    break;
                }
            }
        }
    }
}
void colectareArce2(TGL2 *g, ArcVector2 **arce, int *nrArce) {
    //fct care construieste vectorul de arce
    
    // Alocare memorie pentru vectorul de arce
    *arce = (ArcVector2 *)malloc((*nrArce) * sizeof(ArcVector2));

    // Se parcurge graful, se salveaza info fiecarui arc
    int index = 0;
    for (int i = 0; i < g->n; i++) {
        AArc2 arc = g->x[i];
        while (arc) {
            if (arc->indexArc != -1) {
                (*arce)[index].sursa = i;
                (*arce)[index].destinatie = arc->d;
                (*arce)[index].c = arc->c;
                (*arce)[index].indexArc = arc->indexArc;
                (*arce)[index].necesar = 0;
                (*arce)[index].maxDist = 0;
                index++;
            }
            arc = arc->urm;
        }
    }
}
int comparaArce2(const void *a, const void *b) {
    //fct de comparare a indecsilor de la ordiena citirii, folosita la qsort pt afisare (se face in ord citirii)
    ArcVector2 *arcA = (ArcVector2 *)a;
    ArcVector2 *arcB = (ArcVector2 *)b;
    return arcA->indexArc - arcB->indexArc;
}

int comparaDistMax(const void* a, const void* b) {
    //fct de comparare a dist maxime folosita la qsort
    ArcVector2* arc1 = (ArcVector2*)a;
    ArcVector2* arc2 = (ArcVector2*)b;
    return arc1->maxDist - arc2->maxDist;
}

void SelectieArce(int count, ArcVector2 *arce, int *K, int *M, ArcVector2 *arcBun) {
     //imi construiesc vectorul de arce care trb pastrate, respectiv afisate
     if (count > *K) {
            //daca pt a parcurge toate nodurile cu drumuri de cost minim depasesc nr max K de cai ferat, determin ce elimin
            //trb eliminate caile care fac parte din cele mai lunge drumuri minime pt a pastra intr-adevar varianta minima posibila
            //ordonez arcele dupa cel mai lung drum minim din care fac parte
            qsort(arce, *M, sizeof(ArcVector2), comparaDistMax);
            int i = 0;
            int index = 0;
            //selectam primele K
            for(i = 0; i < *M && index < *K; i++){
                if (arce[i].necesar == 1) {
                    arcBun[index].sursa = arce[i].sursa;
                    arcBun[index].destinatie = arce[i].destinatie;
                    arcBun[index].c = arce[i].c;
                    arcBun[index].indexArc = arce[i].indexArc;
                    arcBun[index].necesar = arce[i].necesar;
                    arcBun[index].maxDist = arce[i].maxDist;
                    index++;
                }
            }
        } else {
            int i = 0;
            int index = 0;
            //toate drumurile minime se realizeaza cu mai putin sau fix K cai ferate, se pastreaza toate
            for(i = 0; i < *M; i++){
                if (arce[i].necesar == 1) {
                    arcBun[index].sursa = arce[i].sursa;
                    arcBun[index].destinatie = arce[i].destinatie;
                    arcBun[index].c = arce[i].c;
                    arcBun[index].indexArc = arce[i].indexArc;
                    arcBun[index].necesar = arce[i].necesar;
                    arcBun[index].maxDist = arce[i].maxDist;
                    index++;
                }
            }
            *K = count;
        }
}
