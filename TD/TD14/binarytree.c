#include "binarytree.h"
#include "element.h"


binarytree_t node_del(binarytree_t a) {
  a->value=element_delete(a->value);
  free(a);
  return NULL;
}

binarytree_t  binarytree_new()  {
  return NULL;
}

int  binarytree_is_empty(binarytree_t r)  {
  return r==NULL;
}


////////////////////////////////////////////////
/*
  Fonction qui libere la memoire alloue pour un arbre
*/
binarytree_t binarytree_del(binarytree_t r) {
  if (r->left != NULL) binarytree_del(r->left);
  if (r->right != NULL) binarytree_del(r->right);
  free(r);
  return NULL;
}

binarytree_t binarytree_clone(binarytree_t b) {
  binarytree_t r=NULL;r=calloc(1, sizeof(*r));
  if (r==NULL) { puts("Problème d'allocation"); exit(EXIT_FAILURE); }
  r->value.string=strdup(b->value.string);r->value.type=b->value.type;
  if (b->left != NULL){r->left= binarytree_clone(b->left);}
  if (b->right != NULL){r->right = binarytree_clone(b->right);}
  return r;
}

int binarytree_equal(binarytree_t r1, binarytree_t r2) {
  //TODO
  return 0;
}
