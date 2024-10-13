Constructia Grafului

Construcaia grafului începe cu citirea fisierului de intrare tema3.in. Fisierul conaine numarul de rute, numarul de ani pentru simulare si gradul maxim de uzura permis. Pe baza acestor date:
Asocierea Nodurilor: Nodurile sunt asociate cu indici folosind structura TAsociereNr.
Alocarea Arcelor: Pentru fiecare ruta, se aloca dinamic memoria necesara pentru a stoca tronsoanele si uzura acestora folosind structura TCelArc.
Construirea Listei de Adiacenta: Graful este construit utilizând o lista de adiacenaa pentru fiecare nod, pastrând toate arcele care pleaca din acel nod.
Simularea Uzurii

Simularea uzurii se efectueaza pe parcursul mai multor ani, conform specificatiilor din fisierul de intrare:
Dublarea Uzurii: Pentru fiecare tronson din fiecare arc, uzura se dubleaza anual daca aceasta este sub 100%.
Reguli pentru Uzura Zero: Daca un tronson are uzura iniaiala de 0%, uzura sa se actualizeaza în funcaie de uzura tronsoanelor vecine. Aceasta se calculeaza ca maxim a uzurii tronsoanelor anterioare si urmatoare.

Determinarea Rutelor de Pastrat
Dupa simularea uzurii, se determina care rute merita pastrate:
Calcularea Mediei de Uzura: Pentru fiecare arc, se calculeaza media uzurii tronsoanelor.
Filtrarea Rutelor: Rutele a caror uzura medie este sub pragul specificat sunt considerate ca fiind optime si sunt pastrate.
Sortarea Indecsilor: Indicii acestor rute sunt sortaai în ordinea iniaiala si scrisi în fisierul de iesire tema3.out.

Afisarea Grafului cu Uzura
Graful modificat este afisat, prezentând sursa, destinaaia, numarul de tronsoane si uzura fiecarui tronson pentru fiecare arc. Aceasta permite o vizualizare clara a efectului uzurii asupra grafului pe parcursul anilor.

CERINTA 2

Functiile AlocG2, DistrG2, ConstrGraf2 - similar cerinta 1

Functia dijkstra
Aceasta funcaie implementeaza algoritmul Dijkstra pentru a calcula drumurile minime de la un nod sursa la toate celelalte noduri din graf. Algoritmul utilizeaza un vector de distanae si un vector de parinai pentru a reaine drumul minim si parintii fiecarui nod pe acest drum.
Parametri:
graph: Pointer catre structura grafului.
src: Indexul nodului sursa.
dist: Vector de distanae minime de la nodul sursa la fiecare nod.
parent: Vector care conaine parinaii fiecarui nod în drumul minim

Functia arceDijkstra
Aceasta funcaie marcheaza arcele care fac parte din drumurile minime. Pentru fiecare nod, se verifica arcele care conecteaza nodul curent cu parintele sau în drumul minim. Daca un arc este gasit, acesta este marcat ca necesar si se actualizeaza distanta maxima dintre drumurile minime din care face parte.
Parametri:
parent: Vectorul de parinai rezultat din algoritmul Dijkstra.
dist: Vectorul de distanae rezultat din algoritmul Dijkstra.
src: Indexul nodului sursa.
arce: Vectorul de arce al grafului.
V: Numarul de noduri din graf.
M: Numarul de arce din graf.

Functia colectareArce2
Aceasta funcaie colecteaza arcele din graf si le stocheaza într-un vector. Funcaia parcurge graful si salveaza informaaiile fiecarui arc într-un vector de structuri ArcVector2.

Functia SelectieArce
Aceasta funcaie selecteaza un numar maxim de arce astfel încât sa pastreze drumurile minime. Daca numarul de arce necesare depaseste numarul maxim permis (K), funcaia sorteaza arcele dupa distanaa maxima si selecteaza primele K arce.
Parametri:
count: Numarul de arce necesare.
arce: Vectorul de arce.
K: Pointer catre numarul maxim de arce care pot fi pastrate.
M: Pointer catre numarul de arce din graf.
arcBun: Vectorul de arce care vor fi pastrate.

Functia afisareGraf2
Aceasta funcaie afiseaza arcele selectate în fisierul de iesire. Arcele sunt sortate dupa indexul de introducere si apoi afisate în ordinea iniaiala a citirii.
