#include "tile.h"

/**
 * Create a new tile
 * @param renderer  The renderer for the texture in the tile
 * @param name The path to the texture file
 * @param type The type of the tile
 * @param x The horizontal position of the tile
 * @param y The vertical position of the tile
 * @return Either the ID of the tile or an error code
 */
int tile_create(SDL_Renderer *renderer, const char* name, int type, int x, int y) {
    for(int tile = 0; tile < TILE_COUNT; ++tile) {
        if(tiles.types[tile] == TILE_NONE) {
            tiles.names[tile] = name;
            tiles.types[tile] = type;
            tiles.sprites[tile] = sprite_get(name);
            if(tiles.sprites[tile] == ERROR_SPRITE_NOT_FOUND) {
                tiles.sprites[tile] = sprite_create(renderer, name);
            }

            tiles.x[tile] = x;
            tiles.y[tile] = y;
            SDL_Texture * texture = sprites.textures[tiles.sprites[tile]];
            SDL_QueryTexture(texture, NULL, NULL, &tiles.width[tile], &tiles.height[tile]);

            return tile;
        }
    }

    printf("ERROR: No more space for tile '%s' available.\n", name);
    return TILE_ERROR_NO_SPACE_AVAILABLE;
}

/**
 * Deletes a tile by the ID
 * @param tile The ID of the tile
 * @return Either a success or error code
 */
int tile_delete(int tile) {
    if (tile > TILE_COUNT) {
        printf("ERROR: Out of range for the tile #%d.\n", tile);
        return TILE_ERROR_OUT_OF_RANGE;
    }

    if(tiles.types[tile] == TILE_NONE) {
        printf("ERROR: Failed to find the tile #%d.\n", tile);
        return TILE_ERROR_NOT_FOUND;
    }

    tiles.names[tile] = NULL;
    tiles.types[tile] = 0;
    tiles.x[tile] = 0;
    tiles.y[tile] = 0;
    tiles.width[tile] = 0;
    tiles.height[tile] = 0;
    tiles.sprites[tile] = 0;

    return TILE_SUCCESS;
}

/**
 * Get the tile by the position
 * @param x The horizontal position of the tile
 * @param y The vertical position of the tile
 * @return Either the ID of the tile or an error code
 */
int tile_get_by_position(int x, int y) {
    for(int tile = 0; tile < TILE_COUNT; ++tile) {
        if(tiles.x[tile] == x && tiles.y[tile]) {
            return tile;
        }
    }

    printf("ERROR: Failed to find the tile x:%d y:%d.\n", x, y);
    return TILE_ERROR_NOT_FOUND;
}
