#include <stdio.h>
#include <SDL2/SDL.h>
#include "entity/entity.h"
#include "sprite/sprite.h"
#include "entity/player.h"
#include "system/system.h"
#include "sprite/texture.h"

Entities entities;
Sprites sprites;
const Uint8 *key;

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

    SDL_RenderSetLogicalSize(renderer, 800, 600);
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_ShowCursor(SDL_DISABLE);

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
        sys_render_update(&entities, &sprites, renderer);
        //sys_render_print_info(&entities);
        SDL_RenderPresent(renderer);
    }

    entity_destroy(&entities, player_id);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
