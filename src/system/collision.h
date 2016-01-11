#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#ifndef SUPERMARIO_COLLISION_H
#define SUPERMARIO_COLLISION_H

bool collision_check(SDL_Rect *rect1, SDL_Rect *rect2);

#endif //SUPERMARIO_COLLISION_H
