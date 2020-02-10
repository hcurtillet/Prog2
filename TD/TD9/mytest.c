#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "element.h"

int main(){
    list_t l; element_t c;
    l=list_new();
    c.rang=1;
    c.visible=1;
    c.couleur=2;
    l=list_add_first(c, l);
    list_print(l);
    c.rang=3;
    c.visible=1;
    c.couleur=3;
    l=list_add_first(c,l);
    list_print(l);
    c.rang=12;
    c.visible=1;
    c.couleur=3;
    l=list_add_last(c,l);
    list_print(l);
    c.rang=3;
    c.visible=1;
    c.couleur=3;
    l=list_add_last(c,l);
    list_print(l);
    printf("présence:%d",list_count(c,l));
    list_print(l);
    list_t l2,l3;
    l2=list_new();
    l2=list_add_last(c,l2);
    l3=list_new();
    printf("Affichage de l3\n");
    printf("Fuision de l:");list_print(l);
    printf("Avec l2:"); list_print(l2);
    l3=list_concat(l,l2);
    list_print(l3);
    printf("Les copies:\n");
    list_t cl;
    cl=list_copy(l3);
    list_print(cl);
    printf("Suppression:\n");
    list_remove_n(2,l3);
    list_print(l3);

}
