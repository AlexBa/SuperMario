#include "mushroom.h"

/**
 * Create a new mushroom
 * @param x The horizontal position
 * @param y The vertical position
 */
Entity* fireflower_create(float x, float y) {
    Entity *fireflower = entity_create();
    fireflower->component_mask = CMP_POSITION | CMP_COLLISION | CMP_RENDER | CMP_ITEM;
    fireflower->position.x = x;
    fireflower->position.y = y;
    fireflower->position.oldX = x;
    fireflower->position.oldY = y;
    fireflower->render.name = "fireflower.bmp";
    fireflower->item.type = "fireflower";
    fireflower->collision.bounds = malloc(sizeof(SDL_Rect));
    fireflower->collision.bounds->x = (int) x;
    fireflower->collision.bounds->y = (int) y;
    fireflower->collision.bounds->w = 32;
    fireflower->collision.bounds->h = 32;

    return fireflower;
}
