#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "game/game.h"
Game *game = NULL;
int main(int argc, char** argv) {


    // Init SDL2
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("%s", SDL_GetError());
        return 1;
    }

    // Create the game
    game = game_create();
    if (game == NULL) {
        printf("ERROR: Failed to create the game.");
    }

    // Run the game
    game_run(game);
    game_delete(game);

    // Quit SDL2
    SDL_Quit();

    return 0;
}
