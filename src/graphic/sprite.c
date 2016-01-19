#include "sprite.h"

/**
 * Create a new sprite
 * @param renderer The renderer for the texture in the sprite
 * @param name The path the BMP file
 * @return Either the sprite or NULL
 */
Sprite* sprite_create(SDL_Renderer *renderer, const char *name) {
    for(int sprite = 1; sprite < SPRITE_COUNT; ++sprite) {
        if(spriteCache[sprite].cashId == SPRITE_EMPTY) {
            spriteCache[sprite].cashId = sprite;
            spriteCache[sprite].texture = texture_create(renderer, name);
            spriteCache[sprite].name = name;
            return &spriteCache[sprite];
        }
    }

    printf("ERROR: No more space for sprite '%s' available.\n", name);
    exit(1);
}

/**
 * Delete an existing sprite
 * @param sprite The sprite ID
 * @return Either a success or error code
 */
void sprite_delete(Sprite *sprite) {
    if (sprite->cashId > SPRITE_COUNT || sprite < 0) {
        printf("ERROR: Out of range for the sprite #%d.\n", sprite->cashId);
        exit(1);
    }

    if(sprite->cashId == SPRITE_EMPTY) {
        printf("ERROR: Failed to find the sprite #%d.\n", sprite->cashId);
        exit(1);
    }

    sprite->cashId = SPRITE_EMPTY;
    sprite->name = NULL;
    sprite->texture = NULL;
}

/**
 * Get an existing sprite by the name
 * @param name The path of the sprite
 * @return The related sprite
 */
Sprite* sprite_get(SDL_Renderer *renderer, const char *name) {
    for(int sprite = 0; sprite < SPRITE_COUNT; sprite++) {
        if(spriteCache[sprite].cashId != SPRITE_EMPTY && strcmp(spriteCache[sprite].name, name) == 0) {
            return &spriteCache[sprite];
        }
    }

    return sprite_create(renderer, name);
}

/**
 * @param renderer The renderer we want to draw to
 * @param sprite The sprite to render
 * @param x The horizontal position of the sprite
 * @param y the vertical position of the sprite
 */
void sprite_render(SDL_Renderer *renderer, Sprite *sprite, int x, int y) {
    texture_render(renderer, sprite->texture, x, y);
}
