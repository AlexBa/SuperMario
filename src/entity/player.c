#include "player.h"

/**
 * Create a new player
 * @param x The horizontal position
 * @param y The vertical position
 */
Entity* player_create(float x, float y) {
    Entity *player = entity_create();
    player->component_mask = CMP_POSITION | CMP_VELOCITY | CMP_COLLISION | CMP_RENDER |
                             CMP_INPUT_PLAYER | CMP_GRAVITATION | CMP_JUMP;
    player->position.x = x;
    player->position.y = y;
    player->position.oldX = x;
    player->position.oldY = y;
    player->velocity.x = 150;
    player->velocity.y = 150;
    player->collision.bounds = malloc(sizeof(SDL_Rect));
    player->collision.bounds->x = (int) x;
    player->collision.bounds->y = (int) y;
    player->collision.bounds->w = 32;
    player->collision.bounds->h = 32;
    player->render.name = "player.bmp";
    player->jump.active = false;
    player->jump.initialForce = 320;
    player->jump.currentForce = 0;
    player->jump.maxFallSpeed = 3;

    return player;
}
