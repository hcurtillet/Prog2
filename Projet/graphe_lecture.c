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

graph_t * creationGraph(char* fName){
    FILE* f;
    int numero,nbSommet,nbArc, depart, arrivee;
    double lat,longi, cout ;
    char line[128] ;
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
    for (i = 0; i < nbSommet; i++){// on va lire chaque ligne de sommet et les attribuer à notre graphe
        fscanf(f,"%d %lf %lf %s ", &numero, &lat, &longi, line);
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

void graphPrint(graph_t * graphe){
    int i;
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
