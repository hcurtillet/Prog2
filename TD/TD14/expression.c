#include "expression.h"
/*
  Fonction de creation d'un noeud a partir d'une chaine de caracteres contenant:
  Role :
     - alloue un espace memoire necessaire a un oeoud
     - alloue et copie la chaine dans le noeud (champ val)
     - met a jour le type du noeud en fonction de la chaine
          - variable
          - constante
          - operateur unaire (sin, cos, tan, sqrt, ...)
          - operateur binaire (+,-,*,/,^^)
*/
expression_t expression_node_new(char *c) {
  expression_t r=NULL;

  if (c==NULL || *c=='\0') { puts("Erreur de syntaxe"); exit(1); }
  TYPE t = element_type(c);

  if (t==PASDEFINI) {
    printf("%s : fonction non implantee\n",c);
    exit(EXIT_FAILURE);
  }
  /* Allocation memoire d'un noeud */
  r=calloc(1,sizeof(*r));
  if (r==NULL) { puts("Plus assez de memoire "); exit(EXIT_FAILURE); }

  r->value=element_new(c,t);
  return r;
}

/*
   Focntion construisant un arbre a partir d'une chaine decoupee en mots

   Algo :
     recupere le premier mot de la chaine par la fonction strtok(NULL," ")
     si ce mot est
       - une constante ou une variable : construit et retourne le noued contenant cette constante ou cette variable
       - un operateur unaire :
               construit le noued contenant cet operateur;
               Le fils droit de ce noeud est vide.
               le fils gauche de ce noeud est le sous arbre obtenu par le reste de l'expression en cours d'analyse
               retourne le noued ainsi obtenu
       - un operateur binaire :
               construit le noued contenant cet operateur;
               le fils gauche de ce noeud est le sous arbre obtenu par le reste de l'expression en cours d'analyse. Cette analyse s'arrete a la fin de l'expression contenant le fils gauche car les expressions sont bien construites
               Le fils droit de ce noeud est le sous arbre obtenu par le reste de l'expression en cours d'analyse
               retourne le noued ainsi obtenu
*/
static expression_t expression_new(char *c) {
  expression_t r=NULL;
  r=expression_node_new(c);
  switch(r->value.type) {
    case OPERATEUR_BINAIRE:
         r->left=expression_new(strtok(NULL," "));
         r->right=expression_new(strtok(NULL," "));
         return r;
    case OPERATEUR_UNAIRE :
         r->right=expression_new(strtok(NULL," ")); return r;
    case VARIABLE: case VALEUR:
         return r;
    default : node_del(r); return NULL;
  }
  return NULL;
}

/*
  Fonction qui construit un arbre a partir d'une expression.
  Elle decoupe la chaine en suite de mot (fonction strtok). Les appels suivants a strtok permettront de recuperer les mots les uns apres les autres.
  Elle appelle ensuite la creation d'un arbre a partir d'une suite de mots
*/
expression_t expression_sscanf(char *s) {
  char *c = strtok(s," ");
  return expression_new(c);
}


////////////////////////////////////////////
void expression_print_infixe(expression_t r) {
  if (r!=NULL){
    if (r->left != NULL){
      if ((strcmp((r->value).string,"*")==0 || strcmp((r->value).string,"/")==0) &&  (strcmp(((r->left)->value).string,"+")==0 || strcmp(((r->left)->value).string,"-")==0)){
        printf("(");
        expression_print_infixe(r->left);
        printf(")");
      }
      else if (strcmp((r->value).string,"^")==0 && ((r->left)->value).type==OPERATEUR_BINAIRE){
        printf("(");
        expression_print_infixe(r->left);
        printf(")");
      }
      else{
        expression_print_infixe(r->left);
      }
    }
    printf("%s", (r->value).string);
    if (r->right != NULL){
      if (((strcmp((r->value).string,"-")==0 || strcmp((r->value).string,"^")==0 )&& ( ((r->right)->value).type==OPERATEUR_BINAIRE))|| ((strcmp((r->value).string,"*")==0 || strcmp((r->value).string,"/")==0) &&  (strcmp(((r->right)->value).string,"+")==0 || strcmp(((r->right)->value).string,"-")==0))){
        printf("(");
        expression_print_infixe(r->right);
        printf(")");
      }
      else if ((r->value).type==OPERATEUR_UNAIRE){
        printf("(");
        expression_print_infixe(r->right);
        printf(")");
      }
      else{
        expression_print_infixe(r->right);
      }
    }
  }


}

