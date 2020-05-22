#include "graph.h"
chemin_t LectureDeChemin(int depart, int arrivee, graph_t graphe){ // on crée une liste contenant les noeuds utilisée dans l'ordre. On utilise la variable father pour cela
    chemin_t chemin=NULL;
    int elementEnCours = arrivee;
    do{
      chemin_t add = calloc (1, sizeof (*add));
      if ( add == NULL){printf("Problème dans l'allocation du maillons\n"); exit(EXIT_FAILURE);}
      add->val = elementEnCours;
      add->next = chemin;
      chemin=add;
      elementEnCours = graphe.data[elementEnCours].father; // on récupère le numléro du père pour pouvoir l'ajouter par la suite dans le chemin
    }while(elementEnCours != depart);
    chemin_t add = calloc (1, sizeof (*add));
    if ( add == NULL){printf("Problème dans l'allocation du maillons\n"); exit(EXIT_FAILURE);}
    add->val = elementEnCours; //On ajoute le départ à la liste
    add->next = chemin;
    chemin=add;
    return chemin;
}

void printChemin( chemin_t chemin, graph_t graphe){
    chemin_t p;
    p = chemin;
    vertex_t elementEnCours;
    printf("Voici le chemin le plus efficace\n");
    printf("----------------------------------------------------------------------------\n");
    if (p != NULL){
        elementEnCours = graphe.data[p->val]; //on crée une variable de type vertex_t afin de faciliter la lecture du code
        printf("Départ de %s de la ligne %s \n", elementEnCours.nom, elementEnCours.ligne);
        p=p->next;
        while( p->next != NULL){ //On affiche tout les éléments du chemin
          // printf(" Valeur de p %d\n",p->val);
          elementEnCours = graphe.data[p->val];
          printf("Passer par %s de la ligne %s \n", elementEnCours.nom, elementEnCours.ligne);
          p=p->next;
        }
        elementEnCours = graphe.data[p->val];
        printf("Arrivée à %s par la ligne %s\n", elementEnCours.nom, elementEnCours.ligne);
        printf("Le cout est de %lf\n\n", elementEnCours.pcc);

    }

    printf("----------------------------------------------------------------------------\n");
}
