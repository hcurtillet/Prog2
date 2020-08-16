#include "graph.h"


// test de Algo.c
int main(){
  // On initialise le graphe de travail
  graph_t * grapheTest;
  grapheTest = creationGraph("graphe1.txt");

  // On affiche le graphe de travail (Sommet par sommet)
  graphPrint(grapheTest);

  // Test du parcours en profondeur :
  printf("Test du parcours en profondeur :\n");
  int i,j;
  // On cherche à trouver le plus court chemin entre chaque sommet du graphe
  for(i = 0 ; i < grapheTest->size_vertex ; i++){
    for(j = 0; j < grapheTest->size_vertex ; j++){

      if(i != j){

      *grapheTest = InitGraphe(i,*grapheTest);

      if(ParcoursEnProfondeur(i,j,*grapheTest) == 1){
        printf("Chemin trouvé entre les sommets %d et %d\n",i,j);
        chemin_t parcours = LectureDeChemin(i,j,*grapheTest);
        printChemin( parcours, *grapheTest);
        }
      else{
        printf("Pas de chemin trouvé entre les sommets %d et %d\n",i,j);
        printf("----------------------------------------------------------------------------\n");
        }

      }

    }
  }
  printf("Fin du test du parcours en largeur\n");
  printf("----------------------------------------------------------------------------\n");

  //Test du parcours en largeur :
  printf("Test du parcours en largeur :\n");
  for(i = 0 ; i < grapheTest->size_vertex ; i++){
    for(j = 0; j < grapheTest->size_vertex ; j++){

      if(i != j){

      if(ParcoursEnLargeur(i,j,*grapheTest) == 1){
        printf("Chemin trouvé entre les sommets %d et %d\n",i,j);
        chemin_t parcours = LectureDeChemin(i,j,*grapheTest);
        printChemin( parcours, *grapheTest);
        }
      else{
        printf("Pas de chemin trouvé entre les sommets %d et %d\n",i,j);
        printf("----------------------------------------------------------------------------\n");
        }

      }

    }
  }
  printf("Fin du test du parcours en largeur\n");
  printf("----------------------------------------------------------------------------\n");

  return 0;
}
