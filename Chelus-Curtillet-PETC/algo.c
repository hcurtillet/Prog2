#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
int ParcoursEnProfondeur(int depart, int arrivee, graph_t graphe){
    if (depart >= graphe.size_vertex || arrivee >= graphe.size_vertex ){ // on vérifiera toujours que les indices des sommets cherchés sont dans le graphe
        printf("Les sommets demandés ne sont pas dans le graphe");
        return 0;
    }
    if (depart == arrivee){
      return 1; // on a trouver l'arrivée, on retourne 1
    }
    else{
      int trouve = 0; //On initialie trouve au début, trouve est propre au noeud en cours
      listedge_t p = (graphe.data)[depart].edges;
      if (p != NULL){ // on parcoure la liste des arcs
          while (p != NULL){
              double DistTemp;
              DistTemp = (graphe.data)[depart].pcc + (p->val).cout;
              int sommetArrive = (p->val).arrivee; // On créer une variable contenant l'indice du sommet d'arrivé de l'arc pour plus de lisibilié dans le code
              if ((DistTemp < (graphe.data)[sommetArrive].pcc) && ((DistTemp < (graphe.data)[arrivee].pcc))){
                  (graphe.data)[sommetArrive].pcc = DistTemp;
                  (graphe.data)[sommetArrive].father = depart;
                  int trouvetmp = ParcoursEnProfondeur(sommetArrive, arrivee,graphe);
                  if (trouvetmp == 1){ /* On actualise la variable trouve uniquement pour la passer à 1.
                  En effet si le premier chemin fonctionne, trouve va passer à 1, mais si un chemin suivit plus tard
                  dans l'exécution du code ne fonctionne pas,trouve ne doit pas passer à 0
                  au risque de retourner 0 si le dernier chemin ne fonctionne pas*/
                      trouve = trouvetmp;
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
        sommet = fifo_dequeue(&file); // on féfile, sans remettre l'indicateur à 0, c'est un indicateur de passage, pas de présence
        listedge_t p = (graphe.data)[sommet].edges;
        while (p != NULL){
            double DistTemp;
            DistTemp = (graphe.data)[sommet].pcc + (p->val).cout;
            int sommetArrive = (p->val).arrivee;// On créer une variable contenant l'indice du sommet d'arrivé de l'arc pour plus de lisibilié dans le code
            if ((DistTemp < (graphe.data)[sommetArrive].pcc) && ((DistTemp < (graphe.data)[arrivee].pcc))){
                (graphe.data)[sommetArrive].pcc = DistTemp;
                (graphe.data)[sommetArrive].father = sommet;
                if ((graphe.data)[sommetArrive].in_fifo == 0){ // on regarde si le sommet d'arrivée de l'arc est déja passer dans le file ou non
                    file=fifo_enqueue(sommetArrive, file); // s'il n'est pas passé, on l'ajoute
                    (graphe.data)[sommetArrive].in_fifo =1; //et on passe l'indicateur de passage à 1
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
    heap_t heap = heap_new(graphe.size_vertex); // on crée un nouveau tas
    graphe = InitGraphe(depart, graphe); // on initialise le graphe
    heap_add(depart, &heap, graphe); // On ajoute le sommet de départ au tas pour pouvoir commencer l'algorithme
    (graphe.data)[depart].in_heap=1; // On passe à 1 le marqueur de présence dans le tas du sommet de départ
    while(!heap_is_empty(heap) && graphe.data[arrivee].in_heap==0){
        int sommet;
        sommet = heap_get_top(&heap,graphe); // on reculère le sommet du tas
        (graphe.data)[sommet].in_heap=0; // on remet son indice de présence à 0
        listedge_t p = (graphe.data)[sommet].edges;
        if (p != NULL){
          while (p != NULL){ // on parcoure la liste des arcs associés au sommet en question
              double DistTemp;
              DistTemp = (graphe.data)[sommet].pcc + (p->val).cout;
              int sommetArrive = (p->val).arrivee; // On créer une variable contenant l'indice du sommet d'arrivé de l'arc pour plus de lisibilié dans le code
              //printf("sommetD :%d\n",sommet);
              //printf("sommetA :%d\n",sommetArrive);
              //heap_print(heap, graphe);
              //char c;
              //scanf("%c",&c);
              if ((DistTemp < (graphe.data)[sommetArrive].pcc) && ((DistTemp < (graphe.data)[arrivee].pcc))){ // on vérifi que le nouveau pcc est inférieur à l'ancier et au pcc de l'arrivée,
              // s'il est supérieure au pcc d'arrivée, le chemin est déjà trop long, il ne sera pas le plus efficace, il n'est donc pas utile de continuer
                  (graphe.data)[sommetArrive].pcc = DistTemp;
                  (graphe.data)[sommetArrive].father = sommet; // on repère la provenance de l'arc pour pouvoir retracer le chemin par la suite
                  if ( (graphe.data)[sommetArrive].in_heap==0){ // cas ou le sommet n'est pas dans le tas
                    heap_add((graphe.data)[sommetArrive].numero, &heap, graphe); // On l'ajoute
                    (graphe.data)[sommetArrive].in_heap = 1; // on passe l'indicateur de présence à 1
                  }
                  else{ //sinon, le sommet est dans le tas
                      heap = heap_sort(heap, graphe); // on actualise le tas
                    }
              }
              p=p->next;


        }
    }
  }
  if ((graphe.data)[arrivee].pcc==INFINITY){// le sommet d'arrivee n'a pas été trouvé
     return 0;
  }
  return 1;

}


graph_t  InitGraphe(int depart, graph_t graphe){
  int i, size;
  size = graphe.size_vertex;
  for (i = 0; i < size; i++){ // On initialise les valeur de pcc à l'infini pour chaque noeud à l'exception du départ initialisé à 0
    (graphe.data)[i].pcc=INFINITY;
    (graphe.data)[i].father=-1; // la variable father nous permet de reconstruire le chemin en associant la provenance du pcc actuel
    (graphe.data)[i].in_fifo=0; // cette variable nous indique le passage ou non du sommet dans la file
    (graphe.data)[i].in_heap=0;// cette variable nous indique la présence ou non du sommet dans le tas
  }
  (graphe.data)[depart].pcc=0;
  return graphe;
}
