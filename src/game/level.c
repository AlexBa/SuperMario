#include "level.h"
#include "../entity/coin.h"

/**
 * Create a new level
 * @param renderer
 * @param name
 */
Level* level_create(SDL_Renderer *renderer, const char *name) {
    Level *level = malloc(sizeof(Level));
    level->name = name;
    level->background = sprite_create(renderer, name);
    level->bounds.x = 0;
    level->bounds.y = 0;
    level->bounds.w = LEVEL_WIDTH * TILE_WIDTH;
    level->bounds.h = LEVEL_HEIGHT * TILE_HEIGHT;

    for (int i = 0; i < LEVEL_TILE_COUNT; i++) {
        level->tiles[i] = NULL;
    }

    for (int i = 0; i < LEVEL_ENTITY_COUNT; i++) {
        level->entities[i] = NULL;
    }

    char field [LEVEL_HEIGHT][LEVEL_WIDTH] = {"________________________________________________________________________ ",
                                              "|                                                                       |",
                                              "|             o    o                                                    |",
                                              "|         c                                                             |",
                                              "|        cc c                                                           |",
                                              "|      c cc c       c                                             c     |",
                                              "|     c  cc  c    c                                              ccc    |",
                                              "|       cc c  c   c                                             ccccc   |",
                                              "|                                                              ccccccc  |",
                                              "______________________ _______________________   ___________ ___________ ",};

    for (int i = 0; i < LEVEL_HEIGHT; i++) {
        for (int j = 0; j < LEVEL_WIDTH; j++) {
            if (field[i][j] == '_') {
                Tile *tile = tile_create(renderer, "brick.bmp", TILE_BLOCK, (j * TILE_WIDTH), (i * TILE_HEIGHT));
                level_add_tile(level, tile);
            } else if (field [i][j] == '|') {
                Tile *tile = tile_create(renderer, "brick.bmp", TILE_BLOCK, (j * TILE_WIDTH), (i * TILE_HEIGHT));
                level_add_tile(level, tile);
            } else if (field [i][j] == 'c') {
                Tile *tile = tile_create(renderer, "brick.bmp", TILE_BLOCK, (j * TILE_WIDTH), (i * TILE_HEIGHT));
                level_add_tile(level, tile);
            } else if (field [i][j] == 'o') {
                Entity *coin = coin_create(500.0f, 60.0f);
                level_add_entity(level, coin);
            }

        }
    }

    return level;
}

/**
 * Delete the level
 * @param level
 */
void level_delete(Level *level) {
    for (int i = 0; i < LEVEL_TILE_COUNT; i++) {
        Tile *tile = level->tiles[i];
        level_remove_tile(level, tile);
        tile_delete(tile);
    }

    for (int i = 0; i < LEVEL_TILE_COUNT; i++) {
        Entity *entity = level->entities[i];
        level_remove_entity(level, entity);
        entity_delete(entity);
    }

    free(level);
}

/**
 * Add a tile to the level
 * @param level
 * @param tile
 */
void level_add_tile(Level *level, Tile *tile) {
    for (int i = 0; i < LEVEL_TILE_COUNT; i++) {
        if (level->tiles[i] == NULL) {
            level->tiles[i] = tile;
            return;
        }
    }

    printf("Error: Failed to add the tile '%s' to the level '%s'. No more space available.\n", level->name, tile->name);
    exit(1);
}

/**
 * Remove a tile from the level
 * @note You have to free the space of the tile by your own
 * @param level
 * @param tile
 */
void level_remove_tile(Level *level, Tile *tile) {
    for (int i = 0; i < LEVEL_TILE_COUNT; i++) {
        if (level->tiles[i] == tile) {
            level->tiles[i] = NULL;
            return;
        }
    }

    printf("Error: Failed to remove the tile '%s' to the level '%s'. Tile not found.\n", level->name, tile->name);
    exit(1);
}

/**
 * Add an entity to the level
 * @param level
 * @param entity
 */
void level_add_entity(Level *level, Entity *entity) {
    for (int i = 0; i < LEVEL_ENTITY_COUNT; i++) {
        if(level->entities[i] == NULL) {
            level->entities[i] = entity;
            return;
        }
    }

    printf("Error: Failed to add an entity to the level '%s'. No more space available.\n", level->name);
    exit(1);
}

/**
 * Remove an entity from the level
 * @note You have to free the space of the entity by your own
 * @param level
 * @param entity
 */
void level_remove_entity(Level *level, Entity *entity) {
    for (int i = 0; i < LEVEL_ENTITY_COUNT; i++) {
        if(level->entities[i] == entity) {
            level->entities[i] = NULL;
            return;
        }
    }

    printf("Error: Failed to remove an entity from the level '%s'. Entity not found.\n", level->name);
    exit(1);
}

/**
 * Render the level to the screen
 * @param renderer
 * @param level
 */
void level_render(SDL_Renderer *renderer, Level *level) {
    sprite_render(renderer, level->background, 0, 0);

    for (int i = 0; i < LEVEL_TILE_COUNT; i++) {
        if (level->tiles[i] != NULL) {
            tile_render(renderer, level->tiles[i]);
        }
    }

    for (int i = 0; i < LEVEL_ENTITY_COUNT; i++) {
        if (level->entities[i] != NULL) {
            entity_render(renderer, level->entities[i]);
        }
    }
}
