#ifndef SUPERMARIO_TILE_H
#define SUPERMARIO_TILE_H

#include <SDL2/SDL.h>
#include "sprite.h"

// Constants
#define TILE_WIDTH 32
#define TILE_HEIGHT 32

// Object
typedef struct tile_t {
    int type;
    const char *name;
    Sprite *sprite;
    SDL_Rect *bounds;
} Tile;

enum tile_type {
    TILE_NONE = 0,
    TILE_BLOCK = 1 << 0
};

// Methods
Tile* tile_create(SDL_Renderer *renderer, const char* name, int type, int x, int y);
void tile_delete(Tile *tile);
void tile_render(SDL_Renderer *renderer, Tile *tile, SDL_Rect *camera);

#endif //SUPERMARIO_TILE_H
