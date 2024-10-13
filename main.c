/*GORGOVAN Bianca Maria 314CB*/
#include "functii.h"
#include "functii2.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    int cerinta = atoi(argv[1]); //determin ce argumente se primeste, respectiv ce cerinta se rezolva
    if (cerinta == 1) {
        char numefis[250];
        strcpy(numefis, "tema3.in");
        int *K = (int *)malloc(1*sizeof(int));
        float *L = (float *)malloc(1*sizeof(float));
        int *R = (int *)malloc(1*sizeof(int));
        TAsociereNr *noduri = (TAsociereNr *)malloc(50 * sizeof(TAsociereNr));
        TGL *g = ConstrGraf(numefis, K, L, R, noduri); //construiesc graful
        ModificareUzura(*K, g); //simulez uzura pe arcele mele
        FILE *fout = fopen("tema3.out", "wt");
        afisareGrafCuUzura(g, noduri, fout, R); //afisez rezultatul obtinut dupa simularea uzurii
        RuteDePastrat(g, *L, fout); //afisez indexul rutelor care merita pastrate
        //eliberez memeoria
        free(noduri);
        free(K);
        free(L);
        free(R);
        DistrG(&g);
        fclose(fout);
    } else if (cerinta == 2) {
        char numefis[250];
        strcpy(numefis, "tema3.in");
        int *K = (int *)malloc(1*sizeof(int));
        int *M = (int *)malloc(1*sizeof(int));
        char oras_start[250];
        TAsociereNr2 *noduri = (TAsociereNr2 *)malloc(50 * sizeof(TAsociereNr));
        TGL2 *g = ConstrGraf2(numefis, K, oras_start, M, noduri); //cosntruiesc graful 
        int i = 0, indexOrasStart = 0;
        int n = g->n;
        //determin indexul orasului pt care calculez distante
        for (i = 0; i < n; i++) {
            if (strcmp(oras_start, noduri[i].denumire) == 0) {
                indexOrasStart = noduri[i].index;
                break;
            }
        }
        FILE *fout = fopen("tema3.out", "wt");
        int *dist = (int *)malloc(n*sizeof(int));
        int *parent = (int *)malloc(n*sizeof(int));
        //determin vectorul cu distante minime
        dijkstra(g, indexOrasStart, dist, parent);
        ArcVector2 *arce = NULL;
        colectareArce2(g, &arce, M); //construiesc vectorul de arce din graf
        arceDijkstra(parent, dist, indexOrasStart, arce, n, *M); //determin arcele cu care se obtin distante minime
        int count = 0;
        //determin nr de arce cu care se realizeaza toate distantele minime
        for (i = 0; i < *M; i ++) {
            if (arce[i].necesar == 1) {
                count++;
            }
        }
        ArcVector2 *arcBun = (ArcVector2 *)malloc((*K)*sizeof(ArcVector2));
        SelectieArce(count, arce, K, M, arcBun); //determin vectorul de arce care pot fi pastrate
        afisareGraf2(arcBun, noduri, fout, K); // afisez arcele determinate
        //eliberez memoria
        free(K);
        free(M);
        free(noduri);
        free(dist);
        free(parent);
        DistrG2(&g);
        free(arce);
        free(arcBun);
        fclose(fout);
    }
    return 0;
}
