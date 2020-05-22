/*! \file SDL_phelma.h
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
/*
 * #include <SDL2/SDL_mixer.h>
 * */
#include <SDL2/SDL2_gfxPrimitives.h>

#ifndef _SDL_PHELMA_H_
#define _SDL_PHELMA_H_

/**  */

/**
 * \struct SDL_PHWindow SDL_phelma.h "SDL2/SDL_phelma.h"
 * \brief La structure assurant l'interface avec la SDL2.
 *
 * Les dessins se font dans le contexte de rendu.
 *
 * Les images utilisent la texture qui est ensuite ecrite dans le contexte de rendu
 *
 */
typedef struct {
  SDL_Window * fenetre; /**< la fenetre SDL2. */
  SDL_Renderer * rendu; /**< le contexte de rendu associe a cette fenetre, pour dessiner dans la fenetre*/
  SDL_Texture * image;  /**< une texture pre-almlouee pour la rapidite d'affichage des images */
  int h, /**< la hauteur de la fenetre */ w /**< la largeur de la fenetre */;
} SDL_PHWindow;


#ifndef _MACOS
/**  \def SDL_PH_RED
\brief Macro pour définir la composante ROUGE d'un pixel
*/
#define SDL_PH_RED 	0xFF0000FF
/**  \def SDL_PH_GREEN
\brief Macro pour définir la composante VERTE d'un pixel
*/
#define SDL_PH_GREEN 	0xFF00FF00
/**  \def SDL_PH_BLUE
\brief Macro pour définir la composante BLEUE d'un pixel
*/
#define SDL_PH_BLUE	0xFFFF0000
/**  \def SDL_PH_BLACK
\brief Macro pour définir le NOIR d'un pixel
*/
#define SDL_PH_BLACK	0xFF000000
#else

#define SDL_PH_RED    0x0000FF00

#define SDL_PH_GREEN     0x00FF0000

#define SDL_PH_BLUE     0xFF000000

#define SDL_PH_BLACK 	0x00000000

#endif

/**  \def SDL_PH_YELLOW
\brief Macro pour définir le JAUNE d'un pixel
*/
#define SDL_PH_YELLOW	(SDL_PH_RED|SDL_PH_GREEN)
/**  \def SDL_PH_MAGENTA
\brief Macro pour définir le MAGENTA d'un pixel
*/
#define SDL_PH_MAGENTA  (SDL_PH_RED|SDL_PH_BLUE)
/**  \def SDL_PH_CYAN
\brief Macro pour définir le CYAN d'un pixel
*/
#define SDL_PH_CYAN	(SDL_PH_BLUE|SDL_PH_GREEN)
/**  \def SDL_PH_WHITE
\brief Macro pour définir le BLANC d'un pixel
*/
#define SDL_PH_WHITE 	(SDL_PH_BLUE|SDL_PH_GREEN|SDL_PH_RED)

