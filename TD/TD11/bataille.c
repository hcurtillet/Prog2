#include <stdio.h>
#include <stdlib.h>
#include "lifo.h"
#include "fifo.h"
#include "element.h"
#include "list.h"
#include "distribution.h"
#include "graph_print.h"

/* Dimension de la fenetre */
#define  DIMX 500
#define  DIMY 700

/* Posiiton en X du jeu du joueur 1 */
#define POS_X_FILE1 50
/* Posiiton en X de la pile de batailleu du joueur 1 */
#define POS_X_PILE1 150
/* Posiiton en X du jeu du joueur 2 */
#define POS_X_FILE2 350
/* Posiiton en X de la pile de batailleu du joueur 2 */
#define POS_X_PILE2 250
#define POS_Y (DIMY-120)

int main(){
    fifo_t j1=fifo_new();
    fifo_t j2=fifo_new();
    lifo_t p1=lifo_new();
    lifo_t p2=lifo_new();

    SDL_PHWindow* f1=NULL;
          /* On cree une fenetre graphique */
    f1=SDL_PH_CreateWindow(DIMX,DIMY);
    if (f1==NULL) { puts("Impossible d'ouvrir une fenetre"); exit(EXIT_FAILURE); }


    if (distribution(&j1, &j2, 2,13)==0) {
      printf("Tous les fichiers images de cartes ne sont pas disponibles\n");
      exit(EXIT_FAILURE);
    }

    /* On affiche le jeu e du joueur 1*/
fifo_draw(j1,f1,POS_X_FILE1,POS_Y);
    /* On affiche le jeu e du joueur 2*/
fifo_draw(j2,f1,POS_X_FILE2,POS_Y);
   /* On affiche la pile du joueur 1*/
lifo_draw(p1,f1,POS_X_PILE1,POS_Y);
    /* On affiche la pile du joueur 2*/
lifo_draw(p2,f1,POS_X_PILE2,POS_Y);

puts("Taper Return pour continuer");    getchar();
puts("On prend une carte de chaque joueur");
puts("On la met sur sa pile");

/* On efface les piles et les files des joueurs */
lifo_erase(p1,f1,POS_X_PILE1,POS_Y);
lifo_erase(p2,f1,POS_X_PILE2,POS_Y);
fifo_erase(j1,f1,POS_X_FILE1,POS_Y);
fifo_erase(j2,f1,POS_X_FILE2,POS_Y);

    CARTE ctmp1,ctmp2;
    while(!fifo_is_empty(j1) && !fifo_is_empty(j2)){
      ctmp1=fifo_dequeue(&j1);
      ctmp1.visible=1;
      p1=lifo_push(ctmp1,p1);
      ctmp2=fifo_dequeue(&j2);
      ctmp2.visible=1;
      p2=lifo_push(ctmp2,p2);
      lifo_draw(p1,f1,POS_X_PILE1,POS_Y);
      lifo_draw(p2,f1,POS_X_PILE2,POS_Y);
      fifo_draw(j1,f1,POS_X_FILE1,POS_Y);
      fifo_draw(j2,f1,POS_X_FILE2,POS_Y);
      puts("Taper Return pour continuer");    getchar();
      puts("On prend une carte de chaque joueur");
      puts("On la met sur sa pile");

      /* On efface les piles et les files des joueurs */
      lifo_erase(p1,f1,POS_X_PILE1,POS_Y);
      lifo_erase(p2,f1,POS_X_PILE2,POS_Y);
      fifo_erase(j1,f1,POS_X_FILE1,POS_Y);
      fifo_erase(j2,f1,POS_X_FILE2,POS_Y);
      while(ctmp1.rang==ctmp2.rang){
        if(fifo_is_empty(j1) || fifo_is_empty(j2)) break;
        ctmp1=fifo_dequeue(&j1);
        ctmp1.visible=0;
        p1=lifo_push(ctmp1,p1);
        ctmp2=fifo_dequeue(&j2);
        ctmp2.visible=0;
        p2=lifo_push(ctmp2,p2);
        lifo_draw(p1,f1,POS_X_PILE1,POS_Y);
        lifo_draw(p2,f1,POS_X_PILE2,POS_Y);
        fifo_draw(j1,f1,POS_X_FILE1,POS_Y);
        fifo_draw(j2,f1,POS_X_FILE2,POS_Y);
        puts("Taper Return pour continuer");    getchar();
        puts("On prend une carte de chaque joueur");
        puts("On la met sur sa pile");

        /* On efface les piles et les files des joueurs */
        lifo_erase(p1,f1,POS_X_PILE1,POS_Y);
        lifo_erase(p2,f1,POS_X_PILE2,POS_Y);
        fifo_erase(j1,f1,POS_X_FILE1,POS_Y);
        fifo_erase(j2,f1,POS_X_FILE2,POS_Y);
        if(fifo_is_empty(j1) || fifo_is_empty(j2)) break;
        ctmp1=fifo_dequeue(&j1);
        ctmp1.visible=1;
        p1=lifo_push(ctmp1,p1);
        ctmp2=fifo_dequeue(&j2);
        ctmp2.visible=1;
        p2=lifo_push(ctmp2,p2);
        lifo_draw(p1,f1,POS_X_PILE1,POS_Y);
        lifo_draw(p2,f1,POS_X_PILE2,POS_Y);
        fifo_draw(j1,f1,POS_X_FILE1,POS_Y);
        fifo_draw(j2,f1,POS_X_FILE2,POS_Y);
        puts("Taper Return pour continuer");    getchar();
        puts("On prend une carte de chaque joueur");
        puts("On la met sur sa pile");

        /* On efface les piles et les files des joueurs */
        lifo_erase(p1,f1,POS_X_PILE1,POS_Y);
        lifo_erase(p2,f1,POS_X_PILE2,POS_Y);
        fifo_erase(j1,f1,POS_X_FILE1,POS_Y);
        fifo_erase(j2,f1,POS_X_FILE2,POS_Y);
      }
      if (ctmp1.rang>ctmp2.rang){
        while(!lifo_is_empty(p1)){
          ctmp1=lifo_pop(&p1);
          ctmp1.visible=0;
          j1=fifo_enqueue(ctmp1,j1);
        }
        while(!lifo_is_empty(p2)){
          ctmp1=lifo_pop(&p2);
          ctmp1.visible=0;
          j1=fifo_enqueue(ctmp1,j1);
        }
      }
      else{
        while(!lifo_is_empty(p1)){
          ctmp1=lifo_pop(&p1);
          ctmp1.visible=0;
          j2=fifo_enqueue(ctmp1,j2);
        }
        while(!lifo_is_empty(p2)){
          ctmp1=lifo_pop(&p2);
          ctmp1.visible=0;
          j2=fifo_enqueue(ctmp1,j2);
        }
      }
    }
}
