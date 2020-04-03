#include "expression.h"
#include "expressionplot.h"
#include "fonctions.h"


int main(int argc, char** argv) {
  char s[512];
  double x;
  binarytree_t r=NULL;

  printf("Ce programme teste l'affichage, l'evaluation et le trace d'un arbre d'expression\n");
  puts("Entrer une expression en notation prefixee avec des espaces entre chaque symbole");
  puts("Exemple : + * 3 x * 7 x");
  fgets(s,511,stdin); s[strlen(s)-1]=0;
  r=expression_sscanf(s);

  puts("Expression :"); expression_print_infixe(r); puts("");

  puts("Entrer une valeur de x pour l'évaluation:");
  scanf("%lf",&x);
  printf("Le résultat est: %lf",expression_eval(r,x));

  r=binarytree_del(r);
  return 0;
}
