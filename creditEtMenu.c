#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "creditEtMenu.h"
#include "declarations.h"
#include "jeu.h"
#define TAILLE_TEXTE_QUITTER 30

// Fonction qui dessine Le Logo MANGONE GAME à l'écran

void credit( SDL_Renderer *renderer )
{
    SDL_Surface *logo = IMG_Load( "res/logo/Logo_MG.png" );
    SDL_Texture *tLogo = SDL_CreateTextureFromSurface( renderer, logo );
    SDL_FreeSurface( logo );

    SDL_RenderCopy( renderer, tLogo, NULL, NULL );
    SDL_RenderPresent( renderer );

    SDL_Delay( 3000 );

    SDL_DestroyTexture( tLogo );
    SDL_RenderClear( renderer );

}

// logo du jeu

void titreJeu( SDL_Renderer *renderer )
{
    //SDL_Surface *logo = IMG_Load(  )
}

// Fonction qui dessine le menu

void menu( SDL_Renderer *renderer, int idMenu )
{
    SDL_Surface *bg = IMG_Load( "res/bg/arriere_plan_0.jpg" );

    TTF_Init(  );

    static int tailleTexte = 30;

    TTF_Font *font = TTF_OpenFont( "res/font/forte.ttf", tailleTexte );
    TTF_Font *font2 = TTF_OpenFont( "res/font/forte.ttf", TAILLE_TEXTE_QUITTER );
    tailleTexte += 1;

    if( tailleTexte > 37 )
        tailleTexte = 30;

    SDL_Color couleur = { 255, 255, 255, 255 };
    SDL_Surface *texte = TTF_RenderText_Blended( font, "Appuyez sur une touche pour jouer", couleur );
    SDL_Surface *texte2 = TTF_RenderText_Blended( font2, "Appuyez sur Echap pour quitter", couleur );

    TTF_CloseFont( font );
    TTF_CloseFont( font2 );

    SDL_Rect dst = { ( LARGEUR_FENETRE / 2 ) - (texte->w / 2), 300, texte->w, texte->h };
    SDL_Rect dst2 = { ( LARGEUR_FENETRE / 2 ) - (texte2->w / 2), 400, texte2->w, texte2->h };

    SDL_BlitSurface( texte, NULL, bg, &dst );
    SDL_BlitSurface( texte2, NULL, bg, &dst2 );

    SDL_FreeSurface( texte );
    SDL_FreeSurface( texte2 );

    SDL_Texture *tBg = SDL_CreateTextureFromSurface( renderer, bg );
    SDL_FreeSurface( bg );
    SDL_RenderCopy( renderer, tBg, NULL, NULL );

    SDL_DestroyTexture( tBg );
    TTF_Quit(  );
}

// Fonction qui choisi le menu à dessiner

void choixDuMenu( SDL_Renderer *renderer, int idMenu, SDL_Point survole, SDL_Point clic, Uint32 tempsDepart )
{
    switch( idMenu )
    {
    case 0 :
        menu( renderer, idMenu );
        break;
    case 1 :
        jouer( renderer, survole, clic, tempsDepart );
        break;
    }
}

