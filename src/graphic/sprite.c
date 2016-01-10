#include "sprite.h"

/**
 * Create a new sprite
 * @param renderer The renderer for the texture in the sprite
 * @param name The path the BMP file
 * @return Either the sprite ID or an error code
 */
int sprite_create(SDL_Renderer *renderer, const char *name) {
    for(int sprite = 0; sprite < SPRITE_COUNT; ++sprite) {
        if(sprites.textures[sprite] == NULL) {
            sprites.textures[sprite] = texture_create(renderer, name);
            sprites.names[sprite] = name;
            return sprite;
        }
    }

    printf("ERROR: No more space for sprite '%s' available.\n", name);
    return SPRITE_ERROR_NO_SPACE_AVAILABLE;
}

/**
 * Delete an existing sprite
 * @param sprite The sprite ID
 * @return Either a success or error code
 */
int sprite_delete(int sprite) {
    if (sprite > SPRITE_COUNT) {
        printf("ERROR: Out of range for the sprite #%d.\n", sprite);
        return SPRITE_ERROR_OUT_OF_RANGE;
    }

    if(sprites.names[sprite] == NULL) {
        printf("ERROR: Failed to find the sprite #%d.\n", sprite);
        return SPRITE_ERROR_NOT_FOUND;
    }

    sprites.names[sprite] = NULL;
    sprites.textures[sprite] = NULL;

    return SPRITE_SUCCESS;
}

/**
 * Get an existing sprite by the name
 * @param name The path of the sprite
 * @return Either the sprite ID or an related error code
 */
int sprite_get(const char *name) {
    for(int sprite = 0; sprite < SPRITE_COUNT; ++sprite) {
        if(sprites.names[sprite] == name) {
            return sprite;
        }
    }

    printf("ERROR: Failed to find the sprite '%s'.\n", name);
    return SPRITE_ERROR_NOT_FOUND;
}

/**
 * @param renderer The renderer we want to draw to
 * @param sprite The sprite ID
 * @param x The horizontal position of the sprite
 * @param y the vertical position of the sprite
 */
void sprite_render(SDL_Renderer *renderer, int sprite, int x, int y) {
    SDL_Texture *texture = NULL;

    texture = sprites.textures[sprite];
    texture_render(renderer, texture, x, y);
}
