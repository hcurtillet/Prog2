// fichier fifo.h pour l'implantation du TAD File au moyen d'une liste chaînée circulaire
#ifndef FIFO_H_
#define FIFO_H_
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "element.h" // on suppose que le type element_t est déclaré dans ce fichier

// 1. le type fifo_t est défini comme "pointeur sur maillon"
typedef struct _fifolink {
  element_t val; /* un élément de la liste*/
  struct _fifolink *next; /* l'adresse du maillon suivant */
} * fifo_t;

// 2. prototypes des fonctions de l'API du TAD File

// Crée et retourne un file vide
fifo_t fifo_new();

// Retourne 1 si la file  queue   est vide, 0 sinon
int fifo_is_empty(fifo_t queue);

// Ajoute l'élément e à la file  queue  et retourne la nouvelle file
// Retourne NULL en cas d'erreur
fifo_t fifo_enqueue(element_t e, fifo_t queue);

// Retourne l'élément en tête de file (sans l'enlever de la file)
// PRECONDITION : la file  queue  ne doit pas être vide
element_t fifo_peek(fifo_t queue);

// Enlève l'élément en tête de la file, et retourne la file
// PRECONDITION : la file pointée par  f  ne doit pas être vide
fifo_t fifo_del_head(fifo_t queue);

// Enlève l'élément en tête de la file, et retourne cet élément
// PRECONDITION : la file pointée par  p_queue  ne doit pas être vide
element_t fifo_dequeue(fifo_t * p_queue);
    // Remarque sur le prototype de fifo_dequeue() :
    // Cette fonction doit "retourner" 2 choses :
    //  - l'élément qui était en tête
    //  - et la file modifiée, dont on enlevée l'ancienne tête
    // Il faut donc, en C, utiliser un passage par adresse pour l'une
    // de ces deux valeurs (ici : la file)

// Détruit la file et retourne une file vide
fifo_t fifo_delete(fifo_t queue);


// FONCTION optionnelle : affiche tous les éléments de la file, dans l'ordre
void fifo_print(fifo_t queue);

// FONCTION optionnelle : compte le nombre d'éléments dans la file
int fifo_length(fifo_t queue);

#endif