#ifdef __cplusplus
extern "C" {
#endif

/* Creation d'une fenetre graphique de
  dimx pixels en horizontal,
  dimy pixels en vertical
  Couleur sur 32 bits en RougeVertBleuAlpha
  Fond blanc
  Interruption possible par CTRL+C
  Origine du repere (poitn de coordonnees 0,0 ) : en haut a gauche de la fenetre
*/
/** \brief  Creation et affichage d'une fenetre graphique
* \details La fonction cree une structure SDL_PHWindow et initialise les 3 structures utiles pour la SDL2 :
- une fenetre SDL_Window, composant de base de la SDL
- un contexte de rendu SDL_Renderer  qui est utile pour dessiner
- une texture SDL_Texture, utile pour l'affichage d'image dans notre cas.

Exemple d'utilisation

* \code
* #include <SDL2/SDL_phelma.h>
* int main(int ar, char** ag) {
*   SDL_PHWindow* f;
*   // initialisation du systeme video,audio et evenementiel de la SDL
*   if ( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO| SDL_INIT_EVENTS) !=0) {
*     fprintf(stderr,"initialisation de la SDL impossible : %s\n", SDL_GetError());
*     exit(EXIT_FAILURE);
*   }
*   // Creation d'une fenetre graphique de 100 lignes et 200 colonnes
*   if( ( f=SDL_PH_CreateWindow(100,200)) == NULL) {
*      fprintf(stderr,"Creation de fenetre impossible : %s\n", SDL_GetError());
*      exit(EXIT_FAILURE);
*   }
*
*   // Mon code qui affiche dnas la fenetre
*   // TODO
*
*   // Suppression de la fentre et quitter la SDL2
*   SDL_PH_DestroyWindow(f);
*   SDL_Quit();
* }
* \endcode
* @param [in] dimx : largeur de la fenetre
* @param [in] dimy : hauteur de la fenetre
* @return un pointeur vars la structure representant la fenetre
* @remarks CTRL C interrompt l'execution
* @remarks Le contexte de rendu (renderer) est specifie en mode SOFTWARE pour la compatibilite machine virtuelle, mac, linux,  windows
\sa demo1.c, demo2.c, demo3.c, demo4.c, demo5.c
*/

SDL_PHWindow* SDL_PH_CreateWindow(int dimx, int dimy) ;

/** \brief Destruction d'une fenetre graphique
* \details La fonction detruit les structures interne et libere la memoire allouee pour la structure SDL_PHWindow

* @param [in] f : la fenetre a detruire
* \sa SDL_PH_CreateWindow
*/
void SDL_PH_ClearWindow(SDL_PHWindow* f);

/** \brief Affichage du contenu d'une fenetre graphique
* \details La fonction provoque l'affichage a l'ecran du contenu de la fenetre graphique.
*
* Les fenetres graphiques sont bufferisees et l'affichage a l'ecran ne se fait pas a chaque dessin dnas la fenetre
* mais uniquement apres un appel a cette fonction.
* \code
  fenetre = SDL_PH_CreateWindow(dimx, dimy);
    // Cette fenetre est remplie par un rectangle de couleur verdatre (R=17, V=206, B=112),
    // chaque couleur primaire pouvant aller de 0 à 255
  boxRGBA(fenetre->rendu,0,0,dimx,dimy,17,206,112,255);

    //On affiche une ellispe en 100 200, axe 40 et 10, couleur Jaune,
  filledEllipseColor(fenetre->rendu, 100,200,40,10,SDL_PH_YELLOW);

  printf("Auncun afficheage encore. Taper une touche pour afficher"); getchar();
  // Mise à jour de l'ecran : affichage a l'ecran du rectangle et de l'ellipse
  SDL_PH_FlushWindow(fenetre);
  // Apres cette ligne, le rectangle et l'ellipse apparaisent a l'ecran
*\endcode
* @param [in] f : la fenetre dont le contenu va etre affiche

*/
void SDL_PH_DestroyWindow(SDL_PHWindow* f);

/** \brief Efface le contenu d'une fenetre graphique
* \details La fonction affiche un fond blanc.

* @param [in] f : la fenetre dont le contenu est efface
*/
void SDL_PH_FlushWindow(SDL_PHWindow* f) ;

#include <SDL2/SDL_PH_audioU8.h>
#include <SDL2/SDL_PH_audioS8.h>
#include <SDL2/SDL_PH_courbes.h>
#include <SDL2/SDL_phelma.h>
#include <SDL2/SDL_PH_image.h>
#include <SDL2/SDL_PH_tab.h>
#include <SDL2/SDL_PH_texte.h>


#ifdef __cplusplus
}
#endif
#endif


/******************/
// fonctions utilitaires de conversion
// "tableau de unsigned char" <-> "tableau de char"


static char* SDL_PH_SoundUcToC(unsigned char* son, int nb) {
    int i,a;
    for(i=0; i<nb; i++) {
        a = son[i]-127;
        son[i]=a;
    }
    return (char* ) son;
}

static unsigned char* SDL_PH_SoundCToUc( char* son, int nb) {
    int i,a;
    for(i=0; i<nb; i++) {
        a = son[i]+127;
        son[i]=a;
    }
    return (unsigned char* ) son;
}

/******************/



char* SDL_PH_GetCreateWavS8(char* filename, int* p_freq, int * p_nb_samples) {
    unsigned char * son_tmp = SDL_PH_GetCreateWavU8(filename, p_freq, p_nb_samples);
    if(son_tmp == NULL) {
        return NULL;
    }
    char * son = SDL_PH_SoundUcToC(son_tmp, *p_nb_samples);
    return son;
}


int SDL_PH_PlaySoundS8(char* son, int nb_samples, int fs) {
    unsigned char * son2 = calloc(nb_samples, sizeof(*son2));
    memcpy(son2, son, nb_samples * sizeof(*son));
    son2 = SDL_PH_SoundCToUc((char*)son2,nb_samples);
    int result = SDL_PH_PlaySoundU8(son2, nb_samples, fs);
    free(son2);
    return result;
}


int SDL_PH_PlayDrawSoundS8(char* son, int nb_samples, int fs, SDL_PHWindow* f, int coul) {
    unsigned char * son2 = calloc(nb_samples, sizeof(*son2));
    memcpy(son2, son, nb_samples * sizeof(*son));
    son2 = SDL_PH_SoundCToUc((char*)son2,nb_samples);
    int result = SDL_PH_PlayDrawSoundU8(son2, nb_samples, fs, f, coul);
    free(son2);
    return result;
}



void SDL_PH_PrintSoundS8( char* son, int nb) {
    int i;
    for(i=0; i<nb; i++) printf("%d ",son[i]);
}
