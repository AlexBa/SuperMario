#include "fireball.h"

Entity* fireball_create(float x, float y, char* direction) {
    Entity* enemy = entity_create();
    enemy->component_mask = CMP_BULLET | CMP_POSITION | CMP_VELOCITY | CMP_COLLISION | CMP_RENDER | CMP_STRAIGHT_MOVEMENT;
    enemy->bullet.type = "fireball";
    enemy->position.x = x;
    enemy->position.y = y;
    enemy->position.oldX = x;
    enemy->position.oldY = y;
    enemy->velocity.x = 100;
    enemy->velocity.y = 0;
    enemy->collision.bounds = malloc(sizeof(SDL_Rect));
    enemy->collision.bounds->x = (int) x;
    enemy->collision.bounds->y = (int) y;
    enemy->collision.bounds->w = 5;
    enemy->collision.bounds->h = 5;
    enemy->render.name = "fireball.bmp";
    enemy->straightMovement.direction = direction;

    return enemy;
}
