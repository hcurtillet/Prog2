#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>
#include <string.h>
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

typedef struct maillon_chemin{
  int val;
  struct maillon_chemin * next;
}
* chemin_t;
// Type sommet
typedef struct {
int numero;
char* nom;
char* ligne;
double x,y;
listedge_t edges;
double pcc;
int father;
char in_fifo; //permet de signaler si un somme est ou pas dans la file
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

// Cette fonction a pour objectif de créer un nouveau graphe à partir d'un fichier donné
graph_t* creationGraph(char* fName);


// Cette fonction alloue dynamiquement un graphe d'une taille donnée
graph_t* newGraph(int nbSommet, int nbArc);


// Cette fonction affiche de façon textuelle d'un graphe donné
void graphPrint(graph_t * graphe);
