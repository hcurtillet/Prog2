#include "graph.h"

void parcours(char * nomDepart, char * nomArrivee, char algo, graph_t * graphe){
    int i=0;
    int sommetDepart=-1, sommetArrivee=-1;
    while(sommetDepart == -1 || sommetArrivee == -1){ //On cherche un sommet correspondant au nom des stations de départ et d'arrivée
        if(strcmp((graphe->data)[i].nom,nomDepart)==0){
            sommetDepart = (graphe->data)[i].numero;
        }
        if(strcmp((graphe->data)[i].nom,nomArrivee)==0){
            sommetArrivee = (graphe->data)[i].numero;
        }
        i++;
        if (i > graphe->size_vertex-1) break;
    }
    int trouve;
    printf("Sommet de départ:%d\nSommet d'arrivée: %d \n",sommetDepart, sommetArrivee);
    if (algo == 1){
        printf("Parcours en profondeur\n");
        *graphe = InitGraphe(sommetDepart, *graphe);
        trouve = ParcoursEnProfondeur(0,5, *graphe);
        printf("Trouve = %d\n",trouve);
    }
    else if (algo ==  2){
        trouve = ParcoursEnLargeur(sommetDepart,sommetArrivee, *graphe);
    }
    else{
        trouve = Dijkstra_like(sommetDepart,sommetArrivee, *graphe);
    }
    if (trouve == 1){
      chemin_t chemin;
      chemin = LectureDeChemin(sommetDepart, sommetArrivee, *graphe);
      chemin_t chemin2;
      chemin2 = chemin->next;
      char * nomstation1 = (graphe->data)[chemin->val].nom;
      char * nomstation2 = (graphe->data)[chemin2->val].nom;
      printChemin(chemin, *graphe);
      while( strcmp(nomstation1,nomstation2)==0){ // on verifie que la station 1 est différente de la station 2, dans le cas contraire, on diminue tout les pcc de la valeur du premier arc et on avance le pointeur chemin
          chemin = chemin2;
          double coutSurplus;
          coutSurplus = (graphe->data)[chemin->val].pcc;
          while(chemin2!= NULL){// on diminue le coup de tout les pcc suivants
              (graphe->data)[chemin2->val].pcc-=coutSurplus;
              chemin2 = chemin2->next;
          }
          chemin2 = chemin->next;
          nomstation1 = (graphe->data)[chemin->val].nom;
          nomstation2 = (graphe->data)[chemin2->val].nom;
      }
      char * nomstation3;
      while(1){
          chemin2 = chemin->next;
          if (chemin2-> next == NULL) break; // on sort de la boucle, on est a la fin
          chemin_t chemin3 = chemin2->next;
          while(chemin3->next != NULL){ // On va au deux derniers sommets
              nomstation2 = (graphe->data)[chemin2->val].nom;
              nomstation3 = (graphe->data)[chemin3->val].nom;
              chemin2 = chemin3;
              chemin3 = chemin3->next;
          }
          nomstation2 = (graphe->data)[chemin2->val].nom;
          nomstation3 = (graphe->data)[chemin3->val].nom;
          if (strcmp(nomstation2,nomstation3)==0){
              chemin2->next = NULL;
          }
          else break;
      }
      printChemin(chemin, *graphe);
    }
}
