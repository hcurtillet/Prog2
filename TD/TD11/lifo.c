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
  // TODO
  return element_empty();
}

CARTE lifo_pop(lifo_t* ap)	/* attention: la pile est modifiee */
{	  // TODO
  return element_empty();
}

int lifo_length(lifo_t p) {
  // TODO
  return 0;
}

void lifo_print(lifo_t p) {
  // TODO
}

lifo_t lifo_delete(lifo_t p) {
  // TODO
  return NULL;
}