double expression_eval(expression_t r, double x) { // J'ai plus de 20 lignes pour aérer mon code, sinon je peux économiser visuellement 22 lignes en mettant l'ensemble des if sur une seule ligne
  switch((r->value).type){
    case VALEUR:
      return atof((r->value).string);
    case VARIABLE:
     return x;
    case OPERATEUR_BINAIRE:
      if (strcmp((r->value).string,"*")==0){
        return (expression_eval(r->left,x)*expression_eval(r->right,x));
      }
      else if (strcmp((r->value).string,"/")==0){
        return (expression_eval(r->left,x)/expression_eval(r->right,x));
      }
      else if (strcmp((r->value).string,"+")==0){
        return (expression_eval(r->left,x)+expression_eval(r->right,x));
      }
      else if (strcmp((r->value).string,"-")==0){
        return (expression_eval(r->left,x)-expression_eval(r->right,x));
      }
      else if (strcmp((r->value).string,"^")==0){
        return pow(expression_eval(r->left,x),expression_eval(r->right,x));
      }
    case OPERATEUR_UNAIRE:
      if (strcmp((r->value).string,"sin")==0){
        return (sin(expression_eval(r->right,x)));
      }
      if (strcmp((r->value).string,"cos")==0){
        return (cos(expression_eval(r->right,x)));
      }
      if (strcmp((r->value).string,"tan")==0){
        return (tan(expression_eval(r->right,x)));
      }
      if (strcmp((r->value).string,"sqrt")==0){
        return (sqrt(expression_eval(r->right,x)));
      }
      if (strcmp((r->value).string,"exp")==0){
        return (exp(expression_eval(r->right,x)));
      }
      if (strcmp((r->value).string,"log")==0){
        return (log(expression_eval(r->right,x)));
      }
  }
}


expression_t expression_derivation(expression_t r) {
  if (r != NULL){
    switch (r->value.type) {
      case VARIABLE:
        return expression_node_new("1");
      case VALEUR:
        return expression_node_new("0");
      case OPERATEUR_BINAIRE:
        if (strcmp((r->value).string,"*")==0){
            return expression_derivation_prod(r->left, r->right);
        }
        else if (strcmp((r->value).string,"/")==0){
          return expression_derivation_div(r->left, r->right);
        }
        else if (strcmp((r->value).string,"+")==0 || strcmp((r->value).string,"-")==0){
          return expression_derivation_som(r);
        }
        else if (strcmp((r->value).string,"^")==0){

        }
      case OPERATEUR_UNAIRE:
        if (strcmp((r->value).string,"sin")==0){

        }
        if (strcmp((r->value).string,"cos")==0){

        }
        if (strcmp((r->value).string,"tan")==0){

        }
        if (strcmp((r->value).string,"sqrt")==0){

        }
        if (strcmp((r->value).string,"exp")==0){

        }
        if (strcmp((r->value).string,"log")==0){

        }
    }
  }
}

