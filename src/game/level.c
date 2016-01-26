#include "level.h"

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
    level->bounds.w = LEVEL_WIDTH;
    level->bounds.h = LEVEL_HEIGHT;
    level->camera.x = 0;
    level->camera.y = 0;
    level->camera.w = LEVEL_CAMERA_WIDTH;
    level->camera.h = LEVEL_CAMERA_HEIGHT;

    for (int i = 0; i < LEVEL_TILE_COUNT; i++) {
        level->tiles[i] = NULL;
    }

    for (int i = 0; i < LEVEL_ENTITY_COUNT; i++) {
        level->entities[i] = NULL;
    }

    char field [LEVEL_TILE_HEIGHT][LEVEL_TILE_WIDTH] =
        {"__________________________________________________",
         "|                       |                        |",
         "|                       |     ccc   c      c c   |",
         "|         c             |    cccc   c     cc cc  |",
         "|P       c  c           |   ccccc   c    cc   cc |",
         "|cccc  c c  c       c   |  cccccc   c   cc  E  cc|",
         "|     c Ecc  c    c     | _______________________|",
         "|       cc c  c   c     |                        |",
         "|      c      M c       |c c  c  c   c  cc  c  c |",
         "|_____________________ _|                     c  |",
         "|        cF            c|  c  c  c  cc   c c c   |",
         "|  ccccc  cccc  cc   c c|c                       |",
         "|  cR         c   cc c c| cR       c         c   |",
         "|   c    c c     c   E  |  c       LcEEE    c    |",
         "|_ _____________________|______________________ _|",
         "|          c            |         L    cR    c  c|",
         "|c      Lc c   c        |      cccc  c c     Lc  |",
         "| c    Ecc    c  c c   c|    c      c  c  c  c  c|",
         "|  ccccc  cR                c cc E c c   c     c |",
         "|________________________________________________|",};

    for (int i = 0; i < LEVEL_TILE_HEIGHT; i++) {
        for (int j = 0; j < LEVEL_TILE_WIDTH; j++) {
            if (field[i][j] == '_') {         //Normal Tile
                Tile *tile = tile_create(renderer, "brick.bmp", TILE_BLOCK, (j * TILE_WIDTH), (i * TILE_HEIGHT));
                level_add_tile(level, tile);
            } else if (field [i][j] == '|') { //Normal Tile
                Tile *tile = tile_create(renderer, "brick.bmp", TILE_BLOCK, (j * TILE_WIDTH), (i * TILE_HEIGHT));
                level_add_tile(level, tile);
            } else if (field [i][j] == 'c') { //Normal Tile
                Tile *tile = tile_create(renderer, "brick.bmp", TILE_BLOCK, (j * TILE_WIDTH), (i * TILE_HEIGHT));
                level_add_tile(level, tile);
            } else if (field [i][j] == 'P') { //Player
                Entity *player = player_create((j * TILE_WIDTH), (i * TILE_HEIGHT));
                level_add_entity(level, player);
                player->check_point.x = (j * TILE_WIDTH);
                player->check_point.y = (i * TILE_HEIGHT);
            } else if (field [i][j] == 'E') { //Enemy
                Entity *enemy = enemy_create((j * TILE_WIDTH), (i * TILE_HEIGHT));
                level_add_entity(level, enemy);
            } else if (field [i][j] == 'L') { //Pyro Left Shooting
                Entity *pyro = pyro_create((j * TILE_WIDTH), (i * TILE_HEIGHT), "left");
                level_add_entity(level, pyro);
            } else if (field [i][j] == 'R') { //Pyro Right Shooting
                Entity *pyro = pyro_create((j * TILE_WIDTH), (i * TILE_HEIGHT), "right");
                level_add_entity(level, pyro);
            } else if (field [i][j] == 'F') { //Mushroom
                Entity *fireflower = fireflower_create((j * TILE_WIDTH), (i * TILE_HEIGHT));
                level_add_entity(level, fireflower);
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
 * Scroll the level
 * @param level
 */
void level_scroll(Level *level) {
    for (int i = 0; i < LEVEL_ENTITY_COUNT; i++) {
        Entity *entity = level->entities[i];
        if (entity != NULL &&
            (entity->component_mask & CMP_PLAYER) != 0 &&
            (entity->component_mask & CMP_COLLISION) != 0 &&
            (entity->component_mask & CMP_POSITION) != 0) {
            // Set the camera position
            SDL_Rect *bounds = entity->collision.bounds;
            level->camera.x = (int)((bounds->x + bounds->w / 2) - SCREEN_WIDTH);
            level->camera.y = (int)((bounds->y + bounds->h / 2) - SCREEN_HEIGHT);

            //Keep the camera in bounds
            if(level->camera.x < 0) {
                level->camera.x = 0;
            }
            if(level->camera.y < 0) {
                level->camera.y = 0;
            }

            if(level->camera.x >  160 + ((LEVEL_TILE_WIDTH-50)*TILE_WIDTH)) {
                level->camera.x =  160 + ((LEVEL_TILE_WIDTH-50)*TILE_WIDTH);
            }
            if(level->camera.y > TILE_HEIGHT * (LEVEL_TILE_HEIGHT - 10)) {
                level->camera.y = TILE_HEIGHT * (LEVEL_TILE_HEIGHT - 10);
            }

        }
    }
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
            tile_render(renderer, level->tiles[i], &level->camera);
        }
    }

    for (int i = 0; i < LEVEL_ENTITY_COUNT; i++) {
        if (level->entities[i] != NULL) {
            entity_render(renderer, level->entities[i], &level->camera);
        }
    }
}
