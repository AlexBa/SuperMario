#include <stdio.h>

#ifndef SUPERMARIO_COMPONENT_H
#define SUPERMARIO_COMPONENT_H

typedef struct
{
    float x;
    float y;
} cmp_position;

typedef struct
{
    float x;
    float y;
    float width;
    float height;
} cmp_collision;

enum component
{
    CMP_NONE = 0,
    CMP_POSITION = 1 << 0,
    CMP_COLLISION = 1 << 1,
};

#endif //SUPERMARIO_COMPONENT_H
