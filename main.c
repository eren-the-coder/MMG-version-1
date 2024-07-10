#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "declarations.h"
#include "creditEtMenu.h"
#include "jeu.h"

int main( int argc, char* argv[] )
{
    SDL_Init( SDL_INIT_VIDEO );
    TTF_Init( );
    Mix_OpenAudio( 96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024 );

    SDL_Window *fenetre = NULL;
    SDL_Renderer *rendu = NULL;

    SDL_CreateWindowAndRenderer( LARGEUR_FENETRE, HAUTEUR_FENETRE, SDL_WINDOW_SHOWN, &fenetre, &rendu );
    SDL_SetWindowTitle( fenetre, "Mangone's Matching Game 1.0" );

    credit( rendu );

    Mix_Music *musique = Mix_LoadMUS( "res/son/musique.mp3" );
    Mix_VolumeMusic( 50 );
    Mix_PlayMusic( musique, -1 );

    SDL_Point survole = { 0, 0 };
    SDL_Point clic = { 0, 0 };
    SDL_bool quitter = SDL_FALSE;
    SDL_Event event;
    int idMenu = 0;
    Uint32 tempsDepart;
    while( !quitter )
    {
        choixDuMenu( rendu, idMenu, survole, clic, tempsDepart );
        while( SDL_PollEvent( &event ) )
        {
            switch( event.type )
            {
            case SDL_QUIT :
                quitter = SDL_TRUE;
                break;
            case SDL_KEYDOWN :
                if( idMenu == 0 )
                {
                    switch( event.key.keysym.sym )
                    {
                    case SDLK_ESCAPE :
                        quitter = SDL_TRUE;
                        break;
                    default :
                        idMenu++;
                        tempsDepart = SDL_GetTicks( );
                        break;
                    }
                }
                break;
            case SDL_MOUSEMOTION :
                survole.x = event.motion.x;
                survole.y = event.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN :
                clic.x = event.button.x;
                clic.y = event.button.y;
                break;
                default : break;
            }
        }
        SDL_RenderPresent( rendu );
        SDL_RenderClear( rendu );
        SDL_Delay( 200 );
    }

    SDL_DestroyRenderer( rendu );
    SDL_DestroyWindow( fenetre );
    Mix_FreeMusic( musique );
    Mix_CloseAudio( );
    TTF_Quit( );
    SDL_Quit( );
    return 0;
}
