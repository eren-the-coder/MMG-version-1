#ifndef CREDITETMENU_H_INCLUDED
#define CREDITETMENU_H_INCLUDED

    // Fonction qui dessine Le Logo MANGONE GAME à l'écran

    void credit( SDL_Renderer *renderer );

    // Fonction qui dessine le menu

    void menu( SDL_Renderer *renderer, int idMenu );

    // Fonction qui choisi le menu à dessiner

    void jouer( SDL_Renderer *renderer, SDL_Point survole, SDL_Point clic, Uint32 tempsDepart );

    // Fonction qui affiche le logo du jeu

    void titreJeu( SDL_Renderer *renderer );

#endif // CREDITETMENU_H_INCLUDED
