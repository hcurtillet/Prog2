#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graphe_lecture.h"

typedef struct _fifolink { //structure pour les files
  int val; /* un élément de la liste*/
  struct _fifolink *next; /* l'adresse du maillon suivant */
} * fifo_t;


// Cette fonction ajoute un élément à la liste, la liste correspondant à un sommet
listedge_t addElement(edge_t * element, listedge_t list);

// Cette fonction permet de lire une liste d'éléments, les éléments sont des arêtes du graphe
void list_print(listedge_t l);

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
