#include <SDL2/SDL.h>
#include "sprite.h"

#ifndef SUPERMARIO_TILE_H
#define SUPERMARIO_TILE_H

#define TILE_COUNT 10000
#define TILE_SUCCESS 0
#define TILE_ERROR_NOT_FOUND -1
#define TILE_ERROR_NO_SPACE_AVAILABLE -2
#define TILE_ERROR_OUT_OF_RANGE -3

typedef struct tiles_t {
    int types[TILE_COUNT];
    const char *names[TILE_COUNT];
    int sprites[TILE_COUNT];
    int x[TILE_COUNT];
    int y[TILE_COUNT];
    int width[TILE_COUNT];
    int height[TILE_COUNT];
} Tiles;

enum tile_type {
    TILE_NONE = 0,
    TILE_BLOCK = 1 << 0
};

Tiles tiles;
int tile_create(SDL_Renderer *renderer, const char* name, int type, int x, int y);
int tile_delete(int tile);
int tile_get_by_position(int x, int y);
void tile_render(SDL_Renderer *renderer, int tile);

#endif //SUPERMARIO_TILE_H
