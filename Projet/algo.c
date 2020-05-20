#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
int ParcoursEnProfondeur(int depart, int arrivee, graph_t graphe){
    if (depart == arrivee){
      return 1; // on a trouver l'arrivée, on retourne 1
    }
    else{
      int trouve = 0; //On initialie trouve au début, trouve est propre au noeud en cours
      listedge_t p = (graphe.data)[depart].edges;
      if (p != NULL){
          while (p != NULL){
              double DistTemp;
              DistTemp = (graphe.data)[depart].pcc + (p->val).cout;
              if ((DistTemp < (graphe.data)[(p->val).arrivee].pcc) && ((DistTemp < (graphe.data)[arrivee].pcc))){
                  (graphe.data)[(p->val).arrivee].pcc = DistTemp;
                  (graphe.data)[(p->val).arrivee].father = depart;
                  int trouve2 = ParcoursEnProfondeur((p->val).arrivee, arrivee,graphe);
                  if (trouve2 == 1){ /* On actualise la variable trouve uniquement pour la passer à 1.
                  En effet si le premier chemin fonctionne, trouve va passer à 1, mais si un chemin suivit plus tard
                  dans l'exécution du code ne fonctionne pas,trouve ne doit pas passer à 0
                  au risque de retourner 0 si le dernier chemin ne fonctionne pas*/
                      trouve = trouve2;
                  }
              }
              p=p->next;
          }
       }
       return trouve;
    }
}

int ParcoursEnLargeur(int depart, int arrivee, graph_t graphe){
    fifo_t file = fifo_new();
    graphe = InitGraphe(depart, graphe);
    file=fifo_enqueue(depart, file);
    (graphe.data)[depart].in_fifo=1;
    while(!fifo_is_empty(file)){
        int sommet;
        sommet = fifo_dequeue(&file);
        listedge_t p = (graphe.data)[sommet].edges;
        while (p != NULL){
            double DistTemp;
            DistTemp = (graphe.data)[sommet].pcc + (p->val).cout;
            if ((DistTemp < (graphe.data)[(p->val).arrivee].pcc) && ((DistTemp < (graphe.data)[arrivee].pcc))){
                (graphe.data)[(p->val).arrivee].pcc = DistTemp;
                (graphe.data)[(p->val).arrivee].father = sommet;
                if ((graphe.data)[(p->val).arrivee].in_fifo == 0){
                    file=fifo_enqueue((p->val).arrivee, file);
                    (graphe.data)[(p->val).arrivee].in_fifo =1;
                }
            }
            p=p->next;
            }
    }
    if ((graphe.data)[arrivee].pcc!=INFINITY){
       return 1;
    }
    else{
        return 0;
    }
}

int Dijkstra_like(int depart, int arrivee, graph_t graphe){
    heap_t heap = heap_new(graphe.size_vertex);
    graphe = InitGraphe(depart, graphe);
    heap_add(depart, &heap, graphe);
    (graphe.data)[depart].in_heap=1;
    while(!heap_is_empty(heap) && ((graphe.data)[arrivee].pcc == INFINITY)){
        int sommet;
        sommet = heap_get_top(&heap,graphe);
        (graphe.data)[sommet].in_heap=0;
        listedge_t p = (graphe.data)[sommet].edges;
        if (p != NULL){
          while (p != NULL){
              double DistTemp;
              DistTemp = (graphe.data)[sommet].pcc + (p->val).cout;
              if ((DistTemp < (graphe.data)[(p->val).arrivee].pcc) && ((DistTemp < (graphe.data)[arrivee].pcc))){
                  (graphe.data)[(p->val).arrivee].pcc = DistTemp;
                  (graphe.data)[(p->val).arrivee].father = sommet;
                  if ( (graphe.data)[arrivee].in_heap==0){
                    heap_add(sommet, &heap, graphe);
                  }
                  else{
                      heap = heap_sort(heap, graphe);
                  }
              }
              p=p->next;
              }

        }

    }
    if ((graphe.data)[arrivee].pcc!=INFINITY){
       return 1;
    }
    else{
        return 0;
    }
}


graph_t  InitGraphe(int depart, graph_t graphe){
  int i, size;
  size = graphe.size_vertex;
  for (i = 0; i < size; i++){ // On initialise les valeur de pcc à l'infini pour chaque noeud à l'exception du départ initialisé à 0
    (graphe.data)[i].pcc=INFINITY;
    (graphe.data)[i].father=-1; // la variable father nous permet de reconstruire le chemin en associant la provenance du pcc actuel
    (graphe.data)[i].in_fifo=0;
    (graphe.data)[i].in_heap=0;
  }
  (graphe.data)[depart].pcc=0;
  return graphe;
}

chemin_t LectureDeChemin(int depart, int arrivee, graph_t graphe){ // on crée une liste contenant les noeuds utilisée dans l'ordre. On utilise la variable father pour cela
    chemin_t chemin=NULL;
    int elementEnCours = arrivee;
    do{
      chemin_t add = calloc (1, sizeof (*add));
      if ( add == NULL){printf("Problème dans l'allocation du maillons\n"); exit(EXIT_FAILURE);}
      add->val = elementEnCours;
      add->next = chemin;
      chemin=add;
      elementEnCours = graphe.data[elementEnCours].father;
    }while(elementEnCours != depart);
    chemin_t add = calloc (1, sizeof (*add));
    if ( add == NULL){printf("Problème dans l'allocation du maillons\n"); exit(EXIT_FAILURE);}
    add->val = elementEnCours;
    add->next = chemin;
    chemin=add;
    elementEnCours = graphe.data[elementEnCours].father;
    return chemin;
}

void printChemin( chemin_t chemin, graph_t graphe){
    chemin_t p;
    p = chemin;
    vertex_t elementEnCours;
    printf("Voici le chemin le plus efficace\n");
    printf("----------------------------------------------------------------------------\n");
    if (p != NULL){
        while( p != NULL){
          printf(" Valeur de p %d\n",p->val);
          elementEnCours = graphe.data[p->val];
          printf("Passer par %s de la ligne %s\n", elementEnCours.nom, elementEnCours.ligne);
          if (p->next == NULL){
            printf("Le cout est de %lf\n\n", elementEnCours.pcc);
          }
          p=p->next;
        }
    }
    printf("----------------------------------------------------------------------------\n");
}
