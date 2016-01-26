#include "pyro.h"

Entity *pyro_create(float x, float y, char* direction) {
    Entity* pyro = entity_create();
    pyro->component_mask = CMP_POSITION | CMP_VELOCITY | CMP_COLLISION | CMP_RENDER |
                            CMP_GRAVITATION | CMP_SHOOTING | CMP_ENEMY;// | CMP_STRAIGHT_MOVEMENT;
    pyro->position.x = x;
    pyro->position.y = y;
    pyro->position.oldX = x;
    pyro->position.oldY = y;
    pyro->velocity.x = 100;
    pyro->velocity.y = 100;
    pyro->collision.bounds = malloc(sizeof(SDL_Rect));
    pyro->collision.bounds->x = (int) x;
    pyro->collision.bounds->y = (int) y;
    pyro->collision.bounds->w = 32;
    pyro->collision.bounds->h = 32;
    pyro->shooting.ready = false;
    pyro->shooting.bulletType = "fireball";
    pyro->shooting.bulletSize = 5;
    pyro->shooting.direction = direction;
    pyro->shooting.rate = 3.0f;
    pyro->shooting.elapsed = 0;
    pyro->shooting.velocityX = 100;
    pyro->shooting.velocityY = 0;
    //pyro->straightMovement.direction = "left";
    pyro->render.name = "pyro.bmp";

    return pyro;
}
