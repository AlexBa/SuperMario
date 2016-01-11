#include <stdio.h>
#include <SDL2/SDL_rect.h>

#ifndef SUPERMARIO_COMPONENT_H
#define SUPERMARIO_COMPONENT_H

typedef struct cmp_render_t {
    const char* name;
} Render;

typedef struct cmp_position_t {
    float x;
    float y;
} Position;

typedef struct cmp_velocity_t {
    float x;
    float y;
} Velocity;

typedef struct cmp_collision_t
{
    SDL_Rect *bounds;
} Collision;

enum component {
    CMP_NONE = 0,
    CMP_RENDER = 1 << 0,
    CMP_POSITION = 1 << 1,
    CMP_VELOCITY = 1 << 2,
    CMP_COLLISION = 1 << 3,
    CMP_INPUT_PLAYER = 1 << 4
};

#endif //SUPERMARIO_COMPONENT_H
