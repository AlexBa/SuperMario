#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL_rect.h>

#ifndef SUPERMARIO_COMPONENT_H
#define SUPERMARIO_COMPONENT_H

typedef struct cmp_render_t {
    const char* name;
} Render;

typedef struct cmp_position_t {
    float x;
    float y;
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

enum component {
    CMP_NONE = 0,
    CMP_RENDER = 1 << 0,
    CMP_POSITION = 1 << 1,
    CMP_VELOCITY = 1 << 2,
    CMP_COLLISION = 1 << 3,
    CMP_INPUT_PLAYER = 1 << 4,
    CMP_GRAVITATION = 1 << 5,
    CMP_STRAIGHT_MOVEMENT = 1 << 6,
    CMP_JUMP = 1 << 7
};

#endif //SUPERMARIO_COMPONENT_H
