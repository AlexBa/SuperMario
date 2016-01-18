//
// Created by Alex on 18.01.2016.
//

#include "enemy.h"

unsigned int enemy_create(Entities *entities, float x, float y) {
    unsigned int entity = entity_create(entities);
    entities->component_mask[entity] = CMP_POSITION | CMP_VELOCITY | CMP_COLLISION | CMP_RENDER | CMP_GRAVITATION | CMP_STRAIGHT_MOVEMENT;
    entities->positions[entity].x = x;
    entities->positions[entity].y = y;
    entities->velocities[entity].x = 100;
    entities->velocities[entity].y = 100;
    entities->collisions[entity].bounds = malloc(sizeof(SDL_Rect));
    entities->collisions[entity].bounds->x = (int) x;
    entities->collisions[entity].bounds->y = (int) y;
    entities->collisions[entity].bounds->w = 32;
    entities->collisions[entity].bounds->h = 32;
    entities->straightMovements[entity].direction = "left";
    entities->renders[entity].name = "player.bmp";

    return entity;
}
