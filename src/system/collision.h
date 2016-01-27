#ifndef SUPERMARIO_COLLISION_H
#define SUPERMARIO_COLLISION_H

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "../game/level.h"
#include "../graphic/tile.h"
#include "../entity/entity.h"

// Methods
bool collision_check(SDL_Rect *rect1, SDL_Rect *rect2);
bool collision_check_level(Level *level, SDL_Rect *rect);
bool collision_check_entities(Entity *entities[], SDL_Rect *rect);
bool collision_check_tiles(Tile *tiles[], SDL_Rect *rect);
bool collision_check_deadly_entities(Entity *entities[], SDL_Rect *rect);
bool collision_check_player_kills_enemy(Entity *entities[], Entity *player);
bool collision_check_enemy_kills_player(Entity *entities[], Entity *enemy);
bool collision_check_item_touches_player(Entity *entities[], Entity *item);
bool collision_check_bullet_kills_enemy(Entity *entities[], Entity *bullet);
bool collision_check_bullet_kills_player(Entity *entities[], Entity *bullet);

#endif //SUPERMARIO_COLLISION_H
