.PHONY: build run clean
build:
	gcc -g -Wall -Wextra -std=c99 -o tema3 main.c functiiPrelucrare.c functiiAfisare.c functieSimulareUzura.c AfisareGraf2.c fctPrelucrareGraf2.c DistanteMinDijkstra.c

clean:
	rm tema3

valgrind:
	valgrind --leak-check=yes --track-origins=yes ./tema3 $(ARGS)