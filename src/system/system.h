#include <stdio.h>
#include "../entity/entity.h"
#include "../component/component.h"
#include "../sprite/sprite.h"

#ifndef SUPERMARIO_SYSTEM_H
#define SUPERMARIO_SYSTEM_H

void sys_input_update(Entities *entities, const Uint8 *key);
void sys_render_update(Entities *entities, Sprites *sprites, SDL_Renderer *renderer);

#endif //SUPERMARIO_SYSTEM_H
