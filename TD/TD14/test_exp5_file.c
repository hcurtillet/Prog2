#include "expression.h"
#include "expressionsave.h"
#include "analyse.h"
#include "fonctions.h"
#define DIM 256



int main(int argc, char** argv) { char s[512];
  double xmin=-5, xmax=5;
  binarytree_t r=NULL, d=NULL;
  int nb=300;
  char* file_res="donnees.csv";

  /*
	Lecture d'une expression prefixe au clavier
  */
  printf("Ce programme teste l'analyse par grammaire et la derivation simplifiee par construction\n");
  puts("Entrer une expression en notation infixée avec des espaces entre chaque symbole");
  puts("Exemple : ( 3 * x ) + ( 7 * x )");
  fgets(s,511,stdin); s[strlen(s)-1]=0;
  r=Analyse(s);

  /*
	Affichage de cette expression en notation classique
  */
  puts("Expression :"); expression_print_infixe(r); puts("");

  /*
	Derivation et Affichage de cette derivee en notation classique
        Simplification et Affichage de cette derivee en notation classique
  */
  puts(""); puts("Derivee");
  expression_print_infixe(d=expression_deriv_simplify(r));
  puts("");


  puts("Entrer les bornes du trace (xmin et xmax): attention au domaine de definition");
  scanf("%lf %lf",&xmin,&xmax);
      /*	Sauvegarde des 2 courbes  */
  expression_save_two(file_res,r,d,nb,xmin,xmax);

  d=binarytree_del(d);
  r=binarytree_del(r);
  return 0;
}
