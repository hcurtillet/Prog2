#include <stdio.h>
#include <math.h>

#include <SDL2/SDL_phelma.h>

int main(int argc, char *argv[])
{   SDL_PHWindow* fenetre;
    int dimx=1000, dimy=1000;

    printf("Ce programme teste l'affichage de forme deometrique simple avec la SDL\n");

    /* Iniitalisation de la SDL */
  if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO| SDL_INIT_EVENTS) !=0) {
    fprintf(stderr,"initialisation SDL impossible : %s ",SDL_GetError());
    exit(EXIT_FAILURE);
  }

        /* Creation d'une fenetre de dimension dimx x dimy, couleurs sur 32 bits */
    fenetre = SDL_PH_CreateWindow(dimx, dimy);
        /* Cette fenetre est remplie par un rectangle de couleur verdatre (R=17, V=206, B=112),
           chaque couleur primaire pouvant aller de 0 à 255 */
    boxRGBA(fenetre->rendu,0,0,dimx,dimy,17,206,112,255);

        /* Auto repeat du clavier */
    //SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

    /*  On affiche une ellispe en 100 200, axe 40 et 10, couleur Verte, pas de transparence
        les 4 dernies parametres representent R=0, V=255, B=0, Alpha(ou transparence)=255
    */
    filledEllipseColor(fenetre->rendu, 100,100,40,40,SDL_PH_YELLOW);
    SDL_PH_FlushWindow(fenetre); // Mise à jour de l'écran
    printf("Tapez une touche pour continuer\n"); getchar();

    /*  On affiche une ellispe en 300 200, axe 20 et 50, couleur Verte, pas de transparence
        les 4 dernies parametres representent R=0, V=128, B=255, Alpha(ou transparence)=255
    */
    filledEllipseColor(fenetre->rendu, 300,200,20,50,SDL_PH_BLUE);
    SDL_PH_FlushWindow(fenetre); // Mise à jour de l'écran
    printf("Tapez une touche pour continuer\n"); getchar();

    /* meme chose pour une ligne : attention au coordonnees, le point 0,0 est en haut a gauche */
    lineColor(fenetre->rendu, 10,20,300,200,0xFF<<24|120<<16|9<<8|245);
    SDL_PH_FlushWindow(fenetre); // Mise à jour de l'écran

    printf("Tapez une touche pour quitter\n"); getchar();
    SDL_PH_DestroyWindow(fenetre);
    SDL_Quit();

    return EXIT_SUCCESS;
  }
