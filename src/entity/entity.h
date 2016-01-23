#ifndef SUPERMARIO_ENTITY_H
#define SUPERMARIO_ENTITY_H

#include <stdio.h>
#include "../component/component.h"
#include "../graphic/sprite.h"

// Object
typedef struct entity_t {
    int component_mask;
    Render render;
    Position position;
    Velocity velocity;
    Collision collision;
    Gravitation gravitation;
    Straight_Movement straightMovement;
    Jump jump;
    Check_Point check_point;
    Item item;
    Health health;
    Deadly deadly;
    Shooting shooting;
    Bullet bullet;
} Entity;

// Methods
Entity* entity_create();
void entity_delete(Entity *entity);
void entity_render(SDL_Renderer *renderer, Entity *entity);

#endif
