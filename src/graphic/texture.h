#ifndef SUPERMARIO_TEXTURE_H
#define SUPERMARIO_TEXTURE_H

#include <stdio.h>
#include <SDL2/SDL.h>

// Methods
SDL_Texture* texture_create(SDL_Renderer *renderer, const char* name);
void texture_delete(SDL_Texture *texture);
void texture_render(SDL_Renderer *renderer, SDL_Texture * texture, int x, int y);

#endif
