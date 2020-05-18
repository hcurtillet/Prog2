#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(){
  graph_t * g=NULL;
  int depart, arrivee;
  depart = 0;
  arrivee = 6;
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
  return 0;

}
