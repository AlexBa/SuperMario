#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#ifndef SUPERMARIO_MAP_H
#define SUPERMARIO_MAP_H

#define MAP_MAX_X 10
#define MAP_MAX_Y 10
#define MAP_TILE_SIZE 32

SDL_Surface *brickImage, *backgroundImage;

typedef struct Map
{
    int tile[MAP_MAX_Y][MAP_MAX_X];
} Map;

void map_load(Map *map, char *name);

#endif //SUPERMARIO_MAP_H
