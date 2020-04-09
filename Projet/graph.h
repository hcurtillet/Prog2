#include <stdio.h>
#include <stdlib.h>
// Type arc
typedef struct {
int depart, arrivee;
double cout;
} edge_t;
// Les indices des sommets de depart et d’arrivee de l’arc
// Le cout de l’arc
// Type liste chainée d’arcs
typedef struct maillon_edge {
edge_t val;
// ou edge t* val, suivant votre choix : liste d’arcs ou de pointeurs d’arcs
struct maillon_edge * next;
}* listedge_t;
// Type sommet
typedef struct {
int numero;
char* nom;
char* ligne;
double x,y;
listedge_t edges;
double pcc;
/*
indice du sommet
Nom donne au sommet
Nom de la ligne, uniquement pour pour le metro
coordonnees latitude et longitude du sommet pour le graphqie
Liste des arcs qui partent de ce sommet
"plus court chemin" entre le sommet de depart et ce sommet.
N’est utile que durant le déroulé de l’algorithme.*/
} vertex_t;
// Type graphe :
typedef struct {
int size_vertex;
int size_egdes;
vertex_t* data;
} graph_t;
// Nombre de sommets
// Nombre d’arcs
// Tableau des sommets alloue dynamiquement


graph_t* creationGraph(char* fName);

listedge_t addElement(edge_t * element, listedge_t list);

graph_t* newGraph(int nbSommet, int nbArc);

void list_print(listedge_t l);

void graphPrint(graph_t * graphe);

void edgePrint(edge_t *element);
