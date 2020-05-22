#include <stdio.h>
#include <math.h>

#include <SDL2/SDL_phelma.h>

int main(int ar, char** ag) { int ligne=500,col=660,i,j,nbligne,nbcol;
  unsigned char** im;
  SDL_PHWindow* f;

  printf("Ce programme lit une image en niveau de gris sur 8 bits pgm dans un tableau 2D, affiche l'image dans une partie de la fenetre graphique, inverse l'image (noir --> blanc), et affiche cette image inversée a un autre endroit dnas la meme fenetre\n");

  if (ar !=2 || strstr(ag[1],".pgm")==NULL) {   fprintf(stderr,"Usage : %s fichierimage.pgm\n",ag[0]);
    exit(EXIT_FAILURE);
  }
    /* Lecture de l'image au format pgm */
  im=SDL_PH_ReadIm8(ag[1],&nbligne,&nbcol);
  if (im==NULL) { printf("Erreur chargement image %s\n",ag[1]); exit(0) ; }

    /* initialisation du systeme video,audio de la SDL */
  if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO| SDL_INIT_EVENTS) !=0) {
    fprintf(stderr,"initialisation de la SDL impossible : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }
    /* Creation d'une fenetre graphique de ligne lignes et col colonnes */
  if( ( f=SDL_PH_CreateWindow(col,ligne)) == NULL) {
    fprintf(stderr,"Creation de fenetre impossible : %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
  }

    /* Affichage de l'image en 100,10  dans la grande fenetre */
  SDL_PH_DrawIm8(f,im,nbligne,nbcol,100,10);

    /* Et maintenant, on attend */
  puts("Taper pour continuer"); getchar();

    /* On parcourt toute l'image et on inverse chaque pixel */
  for (i=0; i<nbligne; i++)
    for (j=0; j<nbcol; j++) {
      im[i][j]=255-im[i][j];
  }
    /* On affiche cette nouvelle image sur l'ecran, en position  350 150 */
  SDL_PH_DrawIm8(f,im,nbligne,nbcol,350,150);

  puts("Taper pour continuer"); getchar();
  /* Liberation memoire de l'image 2D */
  im=(unsigned char**)PH_DestroyImage((void**)im);
  /* Destruction de la fenetre graphique SDL Phelma */
  SDL_PH_DestroyWindow(f);
  SDL_Quit();
  exit(EXIT_SUCCESS);
}
