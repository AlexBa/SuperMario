#include "mushroom.h"

/**
 * Create a new mushroom
 * @param x The horizontal position
 * @param y The vertical position
 */
Entity* mushroom_create(float x, float y) {
    Entity *mushroom = entity_create();
    mushroom->component_mask = CMP_POSITION | CMP_VELOCITY | CMP_COLLISION | CMP_RENDER |
                               CMP_GRAVITATION | CMP_ITEM | CMP_STRAIGHT_MOVEMENT;
    mushroom->position.x = x;
    mushroom->position.y = y;
    mushroom->position.oldX = x;
    mushroom->position.oldY = y;
    mushroom->render.name = "mushroom.bmp";
    mushroom->item.type = "mushroom";
    mushroom->velocity.x = 120;
    mushroom->velocity.y = 120;
    mushroom->collision.bounds = malloc(sizeof(SDL_Rect));
    mushroom->collision.bounds->x = (int) x;
    mushroom->collision.bounds->y = (int) y;
    mushroom->collision.bounds->w = 32;
    mushroom->collision.bounds->h = 32;
    mushroom->straightMovement.direction = "left";

    return mushroom;
}
