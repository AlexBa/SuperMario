#include "player.h"

unsigned int player_create(Entities *entities, float x, float y) {
    unsigned int entity = entity_create(entities);
    entities->component_mask[entity] = CMP_POSITION | CMP_VELOCITY | CMP_COLLISION | CMP_RENDER | CMP_INPUT_PLAYER;
    entities->positions[entity].x = x;
    entities->positions[entity].y = y;
    entities->velocities[entity].x = .5f;
    entities->velocities[entity].y = .5f;
    entities->collisions[entity].bounds = malloc(sizeof(SDL_Rect));
    entities->collisions[entity].bounds->x = (int) x;
    entities->collisions[entity].bounds->y = (int) y;
    entities->renders[entity].name = "player.bmp";

    return entity;
}
