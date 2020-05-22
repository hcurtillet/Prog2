#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(){
  graph_t * g=NULL;
  g = creationGraph("grapheUSAOuest.csv");
  //graphPrint(g);
  //int trouve;
  char * nomDepart;
  char * nomArrive;
  nomDepart = "Sommets59";
  nomArrive = "Sommets5919627";
  parcours(nomDepart, nomArrive,2, g);
  /*
  heap_t tas = heap_new(g->size_vertex);
  int sommet = 1;
  heap_add(sommet, &tas, *g);
  heap_print(tas, *g);
  sommet = 4;
  heap_add(sommet, &tas, *g);
  heap_print(tas, *g);
  sommet = 6;
  heap_add(sommet, &tas, *g);
  heap_print(tas, *g);
  sommet = 2;
  heap_add(sommet, &tas, *g);
  heap_print(tas, *g);
  printf("On récupère le top\n");
  sommet = heap_get_top(&tas,*g);
  heap_print(tas, *g);
  */



  return 0;


}
