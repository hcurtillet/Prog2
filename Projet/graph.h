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



typedef struct _fifolink { //structure pour les files
  int val; /* un élément de la liste*/
  struct _fifolink *next; /* l'adresse du maillon suivant */
} * fifo_t;

// Cette fonction a pour objectif de créer un nouveau graphe à partir d'un fichier donné
graph_t* creationGraph(char* fName);

// Cette fonction ajoute un élément à la liste, la liste correspondant à un sommet
listedge_t addElement(edge_t * element, listedge_t list);

// Cette fonction alloue dynamiquement un graphe d'une taille donnée
graph_t* newGraph(int nbSommet, int nbArc);

// Cette fonction permet de lire une liste d'éléments, les éléments sont des arêtes du graphe
void list_print(listedge_t l);

// Cette fonction affiche de façon textuelle d'un graphe donné
void graphPrint(graph_t * graphe);

// Cette fonction a pour objectif de trouver le plus court chemin entre le sommet de départ et le sommet d'arrivé
// en utilisant un algorithme Depth First Search
int ParcoursEnProfondeur(int depart, int arrivee, graph_t graphe);

// Cette fonction permet d'initialiser les valeurs de cout des sommets du graphe, 0 pour le départ et + l'infini pour les autres
graph_t  InitGraphe(int depart, graph_t graphe);

// Cette fonction a pour utilité de créer une liste représentant le chemin le plus court parcouru pour aller du départ à l'arrivée
chemin_t LectureDeChemin(int depart, int arrivee, graph_t graphe);

// Cette fonction affiche correctement un chemin donnée
void printChemin( chemin_t chemin, graph_t graphe);

// Cette fonction utilise l'algotithme BFS afin de trouver le chemin qle plus efficace
int ParcoursEnLargeur(int depart, int arrivee, graph_t graphe);




// fonction de gestion de files

// Crée et retourne un file vide
fifo_t fifo_new();

// Retourne 1 si la file  queue   est vide, 0 sinon
int fifo_is_empty(fifo_t queue);

// Ajoute l'élément e à la file  queue  et retourne la nouvelle file
// Retourne NULL en cas d'erreur
fifo_t fifo_enqueue(int e, fifo_t queue);

// Retourne l'élément en tête de file (sans l'enlever de la file)
// PRECONDITION : la file  queue  ne doit pas être vide
int fifo_peek(fifo_t queue);

// Enlève l'élément en tête de la file, et retourne la file
// PRECONDITION : la file pointée par  f  ne doit pas être vide
fifo_t fifo_del_head(fifo_t queue);

// Enlève l'élément en tête de la file, et retourne cet élément
// PRECONDITION : la file pointée par  p_queue  ne doit pas être vide
int fifo_dequeue(fifo_t * p_queue);
    // Remarque sur le prototype de fifo_dequeue() :
    // Cette fonction doit "retourner" 2 choses :
    //  - l'élément qui était en tête
    //  - et la file modifiée, dont on enlevée l'ancienne tête
    // Il faut donc, en C, utiliser un passage par adresse pour l'une
    // de ces deux valeurs (ici : la file)
