#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

void initialiserRect( SDL_Rect *rectCarte, SDL_Rect *rectBtn );

void boutons( SDL_Surface *bg, SDL_Rect *rectBtn, SDL_Point survole );

void jouer( SDL_Renderer *renderer, SDL_Point survole, SDL_Point clic, Uint32 tempsDepart );

#endif // JEU_H_INCLUDED