expression_t expression_derivation_prod(expression_t r1, expression_t r2){
    expression_t r;
    if (r1->value.type==VALEUR && r2->value.type==VALEUR){
      return NULL;
    }
    else if (r1->value.type==VALEUR){
      r=expression_node_new("*");
      printf("Ce cas\n");
      r->left = binarytree_clone(r1);
      r->right = expression_derivation(r2);
    }
    else if (r2->value.type==VALEUR){
      r=expression_node_new("*");
      r->left = binarytree_clone(r2);
      r->right = expression_derivation(r1);
    }
    else{
      r=expression_node_new("+");
      expression_t rtmp;
      //u'v
      rtmp=expression_node_new("*");
      rtmp->right = binarytree_clone(r2);
      rtmp->left = expression_derivation(r1);
      r->left=binarytree_clone(rtmp);
      // uv'
      rtmp->left = binarytree_clone(r1);
      rtmp->right = expression_derivation(r2);
      r->right=binarytree_clone(rtmp);
      rtmp=binarytree_del(rtmp);
    }
    return r;
}

expression_t expression_derivation_som(expression_t d){
  expression_t r, r1, r2;
  r1=d->left;
  r2=d->right;
  if (r1->value.type==VALEUR && r2->value.type==VALEUR){
    return NULL;
  }
  else if (r1->value.type==VALEUR){
    r=expression_derivation(r2);
  }
  else if (r2->value.type==VALEUR){
    r=expression_derivation(r1);
  }
  else{
    r=expression_node_new(d->value.string);
    r->left=expression_derivation(r1);
    r->right=expression_derivation(r2);
  }
  return r;
}

expression_t expression_derivation_div(expression_t r1, expression_t r2){
  expression_t r;
  if (r1->value.type==VALEUR && r2->value.type==VALEUR){
    return NULL;
  }
  else if (r2->value.type==VALEUR){
    r=expression_node_new("/");
    r->left=expression_derivation(r1);
    r->right=binarytree_clone(r2);

  }
  // le cas du - de signe n'est pas bien implémenter encore
  /* else if (r1->value.type==VALEUR){
    r->value.string="/";
    r->value.type = OPERATEUR_BINAIRE;
    expression_t rtmp, rtmp2;
    // v^2
    rtmp->value.string="^";
    rtmp->value.type = OPERATEUR_BINAIRE;
    rtmp->left = binarytree_clone(r2);
    rtmp->right = expression_node_new("2");
    r->right=binarytree_clone(rtmp);
    //u'v-uv'
    rtmp->value.string="-";
    rtmp->value.type = OPERATEUR_BINAIRE;

    rtmp2->value.string="*";
    rtmp2->value.type = OPERATEUR_BINAIRE;
    // u'v
    rtmp->left=NULL;
    //uv'
    rtmp2->left = binarytree_clone(r1);
    rtmp2->right = expression_derivation(r2);
    rtmp->right=binarytree_clone(rtmp2);
    // (u'v - uv')/v^2
    r->left=binarytree_clone(rtmp);
    // on libère
    rtmp=binarytree_del(rtmp);rtmp2=binarytree_del(rtmp2);
  }*/
  else{
    r=expression_node_new("/");
    expression_t rtmp, rtmp2;
    // v^2
    rtmp=expression_node_new("^");
    rtmp->left = binarytree_clone(r2);
    rtmp->right = expression_node_new("2");
    r->right=binarytree_clone(rtmp);
    //u'v-uv'
    rtmp->value.string="-";
    rtmp->value.type = OPERATEUR_BINAIRE;

    rtmp2=expression_node_new("*");
    // u'v
    rtmp2->right = binarytree_clone(r2);
    rtmp2->left = expression_derivation(r1);
    rtmp->left=binarytree_clone(rtmp2);
    //uv'
    rtmp2->left = binarytree_clone(r1);
    rtmp2->right = expression_derivation(r2);
    rtmp->right=binarytree_clone(rtmp2);
    // (u'v - uv')/v^2
    r->left=binarytree_clone(rtmp);
    // on libère
    rtmp=binarytree_del(rtmp);rtmp2=binarytree_del(rtmp2);
  }
  return r;
}


int expression_equal(expression_t r1, expression_t r2) {
  // TODO
  return 0;
}


expression_t expression_deriv_simplify(expression_t r) {
  //TODO
   return NULL;
}
