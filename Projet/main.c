#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(){
  graph_t * g=NULL;
  int depart, arrivee;
  depart = 0;
  arrivee = 5;
  g = creationGraph("graphe1.txt");
  graphPrint(g);
  int trouve;
  *g = InitGraphe(depart, *g);
  printf("Init ok\n");
  graphPrint(g);
  trouve = ParcoursEnProfondeur(depart,arrivee, *g);
  printf(" fin du code trouve = %d\n",trouve);
  if (trouve == 1){
    chemin_t chemin;
    chemin = LectureDeChemin(depart, arrivee, *g);
    printChemin(chemin, *g);
  }
  trouve = ParcoursEnLargeur(depart,arrivee, *g);
  printf(" fin du code trouve = %d\n",trouve);
  if (trouve == 1){
    chemin_t chemin;
    chemin = LectureDeChemin(depart, arrivee, *g);
    printChemin(chemin, *g);
  }
  heap_t tas = heap_new(g->size_vertex);
  int sommet;
  sommet = g->data[2].numero;
  printf("Test du tas ---------------------------------------------------\n");
  printf("Ajout du sommet %d\n",sommet);
  heap_add(sommet,&tas,*g);
  heap_print(tas, *g);
  sommet = g->data[4].numero;
  printf("Test du tas ---------------------------------------------------\n");
  printf("Ajout du sommet %d\n",sommet);
  heap_add(sommet,&tas,*g);
  heap_print(tas, *g);
  sommet = g->data[6].numero;
  printf("Test du tas ---------------------------------------------------\n");
  printf("Ajout du sommet %d\n",sommet);
  heap_add(sommet,&tas,*g);
  heap_print(tas, *g);
  sommet = g->data[1].numero;
  printf("Test du tas ---------------------------------------------------\n");
  printf("Ajout du sommet %d\n",sommet);
  heap_add(sommet,&tas,*g);
  heap_print(tas, *g);

  return 0;


}
