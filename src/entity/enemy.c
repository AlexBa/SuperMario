#include "enemy.h"

/**
 * Create a new enemy
 * @param x The horizontal position
 * @param y The vertical position
 */
Entity* enemy_create(float x, float y) {
    Entity* enemy = entity_create();
    enemy->component_mask = CMP_POSITION | CMP_VELOCITY | CMP_COLLISION | CMP_RENDER |
                            CMP_GRAVITATION | CMP_STRAIGHT_MOVEMENT;
    enemy->position.x = x;
    enemy->position.y = y;
    enemy->position.oldX = x;
    enemy->position.oldY = y;
    enemy->velocity.x = 100;
    enemy->velocity.y = 100;
    enemy->collision.bounds = malloc(sizeof(SDL_Rect));
    enemy->collision.bounds->x = (int) x;
    enemy->collision.bounds->y = (int) y;
    enemy->collision.bounds->w = 32;
    enemy->collision.bounds->h = 32;
    enemy->straightMovement.direction = "left";
    enemy->render.name = "player.bmp";

    return enemy;
}
