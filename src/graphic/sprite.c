#include "sprite.h"

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

int sprite_get( const char *name) {
    for(int sprite = 0; sprite < SPRITE_COUNT; ++sprite) {
        if(sprites.names[sprite] == name) {
            return sprite;
        }
    }

    printf("ERROR: Failed to find the sprite '%s'.\n", name);
    return ERROR_SPRITE_NOT_FOUND;
}

void sprite_render(SDL_Renderer *renderer, const char *name, int x, int y) {
    int sprite;
    SDL_Texture *texture = NULL;

    sprite = sprite_get(name);
    if (sprite >= 0) {
        texture = sprites.textures[sprite];
        texture_render(renderer, texture, x, y);
    }
}
