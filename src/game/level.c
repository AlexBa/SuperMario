#include "level.h"

Level* level_create(SDL_Renderer *renderer, const char *name) {
    Level *level = malloc(sizeof(Level));
    level->name = name;
    level->background = sprite_create(renderer, name);

    for (int i = 0; i < LEVEL_TILE_COUNT; i++) {
        level->tileFree[i] = 1;
    }

    return level;
}

void level_delete(Level *level) {
    for (int i = 0; i < LEVEL_TILE_COUNT; i++) {
        free(level->tiles[i]);
    }

    free(level);
}

void level_add_tile(Level *level, Tile *tile) {
    for (int i = 0; i < LEVEL_TILE_COUNT; i++) {
        if (level->tileFree[i] == 1) {
            level->tiles[i] = tile;
            level->tileFree[i] = 0;
            return;
        }
    }

    printf("Error: Failed to add the tile '%s' to the level '%s'. No more space available.\n", level->name, tile->name);
    exit(1);
}

void level_remove_tile(Level *level, Tile *tile) {
    for (int i = 0; i < LEVEL_TILE_COUNT; i++) {
        if (level->tiles[i]->name == tile->name &&
            level->tiles[i]->type == tile->type &&
            level->tiles[i]->bounds->x == tile->bounds->x &&
            level->tiles[i]->bounds->y == tile->bounds->y) {
            free(level->tiles[i]);
            return;
        }
    }

    printf("Error: Failed to remove the tile '%s' to the level '%s'. Tile not found.\n", level->name, tile->name);
    exit(1);
}

void level_render(SDL_Renderer *renderer, Level *level) {
    sprite_render(renderer, level->background, 0, 0);

    for (int i = 0; i < LEVEL_TILE_COUNT; i++) {
        if (level->tileFree[i] == 0) {
            tile_render(renderer, level->tiles[i]);
        }
    }
}
