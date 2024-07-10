#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "declarations.h"
#include "jeu.h"

void initialiserRect( SDL_Rect *rectCarte, SDL_Rect *rectBtn )
{
    int i;
    for( i = 0; i < 8; i++ )
    {
        rectCarte[i].w = 140;
        rectCarte[i].h = 160;
    }

    // 1ere ligne de cartes

    rectCarte[0].x = 55;
    rectCarte[0].y = 17;

    rectCarte[1].x = 250;
    rectCarte[1].y = 17;

    rectCarte[2].x = 445;
    rectCarte[2].y = 17;

    // 2e ligne de cartes

    rectCarte[3].x = 55;
    rectCarte[3].y = 194;

    rectCarte[4].x = 250;
    rectCarte[4].y = 194;

    rectCarte[5].x = 445;
    rectCarte[5].y = 194;

    // 3e ligne de cartes

    rectCarte[6].x = 55;
    rectCarte[6].y = 371;

    rectCarte[7].x = 250;
    rectCarte[7].y = 371;

    // boutons

    rectBtn[0].x = 445;
    rectBtn[0].y = 371;
    rectBtn[0].w = 140;
    rectBtn[0].h = 70;

    rectBtn[1].x = 445;
    rectBtn[1].y = 461;
    rectBtn[1].w = 140;
    rectBtn[1].h = 70;
}

void boutons( SDL_Surface *bg, SDL_Rect *rectBtn, SDL_Point survole )
{
    int i;
    SDL_Surface *btn[2];
    btn[0] = IMG_Load( "res/img/bouton_rejouer.png" );
    btn[1] = IMG_Load( "res/img/bouton_quitter.png" );
    // Blittage des boutons à l'écran

    for( i = 0; i < 2; i++ )
        SDL_BlitSurface( btn[i], NULL, bg, &rectBtn[i] );

    // Animation des boutons en cas de survol de la souris

    SDL_Surface *btn_survole[2];
    btn_survole[0] = IMG_Load( "res/img/bouton_rejouer_2.png" );
    btn_survole[1] = IMG_Load( "res/img/bouton_quitter_2.png" );
    for( i = 0; i < 2; i++ )
    {
        if( SDL_PointInRect( &survole, &rectBtn[i] ) == SDL_TRUE )
        {
            SDL_BlitSurface( btn_survole[i], NULL, bg, &rectBtn[i] );
        }
    }

    // Libération des ressources

    for( i = 0; i < 2; i++ )
    {
        SDL_FreeSurface( btn[i] );
        SDL_FreeSurface( btn_survole[i] );
    }
}

