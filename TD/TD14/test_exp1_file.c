#include "expression.h"
#include "expressionsave.h"
#include "fonctions.h"

int main(int argc, char** argv) { char s[512];
  double xmin=-5, xmax=5;
  binarytree_t r=NULL;
  char* file_res="donnees.csv";
  int nb=300;
  	/*
	   Lecture d'une expression prefixe au clavier
 	 */
  printf("Ce programme teste l'affichage, l'evaluation et le trace d'un arbre d'expression\n");
  puts("Entrer une expression en notation prefixee avec des espaces entre chaque symbole");
  puts("Exemple : + * 3 x * 7 x");
  fgets(s,511,stdin); s[strlen(s)-1]=0;
  r=expression_sscanf(s);
 	 /*
	Affichage de cette expression en notation classique
 	 */
  puts("Expression :"); expression_print_infixe(r); puts("");

  /*
  	Affichage dnas un fichier
  */
  puts("Entrer les bornes du trace (xmin et xmax): attention au domaine de definition");
  scanf("%lf %lf",&xmin,&xmax);
  expression_save_one(file_res,r,nb,xmin,xmax);

  /*
	Liberation de la memoire de l'arbre
  */
  r=binarytree_del(r);
  return 0;
}
