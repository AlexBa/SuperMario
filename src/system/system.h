#include <stdio.h>
#include "../entity/entity.h"
#include "../component/component.h"
#include "collision.h"
#include "../graphic/sprite.h"
#include "../game/level.h"
#include "../entity/entity.h"

#ifndef SUPERMARIO_SYSTEM_H
#define SUPERMARIO_SYSTEM_H

void sys_input_update(Level *level, Entities *entities, const Uint8 *key, float delta);
void sys_render_update(Entities *entities, SDL_Renderer *renderer);
void sys_gravitation_update(Level *level, Entities *entities, float delta);

#endif //SUPERMARIO_SYSTEM_H
