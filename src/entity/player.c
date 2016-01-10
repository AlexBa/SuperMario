#include "player.h"

unsigned int player_create(Entities *entities, float x, float y)
{
    unsigned int entity = entity_create(entities);
    entities->component_mask[entity] = CMP_POSITION | CMP_COLLISION | CMP_RENDER | CMP_INPUT_PLAYER;
    entities->positions[entity].x = x;
    entities->positions[entity].y = y;
    entities->collisions[entity].x = x;
    entities->collisions[entity].y = y;
    entities->renders[entity].name = "player.bmp";

    return entity;
}
