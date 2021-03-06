#include "coin.h"

/**
 * Create a new coin
 * @param x The horizontal position
 * @param y The vertical position
 */
Entity* coin_create(float x, float y) {
    Entity* coin = entity_create();
    coin->component_mask = CMP_POSITION | CMP_COLLISION | CMP_RENDER | CMP_GRAVITATION | CMP_ITEM;
    coin->position.x = x;
    coin->position.y = y;
    coin->position.oldX = x;
    coin->position.oldY = y;
    coin->collision.bounds = malloc(sizeof(SDL_Rect));
    coin->collision.bounds->x = (int) x;
    coin->collision.bounds->y = (int) y;
    coin->collision.bounds->w = 0;
    coin->collision.bounds->h = 0;
    coin->render.name = "coin.bmp";
    coin->item.type = "coin";

    return coin;
}