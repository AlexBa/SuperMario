

#ifndef SUPERMARIO_SPRITE_H
#define SUPERMARIO_SPRITE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "texture.h"
#include "../component/component.h"

// Constants
#define SPRITE_COUNT 50
#define SPRITE_EMPTY 0

// Object
typedef struct sprite_t {
    int cashId;
    const char *name;
    SDL_Texture *texture;
} Sprite;

// Methods
Sprite spriteCache[SPRITE_COUNT];
Sprite* sprite_create(SDL_Renderer *renderer, const char* name);
void sprite_delete(Sprite *sprite);
Sprite* sprite_get(const char* name);
void sprite_render(SDL_Renderer *renderer, Sprite *sprite, int x, int y);

#endif
