#include "graph.h"


graph_t* newGraph(int nbSommet, int nbArc){
    graph_t* g; // On va allouer dinamiquement de la mémoire pour créer un nouveau graphe
    g = calloc(1, sizeof(*g));
    g->data = calloc(nbSommet, sizeof(vertex_t)); // On alloue dinamiquement le nombre de sommer necessaire
    g->size_vertex = nbSommet;
    g->size_egdes = nbArc;
    return g;
}


void edgePrint( edge_t *element){
    printf("Départ: %d, arrivée: %d, cout: %lf \n",element->depart, element->arrivee, element->cout);
}

void list_print(listedge_t l) {
  listedge_t p;
  edge_t val;
  printf("{\n");
  for ( p=l;  p!= NULL; p = p->next) {
    val=p->val;
    printf(" ( Début: %d, arrivée: %d, cout: %lf )\n", val.depart, val.arrivee, val.cout);
  }
  printf("}\n");
}

listedge_t addElement(edge_t *element, listedge_t list){
    printf("Liste debut de fonction:");list_print(list);
    listedge_t add = calloc (1, sizeof (*add));
    if ( add == NULL){printf("Problème dans l'allocation du maillons\n"); exit(EXIT_FAILURE);}
    add->val = *element;
    add->next = NULL;
    listedge_t p;
    p = list;
    if ( p == NULL){printf("C'est nul\n");return add;}
    while(p->next!=NULL){
        p=p->next;
    }
    p->next=add;
    return list;
}


graph_t * creationGraph(char* fName){
    FILE* f;
    int numero,nbSommet,nbArc, depart, arrivee;
    double lat,longi, cout ;
    char line[128] ;
    char name[128] ;
    char mot[512] ;
    f=fopen(fName,"r");
    if (f==NULL) { printf("Impossible d’ouvrir le fichier\n"); exit(EXIT_FAILURE);}
    /* Lecture de la premiere ligne du fichier : nombre de sommet et nombre d’arcs */
    fscanf(f,"%d %d ",&nbSommet,&nbArc);
    graph_t* graphe;
    graphe = newGraph(nbSommet, nbArc);
    if (graphe==NULL) { printf("Impossible d’allouer dynamiquement de graphe\n"); exit(EXIT_FAILURE);}
    /* Ligne de texte "Sommets du graphe" qui ne sert a rien */
    fgets(mot,511,f);
    printf("Le mot est %s",mot);
    /* lecture d’une ligne de description d’un sommet */
    /* on lit d’abord numero du sommet, la position, le nom de la ligne */
    int i;
    vertex_t * p;
    for (i = 0; i < nbSommet; i++){// on va lire chaque ligne de sommet et les attribuer à notre graphe
        fscanf(f,"%d %lf %lf %s %s", &numero, &lat, &longi, line, name);
        (graphe->data)[numero].numero = numero;
        (graphe->data)[numero].nom = strdup(name);
        (graphe->data)[numero].ligne = strdup(line);
        (graphe->data)[numero].x=lat;
        (graphe->data)[numero].y=longi;
    }
    fgets(mot,511,f); // on saute la ligne inutile
    fgets(mot,511,f); // on saute la ligne inutile
    printf("Le mot est %s",mot);
    edge_t * newVal=calloc(1, sizeof(*newVal));
    for ( i = 0; i < nbArc; i++){
        fscanf(f, "%d %d %lf", &depart , &arrivee, &cout); // on lit les elements de l'arcs
        newVal->depart = depart;
        newVal->arrivee = arrivee;
        newVal->cout = cout;
        printf("On est la %d\n",i);
        printf("Element a ajouter: (Départ: %d, arrivée: %d, cout: %lf )\n",depart, arrivee,cout);
        printf("Liste avant:");list_print((graphe->data)[depart].edges);
        /*
        listedge_t p;
        p = (graphe->data)[depart].edges;
        if ( p == NULL){
          printf("C'est nul\n");
          (graphe->data)[depart].edges=calloc (1, sizeof (*(graphe->data)[depart].edges));
          (graphe->data)[depart].edges->val=*newVal;
          (graphe->data)[depart].edges->next=NULL;
        }
        else{
          listedge_t add = calloc (1, sizeof (*add));
          if ( add == NULL){printf("Problème dans l'allocation du maillons\n"); exit(EXIT_FAILURE);}
          add->val = *newVal;
          add->next = NULL;
          while(p->next!=NULL){
              p=p->next;
          }
          p->next=add;
        }*/
        (graphe->data)[depart].edges=addElement(newVal, (graphe->data)[depart].edges);

        printf("Liste apres:");list_print((graphe->data)[depart].edges);

    }
    fclose(f);
    return graphe;
}

void graphPrint(graph_t * graphe){ int i;
    int nbSommet = graphe->size_vertex;
    int nbArc = graphe->size_egdes;
    vertex_t* pdata = graphe->data;
    printf("Le graphe comporte %d sommet(s) et %d arc(s)\n", nbSommet, nbArc);
    for (i = 0; i < nbSommet; i++){
        printf("On considère le sommet numéro %d nommé %s de la ligne %s\n",pdata[i].numero,pdata[i].nom,pdata[i].ligne);
        printf("Voici les arcs partant de ce sommet:\n");
        list_print(pdata[i].edges);
    }

}

int main(){
  graph_t * g=NULL;
  g = creationGraph("graphe1.txt");
  graphPrint(g);
  return 0;
}
