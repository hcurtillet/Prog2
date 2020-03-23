#ifndef _EXPRESSIONSAVE
#define _EXPRESSIONSAVE
#include "expression.h"
#include "fonctions.h"
/*
	Sauvegarde dans un fichier des valeurs de l'expression r, entre x=xmin
  et x=xmax, avec nb points
*/
int expression_save_one(char * f1, binarytree_t r, int nb, double xmin, double xmax)  ;
int expression_save_two(char* f1, binarytree_t r, binarytree_t d, int nb, double xmin, double xmax);
#endif
