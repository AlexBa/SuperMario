#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "../component/component.h"
#include "texture.h"
#include <stdbool.h>

#ifndef SUPERMARIO_SPRITE_H
#define SUPERMARIO_SPRITE_H

#define SPRITE_COUNT 50
#define SPRITE_EMPTY 0

typedef struct sprite_t {
    int cashId;
    const char *name;
    SDL_Texture *texture;
} Sprite;

Sprite spriteCache[SPRITE_COUNT];
Sprite* sprite_create(SDL_Renderer *renderer, const char* name);
void sprite_delete(Sprite *sprite);
Sprite* sprite_get(const char* name);
void sprite_render(SDL_Renderer *renderer, Sprite *sprite, int x, int y);

#endif
