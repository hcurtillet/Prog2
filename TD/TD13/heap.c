#include "heap.h"

heap_t heap_new(int m) {
  heap_t tas;
  tas.data=calloc(m, sizeof(element_t));
  tas.max_size=m;
  tas.number=0;
  return tas;
}

int heap_is_empty(heap_t tas) {
  return tas.number==0?1:0;
}

/* Ajoute l'element valeur au tas pointe par ptas */
int heap_add(element_t valeur, heap_t* ptas) {
  int i,tmp;
  element_t *p;
  p=ptas->data;
  i=ptas->number;
  p[i]=valeur;
  /*printf("On affiche le tas avant:\n");
  heap_print(*ptas);*/
  while (i!=0 && p[i]>p[(i-1)/2]){
    tmp = p[i];
    p[i]=p[(i-1)/2];
    p[(i-1)/2] =tmp;
    i=(i-1)/2;
    //printf("On affiche le tas:\n");
    //heap_print(*ptas);
  }
  ptas->number+=1;
  return 1;

}


/* Retourne l'indice du plus grand des deux fils ou -1 si c'est une feuille */
static int heap_largest_son(heap_t tas, int indice) {
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
  if (tas.data[ig]>tas.data[id]){
    return ig;
  }
  else{
    return id;
  }
}

/* Supprimer la racine en la remplacant par le dernier element du tas */
int heap_delete_max(heap_t* ptas) {
  element_t * p;
  int tmp;
  p=ptas->data;
  int i;
  i=ptas->number;
  ptas->number-=1;
  p[0]=p[i];
  p[i]=NULL;
  i=0;
  int ip=heap_largest_son( *ptas, i);
  while (ip!=-1){
    tmp=p[i];
    if (p[i]<p[ip]){
    p[i]=p[ip];
    p[ip]=tmp;
    i=ip;
    ip=heap_largest_son( *ptas, i);
    }
    else{
      break;
    }
  }
  return 1;
}


void heap_delete(heap_t* ptas) {
    free(ptas->data);
}

/* Retourne l'element max */
element_t heap_get_max(heap_t tas) {
  return tas.data[0];
}

/* Affiche le tas a l'ecran */
void heap_print(heap_t tas) {
  for (int i=0; i<tas.number; i++)
    element_print(tas.data[i]);
  puts("");
}

/*
  Verifie la propriete des tas sur tous les noeuds :
  le pere est plus grand que les 2 fils
*/

int heap_verification(heap_t tas) {
  int i;
  for (i=0; i< tas.number/2; i++) {
  if (ELEMENT_COMPARE(tas.data+i,tas.data+HEAP_LEFTSON(i))<0) return i;
    if (HEAP_RIGHTSON(i)<tas.number && tas.data[i]<tas.data[HEAP_RIGHTSON(i)]) return i;
  }
  return -1;
}
