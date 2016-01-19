#ifndef SUPERMARIO_GAME_H
#define SUPERMARIO_GAME_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "../entity/entity.h"
#include "../entity/player.h"
#include "../entity/enemy.h"
#include "../system/system.h"
#include "level.h"

// Object
typedef struct game_t {
    SDL_Window *window;
    SDL_Renderer *renderer;
    Level *level;
    bool pause;
    unsigned int last_ticks;
    unsigned int current_ticks;
    const Uint8 *key;
} Game;

// Methods
Game* game_create();
void game_delete(Game *game);
void game_run(Game *game);
void game_continue(Game *game);
void game_pause(Game *game);
void game_update(Game *game, float delta);
void game_render(Game *game, float delta);

#endif //SUPERMARIO_GAME_H
