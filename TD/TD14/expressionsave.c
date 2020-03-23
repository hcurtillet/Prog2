#include "expression.h"
#include "expressionsave.h"
#include "fonctions.h"
/*
	Sauvegarde dans un fichier des valeurs de l'expression r, entre x=xmin
  et x=xmax, avec nb points
*/
int expression_save_one(char * f1, binarytree_t r, int nb, double xmin, double xmax)  {
  int i;
  FILE* fp;
  if ( (fp=fopen(f1,"w"))==NULL) return -1;
  for (i=0; i<nb; i++) {
    fprintf(fp, "%lf;\t%lf\n",xmin+i*(xmax-xmin)/(nb-1), expression_eval(r,xmin+i*(xmax-xmin)/(nb-1))) ;
  }
  fclose(fp);
  return 0;
}

int expression_save_two(char* f1, binarytree_t r, binarytree_t d, int nb, double xmin, double xmax)  {
  int i;
  FILE* fp;
  if ( (fp=fopen(f1,"w"))==NULL) return -1;
  for (i=0; i<nb; i++) {
    fprintf(fp, "%lf;\t%lf;\t%lf\n",xmin+i*(xmax-xmin)/(nb-1), expression_eval(r,xmin+i*(xmax-xmin)/(nb-1)),expression_eval(d,xmin+i*(xmax-xmin)/(nb-1)));
  }
  fclose(fp);
  return 0;
}
