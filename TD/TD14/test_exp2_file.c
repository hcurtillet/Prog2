#include "expression.h"
#include "expressionsave.h"
#include "fonctions.h"

int main(int argc, char** argv) { char s[512];
  double xmin=-5, xmax=5;
  binarytree_t r=NULL;
  binarytree_t c=NULL;
  int nb=300;
  char* file_res="donnees.csv";

  printf("Ce programme teste les fonctions de copie et de liberation memoire\n");
  puts("Entrer une expression en notation prefixee avec des espaces entre chaque symbole");
  puts("Exemple : + * 3 x * 7 x");
  fgets(s,511,stdin); s[strlen(s)-1]=0;
  r=expression_sscanf(s);
  puts("Expression :"); expression_print_infixe(r); puts("");
  /*
      Recopie de r dans c, et liberation de la memoire pour r
      r n'est plus utilisable car n'existe plus
      On trace la copie de r
  */
  printf("On clone l'expression\n");
  c = binarytree_clone(r);
  /*
    Supprime l'arbre initial
  */
  printf("Liberation de l'arbre initial\n");
  r = binarytree_del(r);
  puts("L'expression r initiale (doit etre vide)");
  expression_print_infixe(r); puts("");
  puts("L'expression c copiee (doit etre la meme que r au debut)");
  expression_print_infixe(c); puts("");

  puts("Entrer les bornes du trace (xmin et xmax): attention au domaine de definition");
  scanf("%lf %lf",&xmin,&xmax);
  expression_save_one(file_res,c,nb,xmin,xmax);

  /*
  Liberation de la memoire de la copie
  */
  printf("Liberation de la copie\n");
  c = binarytree_del(c);

  return 0;
}
