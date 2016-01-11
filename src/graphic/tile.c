#include "tile.h"

/**
 * Create a new tile
 * @param renderer The renderer for the texture in the tile
 * @param name The path to the texture file
 * @param type The type of the tile
 * @param x The horizontal position of the tile
 * @param y The vertical position of the tile
 * @return Either the tile or NULL
 */
Tile* tile_create(SDL_Renderer *renderer, const char* name, int type, int x, int y) {
    Tile *tile = malloc(sizeof(Tile));
    tile->name = name;
    tile->type = type;
    tile->sprite = sprite_get(name);
    if(tile->sprite == SPRITE_EMPTY) {
        tile->sprite = sprite_create(renderer, name);
    }
    tile->bounds = malloc(sizeof(SDL_Rect));
    tile->bounds->x = x;
    tile->bounds->y = y;
    tile->bounds->w = TILE_WIDTH;
    tile->bounds->h = TILE_HEIGHT;

    return tile;
}

/**
 * Deletes a tile
 * @param tile The tile to delete
 * @return Either a success or error code
 */
void tile_delete(Tile *tile) {
    free(tile);
}

/**
 * Render the tile to the screen
 * @param renderer The renderer we want to draw to
 * @param tile The tile we want to draw
 */
void tile_render(SDL_Renderer *renderer, Tile *tile) {
    sprite_render(renderer, tile->sprite, tile->bounds->x, tile->bounds->y);
}
