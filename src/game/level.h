#ifndef SUPERMARIO_LEVEL_H
#define SUPERMARIO_LEVEL_H

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "../graphic/sprite.h"
#include "../graphic/tile.h"
#include "../entity/entity.h"

// Constants
#define LEVEL_TILE_COUNT 10000
#define LEVEL_ENTITY_COUNT 1000
#define LEVEL_WIDTH 20
#define LEVEL_HEIGHT 10

// Object
typedef struct level_t {
    const char *name;
    Sprite *background;
    Tile *tiles[LEVEL_TILE_COUNT];
    Entity *entities[LEVEL_ENTITY_COUNT];
} Level;

// Methods
Level* level_create(SDL_Renderer *renderer, const char *name);
void level_delete(Level *level);
void level_add_tile(Level *level, Tile *tile);
void level_remove_tile(Level *level, Tile *tile);
void level_add_entity(Level *level, Entity *entity);
void level_remove_entity(Level *level, Entity *entity);
void level_render(SDL_Renderer *renderer, Level *level);

#endif
