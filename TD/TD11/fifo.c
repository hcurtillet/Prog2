#include "fifo.h"
#include <stdio.h>
#include <stdlib.h>

fifo_t fifo_new(void){
  return NULL;	/* la liste vide est representée par NULL	*/
}

int fifo_is_empty(fifo_t L){
  return L==NULL;	/* la liste vide est representée par NULL	*/
}

void fifo_print(fifo_t L) {
  // TODO
}

fifo_t fifo_enqueue(CARTE e, fifo_t f){
  // TODO
  return NULL;
}

CARTE fifo_peek(fifo_t f){
  // TODO
  return element_empty();
}

fifo_t fifo_del_head(fifo_t f) {
  // TODO
  return NULL;
}

CARTE fifo_dequeue(fifo_t* af) {
  // TODO
  return element_empty();
}

fifo_t fifo_delete(fifo_t f) {
  // TODO
  return NULL;
}