void jouer( SDL_Renderer *renderer, SDL_Point survole, SDL_Point clic, Uint32 tempsDepart )
{
    SDL_Surface *bg = IMG_Load( "res/bg/arriere_plan_2_c.jpg" );

    SDL_SetRenderDrawColor( renderer, 0, 228, 255, 255 );

    SDL_Rect rectCarte[8];
    SDL_Rect rectBtn[2];

    initialiserRect( &rectCarte, &rectBtn );

    int i;

    boutons( bg, &rectBtn, survole );

    // Chargement des cartes en mémoire

    SDL_Surface *carte[8];
    for( i = 0; i < 8; i++ )
        carte[i] = IMG_Load( "res/img/dos_de_carte.png" );

    // Blittage des cartes à l'écran

    for( i = 0; i < 8; i++ )
        SDL_BlitSurface( carte[i], NULL, bg, &rectCarte[i] );

    // Destruction des cartes chargées en mémoire

    for( i = 0; i < 8; i++ )
        SDL_FreeSurface( carte[i] );

    Uint32 tempsArrivee = SDL_GetTicks( );
    SDL_Surface *carteRetournee[8];
    carteRetournee[0] = IMG_Load( "res/img/carte_1.png" );
    carteRetournee[1] = IMG_Load( "res/img/carte_2.png" );
    carteRetournee[2] = IMG_Load( "res/img/carte_3.png" );
    carteRetournee[3] = IMG_Load( "res/img/carte_4.png" );
    carteRetournee[4] = IMG_Load( "res/img/carte_3.png" );
    carteRetournee[5] = IMG_Load( "res/img/carte_2.png" );
    carteRetournee[6] = IMG_Load( "res/img/carte_4.png" );
    carteRetournee[7] = IMG_Load( "res/img/carte_1.png" );

    if( (tempsArrivee - tempsDepart ) > 2000 )
    {
    // Blittage des cartes à l'écran

    for( i = 0; i < 8; i++ )
        SDL_BlitSurface( carteRetournee[i], NULL, bg, &rectCarte[i] );

    // Destruction des cartes chargées en mémoire

    }

    if( tempsArrivee - tempsDepart > 4500 )
    {
        for( i = 0; i < 8; i++ )
            carte[i] = IMG_Load( "res/img/dos_de_carte.png" );

        // Blittage des cartes à l'écran

        for( i = 0; i < 8; i++ )
            SDL_BlitSurface( carte[i], NULL, bg, &rectCarte[i] );

        // Destruction des cartes chargées en mémoire

        for( i = 0; i < 8; i++ )
            SDL_FreeSurface( carte[i] );
    }

    static double nbreMouv = 0;
    static int nbreCartesRet = 0;
    static int couple[2] = {0}, couples[8], couplesTrouvees[8] = {0};
    static double scoreDoub;

    scoreDoub = nbreMouv / 8;

    TTF_Font *font = TTF_OpenFont( "res/font/forte.ttf", 40 );

    SDL_Color couleurTexte = { 0, 228, 255, 255 };
    char score[4] = {0};
    //char motScore[] = "Score : ";
    char Unite[] = " mouv/carte (Score)";

    snprintf( score, 4, "%.2f", scoreDoub );

    //SDL_Surface *texte1 = TTF_RenderText_Blended( font, motScore, couleurTexte  );
    SDL_Surface *texte2 = TTF_RenderText_Blended( font, score, couleurTexte  );
    SDL_Surface *texte3 = TTF_RenderText_Blended( font, Unite, couleurTexte  );
    TTF_CloseFont( font );

    //SDL_Rect coordTexte1 = { 20, 545, texte1->w, texte1->h };
    SDL_Rect coordTexte2 = { 20, 545, texte2->w, texte2->h };
    SDL_Rect coordTexte3 = { texte2->w + 25, 545, texte3->w, texte3->h };

    //SDL_BlitSurface( texte1, NULL, bg, &coordTexte1 );
    SDL_BlitSurface( texte2, NULL, bg, &coordTexte2 );
    SDL_BlitSurface( texte3, NULL, bg, &coordTexte3 );

    //SDL_FreeSurface( texte1 );
    SDL_FreeSurface( texte2 );
    SDL_FreeSurface( texte3 );

    couples[0] = 1;
    couples[1] = 2;
    couples[2] = 3;
    couples[3] = 4;
    couples[4] = 3;
    couples[5] = 2;
    couples[6] = 4;
    couples[7] = 1;

    static int j = 0;
    if( j == 2 )
        j = 0;

    for( i = 0; i < 8; i++ )
    {
        if( SDL_PointInRect( &clic, &rectCarte[i]) == SDL_TRUE )
        {
            // 0 : Carte non retournée ET 1 : Carte retournée
            if( couplesTrouvees[i] != 1 && nbreCartesRet < 2 )
            {
                couple[j] = i;
                j++;

                if( clic.x != 0 && clic.y != 0 )
                    SDL_BlitSurface( carteRetournee[ couple[0] ], NULL, bg, &rectCarte[ couple[0] ] );

                nbreCartesRet++;
                nbreMouv++;
                couplesTrouvees[i] = 1;
            }
            else
            {

            }
        }
    }

    if( nbreCartesRet == 2 )
    {
        nbreCartesRet = 0;
        if( couples[ couple[0] ] == couples[ couple[1] ] )
        {
            //printf( "couple trouve\n" ); /////////////////////////////////////////////////////////////////////////////////
        }
        else
        {
            couplesTrouvees[ couple[ 0 ] ] = 0;
            couplesTrouvees[ couple[ 1 ] ] = 0;
            //printf( "rate\n" ); /////////////////////////////////////////////////////////////////////////////////
        }
    }

    for( i = 0; i < 8; i++ )
    {
        if( couplesTrouvees[i] == 1 )
        {
            SDL_BlitSurface( carteRetournee[i], NULL, bg, &rectCarte[i] );
        }
    }
    int partieTerminee = 1;
    for( i = 0; i < 8; i++ )
    {
        if( couplesTrouvees[i] == 0 )
            partieTerminee = 0;

    }

    TTF_Font *font2 = TTF_OpenFont( "res/font/computer.ttf", 100 );
    SDL_Color couleurTxt = { 0, 0, 0, 255 };
    SDL_Surface *txt = TTF_RenderText_Blended( font2, "PARTIE TERMINEE", couleurTxt );
    TTF_CloseFont( font2 );
    SDL_Rect rect = { ( 640 - txt->w ) / 2, ( 600 - txt->h ) / 2, txt->w, txt->h };

    for( i = 0; i < 8; i++ )
        SDL_RenderDrawRect( renderer, &rectCarte[i] );

    if( partieTerminee )
    {
        //printf( "gagne partie\n" );
        SDL_BlitSurface( txt, NULL, bg, &rect );

    }

    SDL_FreeSurface( txt );

    if( SDL_PointInRect( &clic, &rectBtn[1]) == SDL_TRUE )
        exit( 0 );

    // Libération des ressources

    for( i = 0; i < 8; i++ )
        SDL_FreeSurface( carteRetournee[i] );

    SDL_Texture *textureBg = SDL_CreateTextureFromSurface( renderer, bg );
    SDL_FreeSurface( bg );

    SDL_RenderCopy( renderer, textureBg, NULL, NULL );
    SDL_DestroyTexture( textureBg );

    //for( i = 0; i < 2; i++ )
        //SDL_RenderDrawRect( renderer, &rectBtn[i] );

}
