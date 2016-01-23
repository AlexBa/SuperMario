#ifndef SUPERMARIO_SYSTEM_H
#define SUPERMARIO_SYSTEM_H

#include <stdio.h>
#include "../entity/entity.h"
#include "../component/component.h"
#include "collision.h"
#include "../game/game.h"
#include "../graphic/sprite.h"
#include "../game/level.h"
#include "../entity/entity.h"
#include "../entity/fireball.h"

// Constants
#define SYSTEM_GRAVITY_FACTOR 35

// Methods
void system_input_update(Entity *entity, const Uint8 *key, float delta);
void system_gravitation_update(Entity *entity, float delta);
void system_straight_movement_update(Entity *entity, float delta);
void system_health_update(Entity *entity, Level *level);
void system_collision_update(Entity *entity, Level *level);
void system_deadly_update(Entity *entity, Level *level);
void system_shooting_update(Entity *entity, Level *level, float delta);
void system_bullet_update(Entity *entity, Level *level);

#endif
