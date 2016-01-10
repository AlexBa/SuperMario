#include "texture.h"

/**
 * Load the texture from the related BMP file
 * @param renderer The renderer for the texture
 * @param path The path for the texture
 */
SDL_Texture* texture_create(SDL_Renderer *renderer, const char* path) {
    SDL_Surface *surface = NULL;
    SDL_Texture *texture = NULL;

    surface = SDL_LoadBMP(path);
    if(surface == NULL) {
        printf("Error: couldn't load texture %s", SDL_GetError());
        exit(1);
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    return texture;
}

/**
 * Render the texture at the position x and y
 * @param renderer The renderer we want to draw to
 * @param texture The texture we want to draw
 * @param x The horizontal position of the texture
 * @param y The vertical position of the texture
 */
void texture_render(SDL_Renderer *renderer, SDL_Texture * texture, int x, int y) {
    SDL_Rect destination;
    destination.x = x;
    destination.y = y;

    // Query the width and height of the texture
    SDL_QueryTexture(texture, NULL, NULL, &destination.w, &destination.h);
    SDL_RenderCopy(renderer, texture, NULL, &destination);
}
