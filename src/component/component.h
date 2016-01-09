#include <stdio.h>

#ifndef SUPERMARIO_COMPONENT_H
#define SUPERMARIO_COMPONENT_H

typedef struct
{
    const char* name;
} cmp_render_t;
typedef cmp_render_t Render;

typedef struct
{
    float x;
    float y;
} cmp_position_t;
typedef cmp_position_t Position;

typedef struct
{
    float x;
    float y;
    float width;
    float height;
} cmp_collision_t;
typedef cmp_collision_t Collision;

enum component
{
    CMP_NONE = 0,
    CMP_RENDER = 1 << 0,
    CMP_POSITION = 1 << 1,
    CMP_COLLISION = 1 << 2,
    CMP_INPUT_PLAYER = 1 << 3
};

#endif //SUPERMARIO_COMPONENT_H
