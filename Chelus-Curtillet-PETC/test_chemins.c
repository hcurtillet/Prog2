#include "graph.h"

int main(){
  // On initialise le graphe de travail
  graph_t * grapheTest;
  grapheTest = creationGraph("graphe2.txt");

  // On affiche le graphe de travail (Sommet par sommet)
  graphPrint(grapheTest);


  // On édite artificiellement le graphe pour créer le chemin 11 -> 8 -> 2 -> 0 -> 1
  printf("Création artificielle d'un chemin dans le graphe");
  (grapheTest->data)[1].father = 0;
  (grapheTest->data)[0].father = 2;
  (grapheTest->data)[2].father = 8;
  (grapheTest->data)[8].father = 11;

  // On réaffiche le graphe pour vérifier que les valeurs de father se soient bien actualisées
  graphPrint(grapheTest);

  // On crée le chemin en question
  chemin_t parcours = LectureDeChemin(11,1,*grapheTest);

  // On affiche le chemin ainsi créé
  printChemin(parcours,*grapheTest);

  return 0;
}
