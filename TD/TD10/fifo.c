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
printf("(");
  if(!fifo_is_empty(L)){
  fifo_t p,mem;
  p=L;
  p = p->next;
  mem=p;
  element_print( p->val );
  p = p->next;
  while (p!=mem){
    element_print( p->val );
    p = p->next;
  }

}
printf(")\n");
}

fifo_t fifo_enqueue(CARTE e, fifo_t f){
  fifo_t add = calloc( 1, sizeof( *add ) );
  if ( NULL == add ) {
    fprintf( stderr, "Fatal: Unable to allocate new list link.\n" );
    return f;
  }
  add->val=e;
  if (fifo_is_empty(f)){
    add->next=add;
  }
  else{
    add->next = f->next;
    f->next=add;
  }
  return add;
}

CARTE fifo_peek(fifo_t f){
  CARTE e;
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

CARTE fifo_dequeue(fifo_t* af) {
  assert(!fifo_is_empty(*af));
  CARTE e = fifo_peek(*af);
  *af=fifo_del_head(*af);
  return e;
}

fifo_t fifo_delete(fifo_t f) {
  while(!fifo_is_empty(f)){
      f=fifo_del_head(f);
  }
  return f;
}
