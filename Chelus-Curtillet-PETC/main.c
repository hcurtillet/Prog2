#include "graph.h"

int main(int argc, char * argv[]){
  graph_t * g=NULL;
  char * data;
  data = argv[1];
  printf("%s\n",data);
  g = creationGraph(data);
  char nomDepart[50];
  char nomArrivee[50];
  printf("Entrer le nom du départ:\n");
  fgets(nomDepart,50,stdin);
  nomDepart[strlen(nomDepart)-1]='\0';
  printf("Entrer le nom de l'arrivée:\n");
  fgets(nomArrivee,50,stdin);
  nomArrivee[strlen(nomArrivee)-1]='\0';
  int i;
  printf("Choix de l'algorithme:\n");
  printf("1) Parcours en profondeur\n");
  printf("2) Parcours en largeur\n");
  printf("3) Parcours Dijkstra like\n");
  scanf("%d",&i);
  while (i!=1 && i!=2 && i!=3){
      printf("Veuillez entrer une valeurs de la liste\n");
      printf("Choix de l'algorithme:\n");
      printf("1) Parcours en profondeur\n");
      printf("2) Parcours en largeur\n");
      printf("3) Parcours Dijkstra like\n");
      scanf("%d",&i);
  }
  parcours(nomDepart, nomArrivee,2, g);
  return 0;
}
