#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

graph_t* newGraph(int nbSommet, int nbArc){
    graph_t* g; // On va allouer dinamiquement de la mémoire pour créer un nouveau graphe
    g = calloc(1, sizeof(*g));
    g->data = calloc(nbSommet, sizeof(vertex_t)); // On alloue dinamiquement le nombre de sommer necessaire
    g->size_vertex = nbSommet;
    g->size_egdes = nbArc;
    return g;
}

fifo_t fifo_new(void){
  return NULL;	/* la liste vide est representée par NULL	*/
}

int fifo_is_empty(fifo_t L){
  return L==NULL;	/* la liste vide est representée par NULL	*/
}

fifo_t fifo_enqueue(int n, fifo_t f){
  fifo_t add = calloc( 1, sizeof( *add ) );
  if ( NULL == add ) {
    fprintf( stderr, "Fatal: Unable to allocate new list link.\n" );
    return f;
  }
  add->val=n;
  if (fifo_is_empty(f)){
    add->next=add;
  }
  else{
    add->next = f->next;
    f->next=add;
  }
  return add;
}

int fifo_peek(fifo_t f){
  int e;
  fifo_t p = f->next;
  e = p->val;
  return e;
}

fifo_t fifo_del_head(fifo_t f) {
  assert(!fifo_is_empty(f));
  if (f == f->next){
      free(f);
      return NULL;
  }
  fifo_t p;
  p=f->next;
  f->next = p->next;
  free(p);
  return f;
}

int fifo_dequeue(fifo_t* af) {
  assert(!fifo_is_empty(*af));
  int e = fifo_peek(*af);
  *af=fifo_del_head(*af);
  return e;
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
    listedge_t add = calloc (1, sizeof (*add));
    if ( add == NULL){printf("Problème dans l'allocation du maillons\n"); exit(EXIT_FAILURE);}
    add->val = *element;
    add->next = NULL;
    listedge_t p;
    p = list;
    if ( p == NULL){return add;}
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
    //printf("Le mot est %s",mot);
    /* lecture d’une ligne de description d’un sommet */
    /* on lit d’abord numero du sommet, la position, le nom de la ligne */
    int i;
    vertex_t * p;
    for (i = 0; i < nbSommet; i++){// on va lire chaque ligne de sommet et les attribuer à notre graphe
        fscanf(f,"%d %lf %lf %s", &numero, &lat, &longi, line);
        fgets(mot,511,f);
        if (mot[strlen(mot)-1]<32) mot[strlen(mot)-1]=0;
        (graphe->data)[numero].numero = numero;
        (graphe->data)[numero].nom = strdup(mot);
        (graphe->data)[numero].ligne = strdup(line);
        (graphe->data)[numero].x=lat;
        (graphe->data)[numero].y=longi;
    }
    fgets(mot,511,f); // on saute la ligne inutile
    edge_t * newVal=calloc(1, sizeof(*newVal));
    for ( i = 0; i < nbArc; i++){
        fscanf(f, "%d %d %lf", &depart , &arrivee, &cout); // on lit les elements de l'arcs
        newVal->depart = depart;
        newVal->arrivee = arrivee;
        newVal->cout = cout;
        (graphe->data)[depart].edges=addElement(newVal, (graphe->data)[depart].edges);

    }
    fclose(f);
    return graphe;
}

void graphPrint(graph_t * graphe){ int i;
    int nbSommet = graphe->size_vertex;
    int nbArc = graphe->size_egdes;
    vertex_t* pdata = graphe->data;
    printf("Le graphe comporte %d sommet(s) et %d arc(s)\n", nbSommet, nbArc);
    printf("----------------------------------------------------------------------------\n");
    for (i = 0; i < nbSommet; i++){
        printf("On considère le sommet numéro %d nommé %s de la ligne %s\n",pdata[i].numero,pdata[i].nom,pdata[i].ligne);
        printf("Ses coordonnées sont %lf en latitude et %lf en longitude\n",pdata[i].x, pdata[i].y);
        printf("Ses paramètres sont %lf en pcc et %d en father\n",pdata[i].pcc, pdata[i].father);
        printf("Voici les arcs partant de ce sommet:\n");
        list_print(pdata[i].edges);
        printf("----------------------------------------------------------------------------\n");
    }

}

