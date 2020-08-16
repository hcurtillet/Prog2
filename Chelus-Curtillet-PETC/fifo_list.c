#include "graph.h"

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
