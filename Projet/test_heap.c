#include "graph.h"

int main(){
  // Test des fonctions sur les tas

  // On initialise le graphe de travail
  graph_t * grapheTest;
  grapheTest = creationGraph("graphe1.txt");

  // On crée les tas à utiliser
  heap_t tasTri = heap_new(grapheTest->size_vertex);
  heap_t tasAdd = heap_new(grapheTest->size_vertex);

  // On change les pcc de tous les sommets du graphe artificiellement

  int i;
  for (i = 0; i<grapheTest->size_vertex ; i++){
    (grapheTest->data)[i].pcc = rand() % 50;
  }

  // On affiche ensuite le graphe pour vérifier l'attribution des pcc

  graphPrint(grapheTest);

  // On ajoute ensuite chacun des sommets au tas tasAdd

  for (i = 0; i<grapheTest->size_vertex ; i++){
    heap_add(i, &tasAdd , *grapheTest);
  }

  // On affiche le tas tasAdd
  printf("--------------------------------------------------------------------\n");
  printf("Affichage du tas tasAdd :\n");
  heap_print(tasAdd, *grapheTest);

  // On vérifie la fonction heap_get_top :

  int top = heap_get_top(&tasAdd, *grapheTest);

  printf("--------------------------------------------------------------------\n");
  printf("Le sommet du tas vaut %d\n",top);
  printf("--------------------------------------------------------------------\n");

  // On change à nouveau les pcc des sommets

  for (i = 0; i<grapheTest->size_vertex ; i++){
    (grapheTest->data)[i].pcc += (rand() % 10) - 5 ;
  }

  // On affiche le graphe

  graphPrint(grapheTest);

  // On trie les sommets avec la fonction heap_sort

  tasTri = heap_sort(tasAdd, *grapheTest);

  // On affiche les tas

  printf("--------------------------------------------------------------------\n");
  printf("Affichage de l'ancien tas tasAdd\n");
  heap_print(tasAdd, *grapheTest);
  printf("--------------------------------------------------------------------\n");
  printf("Affichage du tas tasTri :\n");
  heap_print(tasTri, *grapheTest);

  return 0;
}