int ParcoursEnProfondeur(int depart, int arrivee, graph_t graphe){
    if (depart == arrivee){
      return 1; // on a trouver l'arrivée, on retourne 1
    }
    else{
      int trouve = 0; //On initialie trouve au début, trouve est propre au noeud en cours
      listedge_t p = (graphe.data)[depart].edges;
      if (p != NULL){
          while (p != NULL){
              double DistTemp;
              DistTemp = (graphe.data)[depart].pcc + (p->val).cout;
              if ((DistTemp < (graphe.data)[(p->val).arrivee].pcc) && ((DistTemp < (graphe.data)[arrivee].pcc))){
                  (graphe.data)[(p->val).arrivee].pcc = DistTemp;
                  (graphe.data)[(p->val).arrivee].father = depart;
                  int trouve2 = ParcoursEnProfondeur((p->val).arrivee, arrivee,graphe);
                  if (trouve2 == 1){ /* On actualise la variable trouve uniquement pour la passer à 1.
                  En effet si le premier chemin fonctionne, trouve va passer à 1, mais si un chemin suivit plus tard
                  dans l'exécution du code ne fonctionne pas,trouve ne doit pas passer à 0
                  au risque de retourner 0 si le dernier chemin ne fonctionne pas*/
                      trouve = trouve2;
                  }
              }
              p=p->next;
          }
       }
       return trouve;
    }
}

graph_t  InitGraphe(int depart, graph_t graphe){
  int i, size;
  size = graphe.size_vertex;
  for (i = 0; i < size; i++){ // On initialise les valeur de pcc à l'infini pour chaque noeud à l'exception du départ initialisé à 0
    (graphe.data)[i].pcc=INFINITY;
    (graphe.data)[i].father=-1; // la variable father nous permet de reconstruire le chemin en associant la provenance du pcc actuel
    (graphe.data)[i].in_fifo=0;
  }
  (graphe.data)[depart].pcc=0;
  return graphe;
}

chemin_t LectureDeChemin(int depart, int arrivee, graph_t graphe){ // on crée une liste contenant les noeuds utilisée dans l'ordre. On utilise la variable father pour cela
    chemin_t chemin=NULL;
    int elementEnCours = arrivee;
    do{
      chemin_t add = calloc (1, sizeof (*add));
      if ( add == NULL){printf("Problème dans l'allocation du maillons\n"); exit(EXIT_FAILURE);}
      add->val = elementEnCours;
      add->next = chemin;
      chemin=add;
      elementEnCours = graphe.data[elementEnCours].father;
    }while(elementEnCours != depart);
    chemin_t add = calloc (1, sizeof (*add));
    if ( add == NULL){printf("Problème dans l'allocation du maillons\n"); exit(EXIT_FAILURE);}
    add->val = elementEnCours;
    add->next = chemin;
    chemin=add;
    elementEnCours = graphe.data[elementEnCours].father;
    return chemin;
}

void printChemin( chemin_t chemin, graph_t graphe){
    chemin_t p;
    p = chemin;
    vertex_t elementEnCours;
    printf("Voici le chemin le plus efficace\n");
    printf("----------------------------------------------------------------------------\n");
    if (p != NULL){
        while( p != NULL){
          printf(" Valeur de p %d\n",p->val);
          elementEnCours = graphe.data[p->val];
          printf("Passer par %s de la ligne %s\n", elementEnCours.nom, elementEnCours.ligne);
          if (p->next == NULL){
            printf("Le cout est de %lf\n\n", elementEnCours.pcc);
          }
          p=p->next;
        }
    }
    printf("----------------------------------------------------------------------------\n");
}

int ParcoursEnLargeur(int depart, int arrivee, graph_t graphe){
    fifo_t file = fifo_new();
    graphe = InitGraphe(depart, graphe);
    file=fifo_enqueue(depart, file);
    (graphe.data)[depart].in_fifo=1;
    while(!fifo_is_empty(file)){
        int sommet;
        sommet = fifo_dequeue(&file);
        listedge_t p = (graphe.data)[sommet].edges;
        if (p != NULL){
          while (p != NULL){
              double DistTemp;
              DistTemp = (graphe.data)[sommet].pcc + (p->val).cout;
              if ((DistTemp < (graphe.data)[(p->val).arrivee].pcc) && ((DistTemp < (graphe.data)[arrivee].pcc))){
                  (graphe.data)[(p->val).arrivee].pcc = DistTemp;
                  (graphe.data)[(p->val).arrivee].father = sommet;
                  if ((graphe.data)[(p->val).arrivee].in_fifo == 0){
                      file=fifo_enqueue((p->val).arrivee, file);
                      (graphe.data)[(p->val).arrivee].in_fifo =1;
                  }
              }
              p=p->next;
              }

        }

    }
    if ((graphe.data)[arrivee].pcc!=INFINITY){
       return 1;
    }
    else{
        return 0;
    }
}


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
  int pause;
  //scanf("%d",&pause);
  trouve = ParcoursEnProfondeur(depart,arrivee, *g);
  printf(" fin du code trouve = %d\n",trouve);
  //scanf("%d",&pause);
  if (trouve == 1){
    chemin_t chemin;
    chemin = LectureDeChemin(depart, arrivee, *g);
    printChemin(chemin, *g);
  }
  trouve = ParcoursEnLargeur(depart,arrivee, *g);
  printf(" fin du code trouve = %d\n",trouve);
  //scanf("%d",&pause);
  if (trouve == 1){
    chemin_t chemin;
    chemin = LectureDeChemin(depart, arrivee, *g);
    printChemin(chemin, *g);
  }
  return 0;

}
