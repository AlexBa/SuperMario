#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "../component/component.h"
#include "texture.h"
#include <stdbool.h>

#ifndef SUPERMARIO_SPRITE_H
#define SUPERMARIO_SPRITE_H

#define SPRITE_COUNT 50
#define SPRITE_SUCCESS 0
#define SPRITE_ERROR_NOT_FOUND -1
#define SPRITE_ERROR_NO_SPACE_AVAILABLE -2
#define SPRITE_ERROR_OUT_OF_RANGE -3

typedef struct sprites_t {
    const char *names[SPRITE_COUNT];
    SDL_Texture *textures[SPRITE_COUNT];
} Sprites;

Sprites sprites;
int sprite_create(SDL_Renderer *renderer, const char* name);
int sprite_delete(int sprite);
int sprite_get(const char* name);
void sprite_render(SDL_Renderer *renderer, const char *name, int x, int y);

#endif
