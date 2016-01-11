#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "../graphic/sprite.h"
#include "../graphic/tile.h"

#ifndef SUPERMARIO_LEVEL_H
#define SUPERMARIO_LEVEL_H

#define LEVEL_TILE_COUNT 10000

typedef struct level_t {
    const char *name;
    Sprite *background;
    int tileFree[LEVEL_TILE_COUNT];
    Tile *tiles[LEVEL_TILE_COUNT];
} Level;

Level* level_create(SDL_Renderer *renderer, const char *name);
void level_delete(Level *level);
void level_add_tile(Level *level, Tile *tile);
void level_remove_tile(Level *level, Tile *tile);
void level_render(SDL_Renderer *renderer, Level *level);

#endif //SUPERMARIO_LEVEL_H
