#ifndef SUPERMARIO_COMPONENT_H
#define SUPERMARIO_COMPONENT_H

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL_rect.h>
#include "../graphic/sprite.h"

typedef struct cmp_render_t {
    const char *name;
} Render;

typedef struct cmp_position_t {
    float x;
    float y;
    float oldX;
    float oldY;
} Position;

typedef struct cmp_velocity_t {
    float x;
    float y;
} Velocity;

typedef struct cmp_collision_t {
    SDL_Rect *bounds;
} Collision;

typedef struct cmp_gravitation_t {
} Gravitation;

typedef struct cmp_straight_movement_t {
    char *direction;
} Straight_Movement;

typedef struct cmp_jump_t {
    bool active;
    float initialForce;
    float currentForce;
    float maxFallSpeed;
} Jump;

typedef struct cmp_item_t {
    char *type;
} Item;

typedef struct cmp_check_point_t {
    float x;
    float y;
} Check_Point;

typedef struct cmp_health {
    int counter;
} Health;

typedef struct cmp_deadly {
    bool isDead;
} Deadly;

typedef struct cmp_shooting {
    bool ready;
    const char *bulletType;
    int bulletSize;
    float rate;
    float elapsed;
    float velocityX;
    float velocityY;
    char *direction;
} Shooting;

typedef struct cmp_bullet {
    const char *type;
} Bullet;

typedef struct cmp_player {
    bool alive;
    bool vulnerable;
    char *touchedItem;
} Player;

typedef struct cmp_enemy {
    bool alive;
    bool vulnerable;
} Enemy;

typedef struct cmp_pyro {
} Pyro;


enum component {
    CMP_NONE = 0,
    CMP_RENDER = 1 << 0,
    CMP_POSITION = 1 << 1,
    CMP_VELOCITY = 1 << 2,
    CMP_COLLISION = 1 << 3,
    CMP_INPUT_PLAYER = 1 << 4,
    CMP_GRAVITATION = 1 << 5,
    CMP_STRAIGHT_MOVEMENT = 1 << 6,
    CMP_JUMP = 1 << 7,
    CMP_CHECK_POINT = 1 << 8,
    CMP_ITEM = 1 << 9,
    CMP_HEALTH = 1 << 10,
    CMP_PLAYER = 1 << 11,
    CMP_ENEMY = 1 << 12,
    CMP_DEADLY = 1 << 13,
    CMP_SHOOTING = 1 << 14,
    CMP_BULLET = 1 << 15,
    CMP_PYRO = 1 << 16,
};

#endif //SUPERMARIO_COMPONENT_H
