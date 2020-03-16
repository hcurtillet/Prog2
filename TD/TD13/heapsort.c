#include "heapsort.h"

/*
  Tri par tas :
    Cree un tas a partir du tableau tab ,
    tri ce tas par l'algorithem du tri par tas,
    recopie le tas trie dnas le tableau tab
    detruit le tas
*/
void heap_sort(element_t* tab, int size) {
  heap_t tas;int i,tmp;
  tas = heap_new(size);
  for ( i = 0; i < size; i++){
    heap_add( tab[i], &tas);
  }
  for ( i = 0; i < size; i++){
    tmp = heap_get_max(tas);
    tab[size-1-i]=tmp;
    heap_delete_max(&tas);
  }
  heap_delete(&tas);
}
