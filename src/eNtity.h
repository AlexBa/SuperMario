#include <stdio.h>
#include "component.h"

#ifndef SUPERMARIO_ENTITY_H
#define SUPERMARIO_ENTITY_H

#define ENTITY_COUNT 1000

struct entities_t
{
    int component_mask[ENTITY_COUNT];
    cmp_position positions[ENTITY_COUNT];
    cmp_collision collisions[ENTITY_COUNT];
};

typedef struct entities_t Entities;

unsigned int entity_create(Entities *entities);

void entity_destroy(Entities *entities, unsigned int entity_id);

#endif //SUPERMARIO_ENTITY_H
