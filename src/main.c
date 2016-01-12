#include <stdio.h>
#include <SDL2/SDL.h>
#include "entity/entity.h"
#include "entity/player.h"
#include "system/system.h"
#include "graphic/tile.h"
#include "game/level.h"

Entities entities;
const Uint8 *key;

int main(int argc, char** argv) {
    SDL_Window *window;
    SDL_Renderer *renderer;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("%s", SDL_GetError());
        return 1;
    }

    SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_RESIZABLE, &window, &renderer);
    if(window==NULL) {
        printf("Error: Could not create window. %s", SDL_GetError());
        return 1;
    }
    if(renderer==NULL) {
        printf("Error: Could not create renderer. %s", SDL_GetError());
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_ShowCursor(SDL_DISABLE);

    Level *level = level_create(renderer, "player.bmp");
    Tile *tile1 = tile_create(renderer, "player.bmp", TILE_BLOCK, 50, 30);
    Tile *tile2 = tile_create(renderer, "player.bmp", TILE_BLOCK, 100, 60);
    level_add_tile(level, tile1);
    level_add_tile(level, tile2);

    unsigned int player_id = player_create(&entities, 100.0f, 16.0f);

    unsigned int last_ticks = SDL_GetTicks();
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

        unsigned int current_ticks = SDL_GetTicks();
        float delta = (current_ticks - last_ticks) / 1000.0f;
        last_ticks = current_ticks;

        sys_input_update(level, &entities, key, delta);
        SDL_RenderClear(renderer);
        level_render(renderer, level);
        sys_render_update(&entities, renderer);
        SDL_RenderPresent(renderer);
    }

    level_delete(level);
    entity_destroy(&entities, player_id);

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
