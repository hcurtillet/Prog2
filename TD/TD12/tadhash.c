#include "tadhash.h"
#include <ctype.h>
#include <string.h>


unsigned int hash(char* s, int n) {
  unsigned int h = 0;
  int i,a;
  a=31;
  for ( i =strlen(s) -1; i>=0; i--){
    h = h+s[i];
  }
  return strlen(s);

}


hashtable_t hashtable_new(int m) {
    int i;
    hashtable_t hash;
    hash.size=m;
    list_t *p;
    p=calloc(m,sizeof(list_t));
    for ( i = 0; i < m; i++){
        p[i]=list_new();
    }
    hash.data=p;
    return hash;
}

int hashtable_put(keys_t k, value_t v, hashtable_t t) {
  unsigned int h;
  element_t add;
  add.key = k;
  add.value = v;
  h=hash(k,t.size);
  if (list_find_key(k,t.data[h]) == NULL) {
    t.data[h]=list_add_first(add,t.data[h]);
  }
  else{
    t.data[h]=list_delete_key( k, t.data[h]);
    t.data[h]=list_add_first(add, t.data[h]);
  }
  return 1;
}

int hashtable_contains_key(keys_t k,hashtable_t t) {
  unsigned int h = hash(k,t.size);
  if (list_find_key(k,t.data[h]) == NULL) {
    return 0;
  }
  else{
    return 1;
  }
}

int hashtable_get_value(keys_t k, value_t* pv, hashtable_t t) {
  unsigned int h = hash(k,t.size);
  list_t p;
  p = list_find_key(k,t.data[h]);
  if (p == NULL) {
    return 0;
  }
  else{
    *pv = p->val.value;
    return 1;
  }
}

void hashtable_print(hashtable_t t) {
  int i;
  for ( i = 0; i < t.size; i++){
      list_print(t.data[i]);
  }

}
////////////////////////////////////////////////////////////////


// A faire dans un second temps :

int hashtable_delete_key(keys_t k, hashtable_t t) {
  unsigned int h = hash(k,t.size);
  list_t p;
  p = list_find_key(k,t.data[h]);
  if (p == NULL) {
    return 0;
  }
  else{
    p=list_delete_key(k, p);
    return 1;
  }
}

hashtable_t hashtable_delete(hashtable_t t) {
  //TODO completer

}

void hashtable_analyse(hashtable_t t) {
  //TODO completer
}

void hashtable_sort_print(hashtable_t tab) {
  int i;
  list_t l;
  l=list_new();

  for (i=0; i<tab.size; i++) {
    if (!list_is_empty(tab.data[i])) {
      l = list_concat(list_inverse_copy(tab.data[i]),l);
    }
  }
  // tri fusion de la liste temporaire
  l= list_sort_value(l);

  list_print(l);

  // Suppression de la liste temporaire
  list_delete(l);
}
