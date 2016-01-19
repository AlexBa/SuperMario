#include <stdio.h>
#include "../component/component.h"
#include "../graphic/sprite.h"

#ifndef SUPERMARIO_ENTITY_H
#define SUPERMARIO_ENTITY_H

#define ENTITY_COUNT 1000

struct entities_t
{
    int component_mask[ENTITY_COUNT];
    Render renders[ENTITY_COUNT];
    Position positions[ENTITY_COUNT];
    Velocity velocities[ENTITY_COUNT];
    Collision collisions[ENTITY_COUNT];
    Gravitation gravitations[ENTITY_COUNT];
    Straight_Movement straightMovements[ENTITY_COUNT];
    Jump jumps[ENTITY_COUNT];
};

typedef struct entities_t Entities;

unsigned int entity_create(Entities *entities);

void entity_destroy(Entities *entities, unsigned int entity_id);

#endif //SUPERMARIO_ENTITY_H
