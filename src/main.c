#include <stdio.h>
#include <SDL2/SDL.h>
#include "entity/entity.h"
#include "graphic/sprite.h"
#include "entity/player.h"
#include "system/system.h"
#include "graphic/texture.h"
#include "graphic/tile.h"

Entities entities;

const Uint8 *key;

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

int main(int argc, char** argv) {
    SDL_Window *window;
    SDL_Renderer *renderer;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("%s", SDL_GetError());
        return 1;
    } else {
        printf("SDL is working correctly.\n\n");
    }

    SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_RESIZABLE, &window, &renderer);
    if(window==NULL) {
        printf("Error: Could not create window. %s", SDL_GetError());
    }
    if(renderer==NULL) {
        printf("Error: Could not create renderer. %s", SDL_GetError());
    }

    SDL_SetWindowSize(window, WINDOW_WIDTH, WINDOW_HEIGHT);
    SDL_RenderSetLogicalSize(renderer, 800, 600);
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_ShowCursor(SDL_DISABLE);


    int tile = tile_create(renderer, "player.bmp", TILE_BLOCK, 30, 30);

    unsigned int player_id = player_create(&entities, 100.0f, 16.0f);

    int done = 0;
    while(!done){
        key = SDL_GetKeyboardState(NULL);
        SDL_Event ev;
        while(SDL_PollEvent(&ev)) {
            switch(ev.type) {
                case SDL_QUIT:
                    done = 1;
                    break;
                case SDL_KEYDOWN:
                    if(ev.key.keysym.sym == SDLK_ESCAPE)
                        done = 1;
                    if(ev.key.keysym.sym == SDLK_p)
                        break;
                case SDL_KEYUP:
                    break;
                default:
                    break;
            }
        }

        sys_input_update(&entities, key);

        SDL_RenderClear(renderer);
        tile_render(renderer, tile);
        sys_render_update(&entities, renderer);
        //sys_render_print_info(&entities);
        SDL_RenderPresent(renderer);
    }

    entity_destroy(&entities, player_id);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
