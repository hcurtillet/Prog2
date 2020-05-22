#include "graph.h"

heap_t heap_new(int m) {
  heap_t tas;
  tas.data=calloc(m, sizeof(int));
  tas.max_size=m;
  tas.number=0;
  return tas;
}

int heap_is_empty(heap_t tas) {
  return tas.number==0?1:0;
}

/* Ajoute l'element valeur au tas pointe par ptas */
int heap_add(int valeur, heap_t* ptas, graph_t graphe) {
  int i,tmp;
  int *p;
  p=ptas->data;
  i=ptas->number;
  p[i]=valeur;
  //printf("On affiche le tas avant:\n");
  //heap_print(*ptas, graphe);
  while (i!=0 && graphe.data[p[i]].pcc < graphe.data[p[(i-1)/2]].pcc){
    tmp = p[i];
    p[i]=p[(i-1)/2];
    p[(i-1)/2] =tmp;
    i=(i-1)/2;
    //printf("On affiche le tas:\n");
    //heap_print(*ptas, graphe);
  }
  ptas->number+=1;
  return 1;
}


/* Retourne l'indice du plus petit des deux fils ou -1 si c'est une feuille */
static int heap_smallest_son(heap_t tas, int indice,graph_t graphe) {
  int ig,id;
  ig=2*indice+1;
  id=2*(indice+1);
  if (id > tas.number){
      if( ig > tas.number){
        return -1;
      }
      else{
        return ig;
      }
  }
  if ((graphe.data)[tas.data[ig]].pcc<(graphe.data)[tas.data[id]].pcc){
    return ig;
  }
  else{
    return id;
  }
}

/* Supprimer la racine en la remplacant par le dernier element du tas */
int heap_get_top(heap_t* ptas, graph_t graphe) {
  int * p;
  int res;
  int tmp;
  p=ptas->data;
  int i;
  ptas->number-=1;
  i=ptas->number;
  res = p[0];
  p[0]=p[i];
  i=0;
  int ip=heap_smallest_son( *ptas, i, graphe);
  while (ip!=-1){
    tmp=p[i];
    if ((graphe.data)[p[i]].pcc>(graphe.data)[p[ip]].pcc){
      p[i]=p[ip];
      p[ip]=tmp;
      i=ip;
      ip=heap_smallest_son( *ptas, i, graphe);
    }
    else{
      break;
    }
  }
  return res;
}


void heap_delete(heap_t* ptas) {
    free(ptas->data);
}

/* Affiche le tas a l'ecran */
void heap_print(heap_t tas, graph_t graphe) {
  vertex_t* pdata = graphe.data;
  for (int i=0; i<tas.number; i++){
      int k=tas.data[i];
      printf("On considère le sommet numéro %d nommé %s de la ligne %s\n",pdata[k].numero,pdata[k].nom,pdata[k].ligne);
      printf("Ses paramètres sont %lf en pcc et %d en father\n",pdata[k].pcc, pdata[k].father);

      printf("----------------------------------------------------------------------------\n");
  }
  puts("");

}


heap_t heap_sort(heap_t tab, graph_t graphe) {
  heap_t tas;
  int size = tab.max_size;
  int i;
  tas = heap_new(size);
  for ( i = 0; i < tab.number; i++){
    heap_add( tab.data[i], &tas, graphe);
  }
  heap_delete(&tab);
  return tas;
}
