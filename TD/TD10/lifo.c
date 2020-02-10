#include "lifo.h"
#include <stdio.h>
#include <stdlib.h>

lifo_t lifo_new(void) {
  return NULL;
}

int lifo_is_empty(lifo_t p) {
  return list_is_empty(p);
}

lifo_t lifo_push (CARTE e,lifo_t p){
  return list_add_first(e,p);
}

lifo_t lifo_del_first(lifo_t p) {
  // TODO
  return NULL;
}

/* la pile n'est pas modifiée */
CARTE lifo_peek(lifo_t p){
  assert(!lifo_is_empty(p));
  return p->val;
}

CARTE lifo_pop(lifo_t* ap)	/* attention: la pile est modifiee */{
    element_t first;
    first = (*ap)->val;
    *ap = list_del_first(*ap);
    return first;

}

int lifo_length(lifo_t p) {
  int len = 0;
  list_t l;
  for( l=p; ! lifo_is_empty(l) ; l=l->next ) {
    len ++;
  }
  return len;
}

void lifo_print(lifo_t p) {
  list_print(p);
}

lifo_t lifo_delete(lifo_t p) {
  while(!lifo_is_empty(p)){
      p=lifo_del_first(p);
  }
  return p;
}
