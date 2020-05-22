#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
int ParcoursEnProfondeur(int depart, int arrivee, graph_t graphe){
    if (depart >= graphe.size_vertex || arrivee >= graphe.size_vertex ){
        printf("Les sommets demandés ne sont pas dans le graphe");
        return 0;
    }
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
              int sommetArrive = (p->val).arrivee;
              if ((DistTemp < (graphe.data)[sommetArrive].pcc) && ((DistTemp < (graphe.data)[arrivee].pcc))){
                  (graphe.data)[sommetArrive].pcc = DistTemp;
                  (graphe.data)[sommetArrive].father = depart;
                  int trouve2 = ParcoursEnProfondeur(sommetArrive, arrivee,graphe);
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
    if (depart >= graphe.size_vertex || arrivee >= graphe.size_vertex ){
        printf("Les sommets demandés ne sont pas dans le graphe");
        return 0;
    }
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
            int sommetArrive = (p->val).arrivee;
            if ((DistTemp < (graphe.data)[sommetArrive].pcc) && ((DistTemp < (graphe.data)[arrivee].pcc))){
                (graphe.data)[sommetArrive].pcc = DistTemp;
                (graphe.data)[sommetArrive].father = sommet;
                if ((graphe.data)[sommetArrive].in_fifo == 0){
                    file=fifo_enqueue(sommetArrive, file);
                    (graphe.data)[sommetArrive].in_fifo =1;
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
    if (depart >= graphe.size_vertex || arrivee >= graphe.size_vertex ){
        printf("Les sommets demandés ne sont pas dans le graphe");
        return 0;
    }
    heap_t heap = heap_new(graphe.size_vertex);
    graphe = InitGraphe(depart, graphe);
    heap_add(depart, &heap, graphe);
    (graphe.data)[depart].in_heap=1;
    while(!heap_is_empty(heap)){
        int sommet;
        sommet = heap_get_top(&heap,graphe);
        (graphe.data)[sommet].in_heap=0;
        /*
        printf("Sommet de départ considéré: %d\n",sommet);
        printf("Affichage du tas:----------------------------------------------------\n");
        heap_print(heap, graphe);
        printf("Fin affichage du tas:----------------------------------------------------\n");
        */
        listedge_t p = (graphe.data)[sommet].edges;
        /*
        int i = 0;
        for (i=0; i<graphe.size_vertex;i++){
            printf("Valeur de présence de %d = %d\n",i, graphe.data[i].in_heap);
        }*/
        if (p != NULL){
          while (p != NULL){
              double DistTemp;
              DistTemp = (graphe.data)[sommet].pcc + (p->val).cout;
              int sommetArrive = (p->val).arrivee;
              //printf("sommet: %d, sommet suivant:%d\n", sommet, (p->val.arrivee));
              //printf("Valleur DistTemp= %lf, valeur pcc arrivee = %lf, valeur de présence= %d\n", DistTemp, (graphe.data)[sommetArrive].pcc,(graphe.data)[sommetArrive].in_heap);
              if ((DistTemp < (graphe.data)[sommetArrive].pcc) && ((DistTemp < (graphe.data)[arrivee].pcc))){
                  //printf("On modifie\n");
                  //printf("Valeur de présence:%d\n",(graphe.data)[sommetArrive].in_heap);
                  (graphe.data)[sommetArrive].pcc = DistTemp;
                  (graphe.data)[sommetArrive].father = sommet;
                  if ( (graphe.data)[sommetArrive].in_heap==0){ // cas ou le sommet n'est pas dans le tas
                    heap_add((graphe.data)[sommetArrive].numero, &heap, graphe); // On l'ajoute
                    (graphe.data)[sommetArrive].in_heap = 1; // on passe l'indicateur de présence à 1
                  }
                  else{ //sinon, le sommet est dans le tas
                      heap = heap_sort(heap, graphe); // on actualise le tas
                    }
              p=p->next;
              }

        }
    }
    if ((graphe.data)[arrivee].pcc==INFINITY){
       return 0;
    }
    else{
        return 1;
    }
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
