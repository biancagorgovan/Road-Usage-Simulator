/*GORGOVAN Bianca Maria 314CB*/
#include "functii.h"
void ModificareUzura(int K, TGL *g) {
    int k, i, j, l;

    for (k = 0; k < K; k++) {
        //imi creez o copie a grafului inainte de fiecare modificare
        TGL *gCopy = AlocG(g->n);
        for (i = 0; i < g->n; i++) {
            gCopy->x[i] = NULL;
            AArc arc = g->x[i];
            AArc prev = NULL;
            while (arc) {
                AArc newArc = (AArc)malloc(sizeof(TCelArc));
                memcpy(newArc, arc, sizeof(TCelArc));
                newArc->urm = NULL;

                // Copiaza gradele de uzura
                newArc->c = (float *)malloc(arc->nrTronsoane * sizeof(float));
                memcpy(newArc->c, arc->c, arc->nrTronsoane * sizeof(float));
                newArc->indexArc = arc->indexArc;
                newArc->nrTronsoane = arc->nrTronsoane;
                newArc->d = arc->d;
                if (prev) {
                    prev->urm = newArc;
                } else {
                    gCopy->x[i] = newArc;
                }

                prev = newArc;
                arc = arc->urm;
            }
        }

        // Dublam uzura pentru fiecare tronson în graful initial g
        for (i = 0; i < g->n; i++) {
            AArc arc = g->x[i];
            while (arc) {
                if (arc->indexArc != -1) {
                    for (j = 0; j < arc->nrTronsoane; j++) {
                        // Dublam gradul de uzura daca este mai mic de 100%
                        if (arc->c[j] < 100.0) {
                            arc->c[j] *= 2;
                            if (arc->c[j] > 100.0) {
                                arc->c[j] = 100.0;
                            }
                        }
                    }
                }
                arc = arc->urm;
            }
        }

        // Aplica regulile speciale pentru tronsoanele cu grad de uzura 0
        for (i = 0; i < gCopy->n; i++) {
            AArc arcCopy = gCopy->x[i];
            AArc arcOriginal = g->x[i];

            while (arcCopy) {
                if (arcCopy->indexArc != -1) {
                    for (j = 0; j < arcCopy->nrTronsoane; j++) {
                        if (arcCopy->c[j] == 0) {
                            float maxUzuraVecin = 0.0;

                            // Verifica uzura vecinilor din acelasi arc
                            if (j > 0 && arcCopy->c[j - 1] > maxUzuraVecin) {
                                maxUzuraVecin = arcCopy->c[j - 1];
                            }
                            if (j < arcCopy->nrTronsoane - 1 && arcCopy->c[j + 1] > maxUzuraVecin) {
                                maxUzuraVecin = arcCopy->c[j + 1];
                            }
                            int lastIndex = arcCopy->nrTronsoane - 1;
                            if (j == lastIndex) {
                                int dest = arcCopy->d;
                                // Verifica uzura vecinilor din alte arce care pleaca din acelasi nod
                                AArc arcVecin = gCopy->x[dest];
                                while (arcVecin) {
                                    if (arcVecin->d != i && arcVecin->nrTronsoane > 0) {
                                        if (arcVecin->c[0] > maxUzuraVecin) {
                                            maxUzuraVecin = arcVecin->c[0]; //in caz de maxim, se ia val din primul tronson
                                        }
                                    }
                                    arcVecin = arcVecin->urm;
                                }
                                // Verifica uzura vecinilor din arcele care ajung în acest nod
                                for (l = 0; l < gCopy->n; l++) {
                                    if (l != i) {
                                        AArc arcInvers = gCopy->x[l];
                                        while (arcInvers) {
                                            if (arcInvers->d == dest && arcInvers->nrTronsoane > 0) {
                                                int lastTronsonIndex = arcInvers->nrTronsoane - 1;
                                                if (arcInvers->c[lastTronsonIndex] > maxUzuraVecin) {
                                                    maxUzuraVecin = arcInvers->c[lastTronsonIndex]; //in caz de maxim, se ia val din ultimul tronson
                                                }
                                            }
                                            arcInvers = arcInvers->urm;
                                        }
                                    }
                                }
                            }
                            if (j == 0) {
                                // Verifica uzura vecinilor din alte arce care pleaca din acelasi nod
                                AArc arcVecin = gCopy->x[i];
                                while (arcVecin) {
                                    if (arcVecin != arcCopy && arcVecin->nrTronsoane > 0) {
                                        if (arcVecin->c[0] > maxUzuraVecin) {
                                            maxUzuraVecin = arcVecin->c[0]; //in caz de maxim, se ia val din primul tronson
                                        }
                                    }
                                    arcVecin = arcVecin->urm;
                                }
                                // Verifica uzura vecinilor din arcele care ajung în acest nod
                                for (l = 0; l < gCopy->n; l++) {
                                    if (l != i) {
                                        AArc arcInvers = gCopy->x[l];
                                        while (arcInvers) {
                                            if (arcInvers->d == i && arcInvers->nrTronsoane > 0) {
                                                int lastTronsonIndex = arcInvers->nrTronsoane - 1;
                                                if (arcInvers->c[lastTronsonIndex] > maxUzuraVecin) {
                                                    maxUzuraVecin = arcInvers->c[lastTronsonIndex]; //in caz de maxim, se ia val din ultimul tronson
                                                }
                                            }
                                            arcInvers = arcInvers->urm;
                                        }
                                    }
                                }
                            }
                            if (maxUzuraVecin > 0) {
                                // Actualizeaza gradul de uzura în graful orginal, "de baza"
                                arcOriginal->c[j] = maxUzuraVecin / 2;
                            }
                        }
                    }
                }
                arcCopy = arcCopy->urm;
                arcOriginal = arcOriginal->urm;
            }
        }
        // Dezaloca memoria pentru graful copie si gradul de uzura
        for (i = 0; i < gCopy->n; i++) {
            AArc arc = gCopy->x[i];
            while (arc) {
                AArc next = arc->urm;
                free(arc->c); // Dezaloca memoria pentru gradul de uzura
                free(arc);    // Dezaloca memoria pentru arc
                arc = next;
            }
        }
        free(gCopy->x);   // Dezaloca memoria pentru vectorul de arce
        free(gCopy);      // Dezaloca memoria pentru graful copie
    }
}
